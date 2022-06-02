#include <GL/glut.h>
#include <cstdio>
#define LEFT 1//0001
#define RIGHT 2//0010
#define BOTTOM 4//0100
#define TOP 8//1000
int x1 = 150, y1 = 50, x2 = 50, y2 = 250, XL = 100, XR = 300, YB = 100, YT = 200;  //(x1,y1)��(x2,y2)Ϊֱ�߶εĶ˵㣬XLΪ��߽磬XRΪ�ұ߽磬YBΪ�±߽磬YTΪ�ϱ߽�
int x1_init = 150, y1_init = 50, x2_init = 50, y2_init = 250;  //��ֱ�߶ζ˵㱸�ݣ��Ա㻭���ü�ǰ��ֱ�߶�
void encode(int x, int y, int& c)
{//|������������һ��Ϊ1�����Ϊ1
	c = 0;
	if (x < XL) c |= LEFT;//�������ֽ��л����㣬��߽�
	else if (x > XR) c |= RIGHT;//�ұ߽�
	if (y < YB) c |= BOTTOM;//�±߽�
	else if (y > YT) c |= TOP;//�ϱ߽�
}
//����:1001; ����:0001; ����:0101;
//����:1000; ����:0000 ����:0100
//����:1010  ����:0010  ����:0110
void CS_LineClip()  //Cohen-Sutherland�ü��㷨
{
	int x, y;
	int code1, code2, code;
	encode(x1, y1, code1);//������˵����ڵ�����
	encode(x2, y2, code2);//������˵����ڵ�����
	//ѭ������
	while (code1 != 0 || code2 != 0)//ֻ�������˵�ͬʱ���ھ���������Ų�ʹ�ú���
	{
		if (code1 & code2)//������Ϊ1�ų���������������ͬһ�������� ֱ�Ӳ����д���
			return;
		if (code1 != 0)//���
			code = code1;
		else
			code = code2;

		if (LEFT & code)//�߶�����߽��ཻ(���
		{
			x = XL;//�������߽�Ľ����xֵ
			y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);//�����߽����yֵ
		}
		else if (RIGHT & code)//�߶����ұ߽��ཻ
		{
			x = XR;//����ұ߽�Ľ����xֵ
			y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);//����б�ʼ�����ұ߽�Ľ����yֵ
		}
		else if (BOTTOM & code)//�߶����±߽��ཻ
		{
			y = YB;//����±߽�Ľ����yֵ
			x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);//����±߽�Ľ����xֵ����б��
		}
		else if (TOP & code)//�߶����ϱ߽��ཻ
		{
			y = YT;
			x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
		}
		if (code == code1)
		{
			x1 = x; y1 = y;  encode(x1, y1, code1);//������ ��Ķ˵㸲�ǵ�
		}
		else
		{
			x2 = x; y2 = y; encode(x2, y2, code2);//������ ��Ķ˵㸲�ǵ�
		}
	}
}
void mydisplay()  //��ʾ����
{
	//���Ʒ��α߽�
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);//���ñ�����ɫ
	glPointSize(2);//���õ�Ĵ�С
	glBegin(GL_LINE_LOOP);//��������Ĳ���
	glVertex2i(XL, YT);//���ƾ���
	glVertex2i(XL, YB);
	glVertex2i(XR, YB);
	glVertex2i(XR, YT);
	glEnd();
	glFlush();
	//����δ�ü�ǰ���߶�
	glBegin(GL_LINES);//����ֱ�ߵĲ���
	glVertex2i(x1_init, y1_init);
	glVertex2i(x2_init, y2_init);
	glEnd();
	glFlush();
	//���Ʋü�����߶�
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glFlush();
	//���Ƽ����������ֱ�߶�
	x1_init = 400, y1_init = 50, x2_init = 300, y2_init = 250;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x1_init, y1_init);
	glVertex2i(x2_init, y2_init);
	glEnd();
	glFlush();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 100);//����λ��
	glutInitWindowSize(500, 400);
	glutCreateWindow("Cohen-Sutherland�ü��㷨");
	glClearColor(1.0, 1.0, 1.0, 0.0);  //���ñ�����ɫ
	glMatrixMode(GL_PROJECTION);       // ����ͶӰ����
	gluOrtho2D(0.0, 600.0, 0.0, 400.0); // ���ó����Ĵ�С
	CS_LineClip();  //ִ��һ�βü��㷨
	glutDisplayFunc(&mydisplay);//���û��ƺ���
	glutMainLoop();
	return 0;
}