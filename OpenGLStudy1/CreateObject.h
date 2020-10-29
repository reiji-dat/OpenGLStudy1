#pragma once
#include <GL/glut.h>
class CreateObject
{
	struct Material {		//struct�̌�̖��O�͎��R�ɕς�����
		GLfloat ambient[4];	//�����ɑ΂��锽�ˌW��
		GLfloat diffuse[4];	//���̐F
		GLfloat specular[4];//�n�C���C�g�̋���
		GLfloat shininess;	//�n�C���C�g�̑傫��
	};

	int face[][4];

	void CreateSphere(float r, float g, float b, float x, float y, float z, float s);

	void CreateCube(float r, float g, float b, float x, float y, float z, float s);

	void CreateCone(float r, float g, float b, float x, float y, float z, float rad, float high);

	void CreateBox(float r, float g, float b, float x, float y, float z, float width, float depth, float height);
};

// ���������̒�`
struct Material {		//struct�̌�̖��O�͎��R�ɕς�����
	GLfloat ambient[4];	//�����ɑ΂��锽�ˌW��
	GLfloat diffuse[4];	//���̐F
	GLfloat specular[4];//�n�C���C�g�̋���
	GLfloat shininess;	//�n�C���C�g�̑傫��
};

int face[][4] = {//�ʂ̒�`
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
	{r * 0.28,   g * 0.28,  b * 0.28,   1.0},//�e
	{r,  g,  b,   1.0},//��
	{0.8 + r * r * 0.14, 0.8 + g * g * 0.14, 0.8 + b * b * 0.14,  1.0},//�n�C���C�g
	76.8 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, metallic.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metallic.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metallic.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &metallic.shininess);
	glTranslated(x, y, z);//�ʒu(��,����,���s)
	glutSolidSphere(s, 20, 20);//(���a, Z���܂��̕�����, Z���ɉ�����������)
	glPopMatrix();
}

void CreateCube(float r, float g, float b, float x, float y, float z, float s)
{
	Material metallic = {
	{r * 0.28,   g * 0.28,  b * 0.28,   1.0},//�e
	{r,  g,  b,   1.0},//��
	{0.8 + r * r * 0.14, 0.8 + g * g * 0.14, 0.8 + b * b * 0.14,  1.0},//�n�C���C�g
	76.8 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, metallic.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metallic.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metallic.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &metallic.shininess);
	glTranslated(x, y, z);
	glutSolidCube(s);//(��ӂ̒���)
	glPopMatrix();
}

void CreateCone(float r, float g, float b, float x, float y, float z, float rad, float high)
{
	Material metallic = {
	{r * 0.28,   g * 0.28,  b * 0.28,   1.0},//�e
	{r,  g,  b,   1.0},//��
	{0.8 + r * r * 0.14, 0.8 + g * g * 0.14, 0.8 + b * b * 0.14,  1.0},//�n�C���C�g
	76.8 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, metallic.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metallic.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metallic.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &metallic.shininess);
	glTranslated(x, y, z);//�ʒu(��,����,���s)
	glRotated(90, -1, 0, 0);
	glutSolidCone(rad, high, 20, 20);//(���a, ����, Z���܂��̕�����, Z���ɉ�����������)
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
	{r * 0.28,   g * 0.28,  b * 0.28,   1.0},//�e
	{r,  g,  b,   1.0},//��
	{0.8 + r * r * 0.14, 0.8 + g * g * 0.14, 0.8 + b * b * 0.14,  1.0},//�n�C���C�g
	76.8 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, metallic.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, metallic.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, metallic.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &metallic.shininess);
	glTranslated(x, y, z);//���s�ړ��l�̐ݒ�
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(ver[face[j][i]]);
		}
	}
	glEnd();
	glPopMatrix();//���ꂪ�Ȃ��Ǝn�_���ύX�����B
}

