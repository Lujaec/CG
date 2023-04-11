#include<GL/glut.h>

int mouseCurButton = 0;
int mouseCurPositionX = 0, mouseCurPositionY = 0;
int mousePrePositionX = 0, mousePrePositionY = 0;

void init() {
	glClearColor(1.0, 1.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	glBegin(GL_POLYGON); // fill connected polygon
	glVertex2f(-2.5, -2.5); // vertices of the square
	glVertex2f(-2.5, 2.5);
	glVertex2f(2.5, 2.5);
	glVertex2f(2.5, -2.5);
	glEnd();

	glBegin(GL_POLYGON); // fill connected polygon
	glVertex2f(-7.5, -2.5); // vertices of the square
	glVertex2f(-4.5, -2.5);
	glVertex2f(-7.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON); // fill connected polygon
	glVertex2f(4, 8); // vertices of the square                            
	glVertex2f(6, 6);
	glVertex2f(6, 4);
	glVertex2f(4, 2);
	glVertex2f(2, 4);
	glVertex2f(2, 6);
	glEnd();
	glFlush();
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON &&
		state == GLUT_DOWN) {
		
		if(x <= 250)
			glColor3f(0, 0, 1.0);
		else
			glColor3f(1.0, 0, 0);
	}
	else if(button == GLUT_RIGHT_BUTTON &&
		state == GLUT_DOWN){
		
		if (y <= 250)
			glColor3f(1.0, 1.0, 1.0);
		else
			glColor3f(0, 0, 0);
	}

	if (state == GLUT_DOWN) {
		mouseCurButton = GLUT_DOWN;
		mouseCurPositionX = x;
		mouseCurPositionY = y;
	}
	else if (state == GLUT_UP) {
		mouseCurButton = GLUT_UP;
	}

	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	


	if (mouseCurButton == GLUT_DOWN) {
		mousePrePositionX = mouseCurPositionX;
		mousePrePositionY = mouseCurPositionY;

		mouseCurPositionX = x;
		mouseCurPositionY = y;

		int diff = mouseCurPositionX - mousePrePositionX;

		if (diff > 0)
			glColor3f(1.0, 0, 0);
		else if(diff < 0)
			glColor3f(0, 1.0, 0);


		glutPostRedisplay();

	}
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);							//항상 필요
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//프레임버퍼의 모드를 설정, SINGLE => 프레임 버퍼 하나를 사용

	glutInitWindowSize(500, 500);					//
	glutInitWindowPosition(0, 0);
	glutCreateWindow("19011460 이유재");
	glutDisplayFunc(mydisplay);
	init();
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotion);
	glutMainLoop();
}
