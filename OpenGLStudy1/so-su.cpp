#include <GL/glut.h>

const int PosX = 100;  //��������E�B���h�E�ʒu��X���W
const int PosY = 100;  //��������E�B���h�E�ʒu��Y���W
const int Width = 1024;    //��������E�B���h�E�̕�
const int Height = 576;    //��������E�B���h�E�̍���

void Ground(void) {
	double max_x = 300.0;//x���n�ʂ̍ő�l
	double max_y = 300.0;//y���n�ʂ̍ő�l
	glColor3d(0.8, 0.8, 0.8);  //�n�ʂ̐F(RGB)
	glBegin(GL_LINES);
	//for(y���n�ʂ̍ő�l�܂�20(���̕�)���ƂɌJ��Ԃ�
	for (double ly = -max_y; ly <= max_y; ly += 20.0) {
		glVertex3d(-max_x, ly, 0);//���_��ǉ�
		glVertex3d(max_x, ly, 0);
	}
	for (double lx = -max_x; lx <= max_x; lx += 20.0) {
		glVertex3d(lx, max_y, 0);
		glVertex3d(lx, -max_y, 0);
	}
	//glEnd();//���ꂪ�Ȃ��ƃG���[�ɂȂ�
}

/// <summary>
/// ������
/// </summary>
void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //�w�i�F
	glEnable(GL_DEPTH_TEST);

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
	

	Ground();//�n�ʂ�`��
	glEnd();//���ꂪ�Ȃ��ƃG���[�ɂȂ�

	glutSwapBuffers(); 
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);//���̏�����

	glutInitWindowPosition(PosX, PosY);//�E�B���h�E�̕\���ʒu
	glutInitWindowSize(Width, Height); //�E�B���h�E�T�C�Y

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//�f�B�X�v���C���[�h�̎w��

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