#include<GL/freeglut.h>

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // black clear color, opaque window
	glColor3f(1.0, 0.0, 1.0); // white
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // screen size (-1.0,-1.0) to (1.0,1.0)
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window

	glBegin(GL_POLYGON); // fill connected polygon
	glVertex2f(-0.5, -0.5); // vertices of the square
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.0, -0.5);
	glEnd();

	glColor3f(1.0, 1.0, 1.0); // white
	glBegin(GL_POLYGON); // fill connected polygon
	glVertex2f(0.1, 0.5); // vertices of the square
	glVertex2f(0.1, -0.5);
	glVertex2f(0.6, 0.5);
	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

	int sc_width = desktop.right;
	int sc_height = desktop.bottom;

	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// actual window size
	glutInitWindowSize(500, 500);
	// initial window location, top-left corner
	glutInitWindowPosition(sc_width / 2 - 250, sc_height / 2 - 250);
	// create window with title °∞simple°±
	glutCreateWindow("19011460_¿Ã¿Ø¿Á_HW_1");
	// call mydisplay() function
	glutDisplayFunc(mydisplay);
	// call init() function
	init();
	// main event loop, do not use exit()
	glutMainLoop();
}