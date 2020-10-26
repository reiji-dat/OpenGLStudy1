#include <GL/glut.h>
#include <stdio.h>
/*
* そろそろここに地面生成や物体生成を別のクラスにしていきたい。
*/

#define KEY_ESC 27

const int PosX = 100;  //生成するウィンドウ位置のX座標
const int PosY = 100;  //生成するウィンドウ位置のY座標
const int Width = 1024;    //生成するウィンドウの幅
const int Height = 576;    //生成するウィンドウの高さ
float camPosX = -100;

int face[][4] = {//面の定義
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 }
};

GLdouble normal[][3] = {//面の法線ベクトル
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};

// 物質質感の定義
struct Material {		//structの後の名前は自由に変えられる
	GLfloat ambient[4];	//環境光に対する反射係数
	GLfloat diffuse[4];	//元の色
	GLfloat specular[4];//ハイライトの強さ
	GLfloat shininess;	//ハイライトの大きさ
};

int btime = 0;
int ttltime = 0;
int flame;
void FPS() {
	flame++;
	int time = glutGet(GLUT_ELAPSED_TIME);
	//printf("1フレーム0.00%d秒\n", time - btime);
	ttltime += time - btime;
	if (ttltime >= 1000)
	{
		printf("%dfps\n",flame);
		ttltime -= 1000;
		flame = 0;
	}
	btime = time;
}

void Ground(float x,float z,float wid) {

	glColor3d(0.8, 0.8, 0.8);  //地面の色(RGB)

	//glBegin関数について(http://wisdom.sakura.ne.jp/system/opengl/gl3.html)
	glBegin(GL_LINES);//2つの頂点をペアとし、それぞれのペアを独立した線分として扱う。
	//for(y軸地面の最大値まで20(線の幅)ごとに繰り返す
	for (float lz = -z; lz <= z; lz += wid) {
		glVertex3d(-x, 0, lz);//頂点の始点
		glVertex3d(x, 0, lz);//頂点の終点(を自動でしてくれる)
	}
	for (float lx = -x; lx <= x; lx += wid) {
		glVertex3d(lx, 0, z);
		glVertex3d(lx, 0, -z);
	}
	glEnd();//線を引く処理を終了する
}

void CreateSphere(float r, float g, float b,float x, float y, float z,float s)
{
	Material metallic = {
	{r * 0.28,   g * 0.28,  b * 0.28,   1.0},//影
	{r,  g,  b,   1.0},//元
	{0.8 + r * r * 0.14, 0.8 + g * g * 0.14, 0.8 + b * b * 0.14,  1.0},//ハイライト
	76.8 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, metallic.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metallic.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metallic.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &metallic.shininess);
	glTranslated(x, y, z);//位置(横,高さ,奥行)
	glutSolidSphere(s, 20, 20);//(半径, Z軸まわりの分割数, Z軸に沿った分割数)
	glPopMatrix();
}

void CreateCube(float r, float g, float b, float x, float y, float z, float s)
{
	Material metallic = {
	{r * 0.28,   g * 0.28,  b * 0.28,   1.0},//影
	{r,  g,  b,   1.0},//元
	{0.8 + r * r * 0.14, 0.8 + g * g * 0.14, 0.8 + b * b * 0.14,  1.0},//ハイライト
	76.8 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, metallic.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metallic.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metallic.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &metallic.shininess);
	glTranslated(x, y, z);
	glutSolidCube(s);//(一辺の長さ)
	glPopMatrix();
}

void CreateCone(float r, float g, float b, float x, float y, float z, float rad, float high)
{
	Material metallic = {
	{r * 0.28,   g * 0.28,  b * 0.28,   1.0},//影
	{r,  g,  b,   1.0},//元
	{0.8 + r * r * 0.14, 0.8 + g * g * 0.14, 0.8 + b * b * 0.14,  1.0},//ハイライト
	76.8 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, metallic.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metallic.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metallic.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &metallic.shininess);
	glTranslated(x, y, z);//位置(横,高さ,奥行)
	glRotated(90, -1, 0, 0);
	glutSolidCone(rad, high, 20, 20);//(半径, 高さ, Z軸まわりの分割数, Z軸に沿った分割数)
	glPopMatrix();
}

void CreateBox(float r, float g, float b, float x, float y, float z, float width, float depth, float height)
{
	width = width / 2;
	depth = depth / 2;
	height = height / 2;
	GLdouble ver[][3] = {
	{ -width, -depth, -height },
	{  width, -depth, -height },
	{  width,  depth, -height },
	{ -width,  depth, -height },
	{ -width, -depth,  height },
	{  width, -depth,  height },
	{  width,  depth,  height },
	{ -width,  depth,  height }
	};
	Material metallic = {
	{r * 0.28,   g * 0.28,  b * 0.28,   1.0},//影
	{r,  g,  b,   1.0},//元
	{0.8 + r * r * 0.14, 0.8 + g * g * 0.14, 0.8 + b * b * 0.14,  1.0},//ハイライト
	76.8 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, metallic.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metallic.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metallic.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &metallic.shininess);
	glTranslated(x, y, z);//平行移動値の設定
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(ver[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();//これがないと始点が変更される。
}

/// <summary>
/// Key入力時に呼び出される
/// </summary>
/// <param name="key">入力キーの種類</param>
/// <param name="x"></param>
/// <param name="y"></param>
void InputKey(unsigned char key, int x, int y) {
	printf_s("%d\n", key);
	switch (key)
	{
	case KEY_ESC:
		exit(0);
		break;
	case 'd':
		camPosX += 0.5f;
		break;
	default:
		break;
	}
}

/// <summary>
/// アイドル時に呼び出される関数。再描画する処理を入れている。
/// </summary>
void Idle() {
	FPS();
	glutPostRedisplay();//再描画する
}

/// <summary>
/// 初期化
/// </summary>
void Init() {
	//printf("初期化中\n");
	glClearColor(1.0, 1.0, 1.0, 1.0); //背景色
	glEnable(GL_DEPTH_TEST);//ディープテストを無効化

	//光源を設定
	GLfloat light_position0[] = { 20.0, 50.0, 50.0, 1.0 }; //光源の座標
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //光源を設置

}

/// <summary>
/// ここに描画させたいものを描く
/// </summary>
void Display() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
	glLoadIdentity();//行列の初期化

	//gluPerspective(視野角, 横割縦, 描画される最も距離, 描画される最も遠い距離);
	gluPerspective(30.0, (double)Width / (double)Height, 0.1, 1000.0); //透視図法

	gluLookAt(
		camPosX, 50, 200, // 視点の位置x,y,z;(横、高さ、奥行)
		camPosX, 20, 00,   // 視界の中心位置の参照点座標x,y,z(どこの座標を画面の真ん中に来るのか)
		0.0, 1.0, 0.0);  //どこの座標が画面の上に来るのか(この場合+z軸が画面の上)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//初期化
	glViewport(0, 0, Width, Height);//ウィンドウの描画範囲

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	CreateSphere(1, 0, 0, 0, 0, 0, 10);
	CreateCube(0, 1, 0, 20, 0, 0, 10);
	CreateCone(0, 0, 1, -20, 0, 0, 10, 20);
	CreateBox(0, 1, 1, 20, 20, -20, 20, 30, 10);
	CreateCube(0.5, 0.5, 0.5, 50.0, 50.0, 20.0, 3);
	
	glDisable(GL_LIGHTING);

	Ground(300.0f,300.f,20.0f);//地面を描画

	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);//環境の初期化

	glutInitWindowPosition(PosX, PosY);//ウィンドウの表示位置
	glutInitWindowSize(Width, Height); //ウィンドウサイズ
	glutCreateWindow("ウィンドウのタイトル");  //ウィンドウの作成、タイトルを決める

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定

	glutDisplayFunc(Display); //Display関数に描かれているものを描画する
	glutKeyboardFunc(InputKey);//ケー入力時にInputKeyを呼ぶ
	glutIdleFunc(Idle);//アイドル時にIdle関数を呼ぶ
	Init(); //初期化
	glutMainLoop();
	return 0;
}