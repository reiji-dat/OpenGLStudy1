#include <GL/glut.h>

const int PosX = 100;  //��������E�B���h�E�ʒu��X���W
const int PosY = 100;  //��������E�B���h�E�ʒu��Y���W
const int Width = 1024;    //��������E�B���h�E�̕�
const int Height = 576;    //��������E�B���h�E�̍���

int face[][4] = {//�ʂ̒�`
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 }
};

void Ground(float x,float y,float wid) {

	glColor3d(0.8, 0.8, 0.8);  //�n�ʂ̐F(RGB)

	//glBegin�֐��ɂ���(http://wisdom.sakura.ne.jp/system/opengl/gl3.html)
	glBegin(GL_LINES);//2�̒��_���y�A�Ƃ��A���ꂼ��̃y�A��Ɨ����������Ƃ��Ĉ����B
	//for(y���n�ʂ̍ő�l�܂�20(���̕�)���ƂɌJ��Ԃ�
	for (float ly = -y; ly <= y; ly += wid) {
		glVertex3d(-x, ly, 0);//���_�̎n�_
		glVertex3d(x, ly, 0);//���_�̏I�_(�������ł��Ă����)
	}
	for (float lx = -x; lx <= x; lx += wid) {
		glVertex3d(lx, y, 0);
		glVertex3d(lx, -y, 0);
	}
	glEnd();//���������������I������
}

/// <summary>
/// ���̂𐶐�
/// </summary>
/// <param name="r">��</param>
/// <param name="g">��</param>
/// <param name="b">��</param>
/// <param name="x">��</param>
/// <param name="y">���s</param>
/// <param name="z">����</param>
/// <param name="s">�傫��</param>
void CreateSphere(float r, float g, float b,float x, float y, float z,float s)
{
	glPushMatrix();
	glColor3d(r, g, b); //�F
	glTranslated(x, y, z);//�ʒu(��,���s,����)
	glutSolidSphere(s, 20, 20);//(���a, Z���܂��̕�����, Z���ɉ�����������)
	glPopMatrix();
}

/// <summary>
/// �����̂𐶐�
/// </summary>
/// <param name="r">��</param>
/// <param name="g">��</param>
/// <param name="b">��</param>
/// <param name="x">��</param>
/// <param name="y">���s</param>
/// <param name="z">����</param>
/// <param name="s">�傫��</param>
void CreateCube(float r, float g, float b, float x, float y, float z, float s)
{
	glPushMatrix();
	glColor3d(r, g, b);
	glTranslated(x, y, z);
	glutSolidCube(s);//(��ӂ̒���)
	glPopMatrix();
}

/// <summary>
/// �~���𐶐�
/// </summary>
/// <param name="r">��</param>
/// <param name="g">��</param>
/// <param name="b">��</param>
/// <param name="x">��</param>
/// <param name="y">���s</param>
/// <param name="z">����</param>
/// <param name="rad">���a</param>
/// <param name="high">����</param>
void CreateCone(float r, float g, float b, float x, float y, float z, float rad, float high)
{
	glPushMatrix();
	glColor3d(r, g, b);//�F
	glTranslated(x, y, z);//�ʒu(��,���s,����)
	glutSolidCone(rad, high, 20, 20);//(���a, ����, Z���܂��̕�����, Z���ɉ�����������)
	glPopMatrix();
}

/// <summary>
/// �����̂𐶐�
/// </summary>
/// <param name="r">��</param>
/// <param name="g">��</param>
/// <param name="b">��</param>
/// <param name="x">��</param>
/// <param name="y">���s</param>
/// <param name="z">����</param>
/// <param name="width">���̒���</param>
/// <param name="depth">�c�̒���</param>
/// <param name="height">�����̒���</param>
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
	//������
	glPushMatrix();
	glColor3d(r, g, b);//�F�̐ݒ�
	glTranslated(x, y, z);//���s�ړ��l�̐ݒ�
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(ver[face[j][i]]);
		}
	}
	glEnd();
}

/// <summary>
/// ������
/// </summary>
void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //�w�i�F
	glEnable(GL_DEPTH_TEST);//�f�B�[�v�e�X�g�𖳌���

	//�������牺�͒n�ʂ̕`��֌W
	glMatrixMode(GL_PROJECTION);//�s�񃂁[�h�̐ݒ�iGL_PROJECTION : �����ϊ��s��̐ݒ�AGL_MODELVIEW�F���f���r���[�ϊ��s��j
	glLoadIdentity();//�s��̏�����

	//gluPerspective(����p, �����c, �`�悳���ł�����, �`�悳���ł���������);
	gluPerspective(30.0, (double)Width / (double)Height, 0.1, 1000.0); //�����}�@

	gluLookAt(
		0.0, -200.0, 50.0, // ���_�̈ʒux,y,z;(���A���s���A����)
		0.0, 0.0, 20,   // ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z(�ǂ��̍��W����ʂ̐^�񒆂ɗ���̂�)
		0.0, 0.0, 1.0);  //�ǂ��̍��W����ʂ̏�ɗ���̂�(���̏ꍇ+z������ʂ̏�)
}

/// <summary>
/// �����ɕ`�悳���������̂�`��
/// </summary>
void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CreateSphere(1, 0, 0, 0, 0, 0, 10);

	CreateCube(0, 1, 0, 20, 0, 0, 10);

	CreateCone(0, 0, 1, -20, 0, 0, 10, 20);

	CreateBox(0, 1, 1, 0, -20, 20, 20, 10, 30);

	//�������������l��ς����牺�����ɂȂ���
	/*
		GL_MODELVIEW	���f���r���[�s��
		GL_PROJECTION	�ˉe�s��
		GL_TEXTURE	�e�N�X�`���s��
		�̎O��ނ�����炵��
	*/
	//��Œ��ׂ�
	glMatrixMode(GL_MODELVIEW);//�s�񃂁[�h�̐ݒ�

	//�����Ă����삵��
	//��Œ��ׂ�
	glLoadIdentity();//�s��̏�����

	//���̐��l�̑��삵����`�悳������ς��
	//��ʂɍ��킹�ĕ`�悷��ݒ�Ɛ���
	glViewport(0, 0, Width, Height);
	
	Ground(300.0f,300.f,20.0f);//�n�ʂ�`��

	glutSwapBuffers();//���ׂ����ǂ悭������Ȃ��Ƃ肠�����K�v�Ȃ���(?)
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);//���̏�����

	glutInitWindowPosition(PosX, PosY);//�E�B���h�E�̕\���ʒu
	glutInitWindowSize(Width, Height); //�E�B���h�E�T�C�Y

	//�f�B�X�v���C���[�h�̎w��
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//Default:GLUT_RGBA | GLUT_SINGLE

	glutCreateWindow("�E�B���h�E�̃^�C�g��");  //�E�B���h�E�̍쐬�A�^�C�g�������߂�
	glutDisplayFunc(Display); //Display�֐��ɕ`����Ă�����̂�`�悷��

	Init(); //������

	/*
	* �������R�����g�A�E�g����ƈ�u�����\�����ꂽ
	* �����炭�\���������鏈�����Ɛ�������
	*/
	glutMainLoop();

	return 0;
}