#include <GL/glut.h>

const int PosX = 100;  //生成するウィンドウ位置のX座標
const int PosY = 100;  //生成するウィンドウ位置のY座標
const int Width = 1024;    //生成するウィンドウの幅
const int Height = 576;    //生成するウィンドウの高さ

void Ground(void) {
	double max_x = 300.0;//x軸地面の最大値
	double max_y = 300.0;//y軸地面の最大値
	glColor3d(0.8, 0.8, 0.8);  //地面の色(RGB)
	glBegin(GL_LINES);
	//for(y軸地面の最大値まで20(線の幅)ごとに繰り返す
	for (double ly = -max_y; ly <= max_y; ly += 20.0) {
		glVertex3d(-max_x, ly, 0);//頂点を追加
		glVertex3d(max_x, ly, 0);
	}
	for (double lx = -max_x; lx <= max_x; lx += 20.0) {
		glVertex3d(lx, max_y, 0);
		glVertex3d(lx, -max_y, 0);
	}
	//glEnd();//これがないとエラーになる
}

/// <summary>
/// 初期化
/// </summary>
void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //背景色
	glEnable(GL_DEPTH_TEST);

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
	

	Ground();//地面を描画
	glEnd();//これがないとエラーになる

	glutSwapBuffers(); 
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);//環境の初期化

	glutInitWindowPosition(PosX, PosY);//ウィンドウの表示位置
	glutInitWindowSize(Width, Height); //ウィンドウサイズ

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定

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