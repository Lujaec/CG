#include<GL/glut.h>

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(20, 1, 0.0001, 100);
	gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
}

void drawCoordinate() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(7, 0, 0);
	glVertex3f(-7, 0, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 7, 0);
	glVertex3f(0, -7, 0);
	glEnd();

	glColor3f(0.7, 0.4, 0.5);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 7);
	glVertex3f(0, 0, -7);
	glEnd();
}

void drawCube(GLfloat offset[3], GLfloat color[3]) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(offset[0], offset[1], offset[2]);
	glColor3f(color[0], color[1], color[2]);
	
	glutWireCube(0.1);
}

void drawSphere(GLfloat offset[3], GLfloat color[3]) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(offset[0], offset[1], offset[2]);
	glColor3f(color[0], color[1], color[2]);
}




void display()
{
	/* clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT);
	
	GLfloat offset[3], color[3];

	offset[0] = -1;
	offset[1] = -1;
	offset[2] = -1;

	color[0] = 1;
	color[1] = 0;
	color[2] = 0;
	
	drawCoordinate();
	drawCube(offset, color);
	glFlush();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);							//항상 필요
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Coordinates");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
