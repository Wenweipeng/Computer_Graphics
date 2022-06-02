#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 800, 0, 600);
}

inline int round(const float a) {
	return int(a + 0.5);
}

void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void lineDDA(int x0, int y0, int xEnd, int yEnd) {
	int dx = xEnd - x0, dy = yEnd - y0, steps, k;
	float xIncrement, yIncrement, x = x0, y = y0;

	if (fabs(dx) > fabs(dy)) {
		steps = fabs(dx);
	}
	else {
		steps = fabs(dy);
	}
	xIncrement = float(dx) / float(steps);
	yIncrement = float(dy) / float(steps);

	setPixel(round(x), round(y));
	for (k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		setPixel(round(x), round(y));
	}
}

void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	int x0, y0, xEnd, yEnd;
	printf("请输入第一个点的坐标:\n");
	scanf("%d%d", &x0, &xEnd);
	printf("请输入第二个点的坐标:\n");
	scanf("%d%d", &y0, &yEnd);
	lineDDA(x0, y0, xEnd, yEnd);
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("DDA直线生成算法");
	glutDisplayFunc(&lineSegment);
	init();
	glutMainLoop();
}