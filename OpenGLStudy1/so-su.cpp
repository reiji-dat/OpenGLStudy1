#include <GL/glut.h>
#include <stdio.h>
/*
* ���낻�낱���ɒn�ʐ����╨�̐�����ʂ̃N���X�ɂ��Ă��������B
*/

#define KEY_ESC 27

const int PosX = 100;  //��������E�B���h�E�ʒu��X���W
const int PosY = 100;  //��������E�B���h�E�ʒu��Y���W
const int Width = 1024;    //��������E�B���h�E�̕�
const int Height = 576;    //��������E�B���h�E�̍���
float camPosX = -100;

int face[][4] = {//�ʂ̒�`
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 }
};

GLdouble normal[][3] = {//�ʂ̖@���x�N�g��
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};

// ���������̒�`
struct Material {		//struct�̌�̖��O�͎��R�ɕς�����
	GLfloat ambient[4];	//�����ɑ΂��锽�ˌW��
	GLfloat diffuse[4];	//���̐F
	GLfloat specular[4];//�n�C���C�g�̋���
	GLfloat shininess;	//�n�C���C�g�̑傫��
};

int btime = 0;
int ttltime = 0;
int flame;
void FPS() {
	flame++;
	int time = glutGet(GLUT_ELAPSED_TIME);
	//printf("1�t���[��0.00%d�b\n", time - btime);
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

	glColor3d(0.8, 0.8, 0.8);  //�n�ʂ̐F(RGB)

	//glBegin�֐��ɂ���(http://wisdom.sakura.ne.jp/system/opengl/gl3.html)
	glBegin(GL_LINES);//2�̒��_���y�A�Ƃ��A���ꂼ��̃y�A��Ɨ����������Ƃ��Ĉ����B
	//for(y���n�ʂ̍ő�l�܂�20(���̕�)���ƂɌJ��Ԃ�
	for (float lz = -z; lz <= z; lz += wid) {
		glVertex3d(-x, 0, lz);//���_�̎n�_
		glVertex3d(x, 0, lz);//���_�̏I�_(�������ł��Ă����)
	}
	for (float lx = -x; lx <= x; lx += wid) {
		glVertex3d(lx, 0, z);
		glVertex3d(lx, 0, -z);
	}
	glEnd();//���������������I������
}

void CreateSphere(float r, float g, float b,float x, float y, float z,float s)
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

/// <summary>
/// Key���͎��ɌĂяo�����
/// </summary>
/// <param name="key">���̓L�[�̎��</param>
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
/// �A�C�h�����ɌĂяo�����֐��B�ĕ`�悷�鏈�������Ă���B
/// </summary>
void Idle() {
	FPS();
	glutPostRedisplay();//�ĕ`�悷��
}

/// <summary>
/// ������
/// </summary>
void Init() {
	//printf("��������\n");
	glClearColor(1.0, 1.0, 1.0, 1.0); //�w�i�F
	glEnable(GL_DEPTH_TEST);//�f�B�[�v�e�X�g�𖳌���

	//������ݒ�
	GLfloat light_position0[] = { 20.0, 50.0, 50.0, 1.0 }; //�����̍��W
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0); //������ݒu

}

/// <summary>
/// �����ɕ`�悳���������̂�`��
/// </summary>
void Display() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);//�s�񃂁[�h�̐ݒ�iGL_PROJECTION : �����ϊ��s��̐ݒ�AGL_MODELVIEW�F���f���r���[�ϊ��s��j
	glLoadIdentity();//�s��̏�����

	//gluPerspective(����p, �����c, �`�悳���ł�����, �`�悳���ł���������);
	gluPerspective(30.0, (double)Width / (double)Height, 0.1, 1000.0); //�����}�@

	gluLookAt(
		camPosX, 50, 200, // ���_�̈ʒux,y,z;(���A�����A���s)
		camPosX, 20, 00,   // ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z(�ǂ��̍��W����ʂ̐^�񒆂ɗ���̂�)
		0.0, 1.0, 0.0);  //�ǂ��̍��W����ʂ̏�ɗ���̂�(���̏ꍇ+z������ʂ̏�)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//������
	glViewport(0, 0, Width, Height);//�E�B���h�E�̕`��͈�

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	CreateSphere(1, 0, 0, 0, 0, 0, 10);
	CreateCube(0, 1, 0, 20, 0, 0, 10);
	CreateCone(0, 0, 1, -20, 0, 0, 10, 20);
	CreateBox(0, 1, 1, 20, 20, -20, 20, 30, 10);
	CreateCube(0.5, 0.5, 0.5, 50.0, 50.0, 20.0, 3);
	
	glDisable(GL_LIGHTING);

	Ground(300.0f,300.f,20.0f);//�n�ʂ�`��

	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);//���̏�����

	glutInitWindowPosition(PosX, PosY);//�E�B���h�E�̕\���ʒu
	glutInitWindowSize(Width, Height); //�E�B���h�E�T�C�Y
	glutCreateWindow("�E�B���h�E�̃^�C�g��");  //�E�B���h�E�̍쐬�A�^�C�g�������߂�

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//�f�B�X�v���C���[�h�̎w��

	glutDisplayFunc(Display); //Display�֐��ɕ`����Ă�����̂�`�悷��
	glutKeyboardFunc(InputKey);//�P�[���͎���InputKey���Ă�
	glutIdleFunc(Idle);//�A�C�h������Idle�֐����Ă�
	Init(); //������
	glutMainLoop();
	return 0;
}