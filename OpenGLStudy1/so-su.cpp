#include <GL/glut.h>

const int PosX = 100;  //生成するウィンドウ位置のX座標
const int PosY = 100;  //生成するウィンドウ位置のY座標
const int Width = 1024;    //生成するウィンドウの幅
const int Height = 576;    //生成するウィンドウの高さ

int face[][4] = {//面の定義
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 }
};

void Ground(float x,float y,float wid) {

	glColor3d(0.8, 0.8, 0.8);  //地面の色(RGB)

	//glBegin関数について(http://wisdom.sakura.ne.jp/system/opengl/gl3.html)
	glBegin(GL_LINES);//2つの頂点をペアとし、それぞれのペアを独立した線分として扱う。
	//for(y軸地面の最大値まで20(線の幅)ごとに繰り返す
	for (float ly = -y; ly <= y; ly += wid) {
		glVertex3d(-x, ly, 0);//頂点の始点
		glVertex3d(x, ly, 0);//頂点の終点(を自動でしてくれる)
	}
	for (float lx = -x; lx <= x; lx += wid) {
		glVertex3d(lx, y, 0);
		glVertex3d(lx, -y, 0);
	}
	glEnd();//線を引く処理を終了する
}

/// <summary>
/// 球体を生成
/// </summary>
/// <param name="r">赤</param>
/// <param name="g">緑</param>
/// <param name="b">青</param>
/// <param name="x">横</param>
/// <param name="y">奥行</param>
/// <param name="z">高さ</param>
/// <param name="s">大きさ</param>
void CreateSphere(float r, float g, float b,float x, float y, float z,float s)
{
	glPushMatrix();
	glColor3d(r, g, b); //色
	glTranslated(x, y, z);//位置(横,奥行,高さ)
	glutSolidSphere(s, 20, 20);//(半径, Z軸まわりの分割数, Z軸に沿った分割数)
	glPopMatrix();
}

/// <summary>
/// 立方体を生成
/// </summary>
/// <param name="r">赤</param>
/// <param name="g">緑</param>
/// <param name="b">青</param>
/// <param name="x">横</param>
/// <param name="y">奥行</param>
/// <param name="z">高さ</param>
/// <param name="s">大きさ</param>
void CreateCube(float r, float g, float b, float x, float y, float z, float s)
{
	glPushMatrix();
	glColor3d(r, g, b);
	glTranslated(x, y, z);
	glutSolidCube(s);//(一辺の長さ)
	glPopMatrix();
}

/// <summary>
/// 円柱を生成
/// </summary>
/// <param name="r">赤</param>
/// <param name="g">緑</param>
/// <param name="b">青</param>
/// <param name="x">横</param>
/// <param name="y">奥行</param>
/// <param name="z">高さ</param>
/// <param name="rad">半径</param>
/// <param name="high">高さ</param>
void CreateCone(float r, float g, float b, float x, float y, float z, float rad, float high)
{
	glPushMatrix();
	glColor3d(r, g, b);//色
	glTranslated(x, y, z);//位置(横,奥行,高さ)
	glutSolidCone(rad, high, 20, 20);//(半径, 高さ, Z軸まわりの分割数, Z軸に沿った分割数)
	glPopMatrix();
}

/// <summary>
/// 直方体を生成
/// </summary>
/// <param name="r">赤</param>
/// <param name="g">緑</param>
/// <param name="b">青</param>
/// <param name="x">横</param>
/// <param name="y">奥行</param>
/// <param name="z">高さ</param>
/// <param name="width">横の長さ</param>
/// <param name="depth">縦の長さ</param>
/// <param name="height">高さの長さ</param>
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
	//直方体
	glPushMatrix();
	glColor3d(r, g, b);//色の設定
	glTranslated(x, y, z);//平行移動値の設定
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(ver[face[j][i]]);
		}
	}
	glEnd();
}

/// <summary>
/// 初期化
/// </summary>
void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //背景色
	glEnable(GL_DEPTH_TEST);//ディープテストを無効化

	//ここから下は地面の描画関係
	glMatrixMode(GL_PROJECTION);//行列モードの設定（GL_PROJECTION : 透視変換行列の設定、GL_MODELVIEW：モデルビュー変換行列）
	glLoadIdentity();//行列の初期化

	//gluPerspective(視野角, 横割縦, 描画される最も距離, 描画される最も遠い距離);
	gluPerspective(30.0, (double)Width / (double)Height, 0.1, 1000.0); //透視図法

	gluLookAt(
		0.0, -200.0, 50.0, // 視点の位置x,y,z;(横、奥行き、高さ)
		0.0, 0.0, 20,   // 視界の中心位置の参照点座標x,y,z(どこの座標を画面の真ん中に来るのか)
		0.0, 0.0, 1.0);  //どこの座標が画面の上に来るのか(この場合+z軸が画面の上)
}

/// <summary>
/// ここに描画させたいものを描く
/// </summary>
void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CreateSphere(1, 0, 0, 0, 0, 0, 10);

	CreateCube(0, 1, 0, 20, 0, 0, 10);

	CreateCone(0, 0, 1, -20, 0, 0, 10, 20);

	CreateBox(0, 1, 1, 0, -20, 20, 20, 10, 30);

	//これを消したり値を変えたら下向きになった
	/*
		GL_MODELVIEW	モデルビュー行列
		GL_PROJECTION	射影行列
		GL_TEXTURE	テクスチャ行列
		の三種類があるらしい
	*/
	//後で調べる
	glMatrixMode(GL_MODELVIEW);//行列モードの設定

	//無くても動作した
	//後で調べる
	glLoadIdentity();//行列の初期化

	//この数値の操作したら描画される基準が変わる
	//画面に合わせて描画する設定と推測
	glViewport(0, 0, Width, Height);
	
	Ground(300.0f,300.f,20.0f);//地面を描画

	glutSwapBuffers();//調べたけどよく分からないとりあえず必要なもの(?)
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);//環境の初期化

	glutInitWindowPosition(PosX, PosY);//ウィンドウの表示位置
	glutInitWindowSize(Width, Height); //ウィンドウサイズ

	//ディスプレイモードの指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//Default:GLUT_RGBA | GLUT_SINGLE

	glutCreateWindow("ウィンドウのタイトル");  //ウィンドウの作成、タイトルを決める
	glutDisplayFunc(Display); //Display関数に描かれているものを描画する

	Init(); //初期化

	/*
	* ここをコメントアウトすると一瞬だけ表示された
	* おそらく表示し続ける処理だと推測した
	*/
	glutMainLoop();

	return 0;
}