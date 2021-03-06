#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "CreateObject.h"
//#include "CreateObject.cpp"
/*
* そろそろここに地面生成や物体生成を別のクラスにしていきたい。
*/

#define KEY_ESC 27


CreateObject cobj;

const int PosX = 100;  //生成するウィンドウ位置のX座標
const int PosY = 100;  //生成するウィンドウ位置のY座標
const int Width = 1024;    //生成するウィンドウの幅
const int Height = 576;    //生成するウィンドウの高さ

const float MoveSpeed = 0.05f;

float camPosX = 0;
float camPosZ = 200;

float camRttX = 0;
float camRttY = 0;

#define PRESSED_KEY_W Prsd_W
#define PRESSED_KEY_A Prsd_A
#define PRESSED_KEY_S Prsd_S
#define PRESSED_KEY_D Prsd_D
bool Prsd_W = false;
bool Prsd_A = false;
bool Prsd_S = false;
bool Prsd_D = false;

GLdouble normal[][3] = {//面の法線ベクトル
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};



void MoveCamera()
{
	if (PRESSED_KEY_W)
	{
		camPosX += MoveSpeed * cos(camRttX);
		camPosZ -= MoveSpeed * sin(camRttX);
	}
	if (PRESSED_KEY_A)
	{
		camPosX -= MoveSpeed * sin(camRttX);
		camPosZ -= MoveSpeed * cos(camRttX);
	}
	if (PRESSED_KEY_S)
	{
		camPosX -= MoveSpeed * cos(camRttX);
		camPosZ += MoveSpeed * sin(camRttX);
	}
	if (PRESSED_KEY_D)
	{
		camPosX += MoveSpeed * sin(camRttX);
		camPosZ += MoveSpeed * cos(camRttX);
	}
}

/// <summary>
/// マウスの位置を取得
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
int px = NULL, py = NULL;
void MousePosition(int x, int y)
{
	printf("x:%d y:%d\n", x, y);
		camRttX = (float)((Width / 2) - x) * 0.01f, camRttY = (float)((Height / 2) - y) * 0.01f;
		//glutWarpPointer(Width / 2, Height / 2);
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



/// <summary>
/// Key入力時に呼び出される
/// </summary>
/// <param name="key">入力キーの種類</param>
/// <param name="x"></param>
/// <param name="y"></param>
void PressedKey(unsigned char key, int x, int y) {
	//printf_s("%d\n", key);
	switch (key)
	{
	case KEY_ESC:
		exit(0);
		break;
	case 'w':
		PRESSED_KEY_W = true;
		break;
	case 'a':
		PRESSED_KEY_A = true;
		break;
	case 's':
		PRESSED_KEY_S = true;
		break;
	case 'd':
		PRESSED_KEY_D = true;
		break;
	default:
		break;
	}
}

void UpedKey(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w':
		PRESSED_KEY_W = false;
		break;
	case 'a':
		PRESSED_KEY_A = false;
		break;
	case 's':
		PRESSED_KEY_S = false;
		break;
	case 'd':
		PRESSED_KEY_D = false;
		break;
	default:
		break;
	}
}

/// <summary>
/// アイドル時に呼び出される関数。再描画する処理を入れている。
/// </summary>
void Idle() {
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

	MoveCamera();

	gluLookAt(
		camPosX, 50, camPosZ, // 視点の位置x,y,z;(横、高さ、奥行)
		camPosX + cos(camRttX) * cos(camRttY), 50 + sin(camRttY), camPosZ - sin(camRttX) * cos(camRttY),   // 視界の中心位置の参照点座標x,y,z(どこの座標を画面の真ん中に来るのか)
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
	glutCreateWindow("一人称視点");  //ウィンドウの作成、タイトルを決める

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定

	glutDisplayFunc(Display); //Display関数に描かれているものを描画する
	glutPassiveMotionFunc(MousePosition);
	glutKeyboardFunc(PressedKey);//ケー入力時にInputKeyを呼ぶ
	glutKeyboardUpFunc(UpedKey);
	glutIdleFunc(Idle);//アイドル時にIdle関数を呼ぶ
	Init(); //初期化
	glutMainLoop();
	return 0;
}