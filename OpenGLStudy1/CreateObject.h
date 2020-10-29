#pragma once
#include <GL/glut.h>
class CreateObject
{
	struct Material {		//structの後の名前は自由に変えられる
		GLfloat ambient[4];	//環境光に対する反射係数
		GLfloat diffuse[4];	//元の色
		GLfloat specular[4];//ハイライトの強さ
		GLfloat shininess;	//ハイライトの大きさ
	};

	int face[][4];

	void CreateSphere(float r, float g, float b, float x, float y, float z, float s);

	void CreateCube(float r, float g, float b, float x, float y, float z, float s);

	void CreateCone(float r, float g, float b, float x, float y, float z, float rad, float high);

	void CreateBox(float r, float g, float b, float x, float y, float z, float width, float depth, float height);
};

// 物質質感の定義
struct Material {		//structの後の名前は自由に変えられる
	GLfloat ambient[4];	//環境光に対する反射係数
	GLfloat diffuse[4];	//元の色
	GLfloat specular[4];//ハイライトの強さ
	GLfloat shininess;	//ハイライトの大きさ
};

int face[][4] = {//面の定義
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 }
};

void CreateSphere(float r, float g, float b, float x, float y, float z, float s)
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

