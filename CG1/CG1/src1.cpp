//#include<GL/glut.h>
//
//void init() {
//	glClearColor(0.0, 0.0, 0.0, 1.0);
//	glColor3f(1.0, 1.0, 1.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
//}
//
//void mydisplay()
//{
//	glClear(GL_COLOR_BUFFER_BIT); // clear the window
//	glBegin(GL_POLYGON); // fill connected polygon
//	glVertex2f(-0.5, -0.5); // vertices of the square
//	glVertex2f(-0.5, 0.5);
//	glVertex2f(0.5, 0.5);
//	glVertex2f(0.5, -0.5);
//	glEnd();
//	glFlush();
//}
//
//int main(int argc, char ** argv){
//	glutInit(&argc, argv);							//항상 필요
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//프레임버퍼의 모드를 설정, SINGLE => 프레임 버퍼 하나를 사용
//
//	glutInitWindowSize(500, 500);					//
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow("simple");
//	glutDisplayFunc(mydisplay);
//	init();
//	glutMainLoop();
//}
