//#include<GL/glut.h>
//#include<iostream>
//#include<cmath>
//int width = 700, height = 700;
//
//GLdouble fov = 80;
//GLboolean redisplay = false;
//
//GLdouble centerOfObject[4][3] = {
//	{1, 0.1, 0.1},
//	{0.2, 0.5, 0.3},
//	{0.3, 0.2, 0},
//	{0.4, -0.7, -0.8}
//};
//
//GLdouble dir[3] = { 0 };
//GLdouble unitVector[3] = { 0 };
//
//GLfloat color[4][3] = {
//	{1, 0, 0},
//	{0, 0, 1},
//	{1, 1, 0},
//	{0, 1, 0}
//};
//
//GLfloat angle = 0.0f;
//
//int mouseCurButton = GLUT_LEFT_BUTTON;
//int mouseCurPositionX, mouseCurPositionY;
//
//void init() {
//	glClearColor(0.0, 0.0, 0.0, 1.0);
//	glColor3f(1.0, 1.0, 1.0);
//
//
//
//
//	glEnable(GL_DEPTH_TEST);
//
//}
//
//void drawCoordinate() {
//	glPushMatrix();
//	int range = 30;
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glColor3f(1, 1, 1);
//	glBegin(GL_LINE_LOOP);
//	glVertex3f(range, 0, 0);
//	glVertex3f(-range, 0, 0);
//	glEnd();
//
//	glBegin(GL_LINE_LOOP);
//	glVertex3f(0, range, 0);
//	glVertex3f(0, -range, 0);
//	glEnd();
//
//	glColor3f(1, 1, 1);
//	glBegin(GL_LINE_LOOP);
//	glVertex3f(0, 0, range);
//	glVertex3f(0, 0, -range);
//	glEnd();
//
//	glPopMatrix();
//}
//
//void drawCube(double size, GLfloat c[3]) {
//	glPushMatrix();
//	glColor3f(c[0], c[1], c[2]);
//	glutSolidCube(size);
//	glPopMatrix();
//}
//
//void drawSphere(double radius, GLfloat c[3]) {
//	glPushMatrix();
//	glColor3f(c[0], c[1], c[2]);
//	glutWireSphere(radius, 100, 50);
//	glPopMatrix();
//
//}
//
//void display()
//{
//	double size[2] = { 0.15, 0.3 }, radius[2] = { 0.2, 0.1 };
//
//	/* clear the screen*/
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(fov, 1, 0.01, 5);
//	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
//
//	glutSolidTorus(0.275, 0.85, 15, 15);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//
//
//	drawCoordinate();
//
//	glRotatef(angle, 0, 0, 1);
//	for (int i = 0; i < 2; i++) {
//		glPushMatrix();
//		glTranslatef(centerOfObject[i][0], centerOfObject[i][1], centerOfObject[i][2]);
//		drawCube(size[i], color[i]);
//		glPopMatrix();
//	}
//	for (int i = 2; i < 4; i++) {
//		glPushMatrix();
//		glTranslatef(centerOfObject[i][0], centerOfObject[i][1], centerOfObject[i][2]);
//		drawSphere(radius[i - 2], color[i]);
//		glPopMatrix();
//	}
//
//	glFlush();
//}
//
//void pointToVector(GLdouble s[3], GLdouble e[3]) {
//	dir[0] = e[0] - s[0];
//	dir[1] = e[1] - s[1];
//	dir[2] = e[2] - s[2];
//
//}
//
//void normalizeVector(GLdouble* vector) {
//	double len = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
//
//	unitVector[0] = vector[0] / len;
//	unitVector[1] = vector[1] / len;
//	unitVector[2] = vector[2] / len;
//}
//
//
//void moveCenterOfObject(GLdouble* centerOfObject, GLdouble vector[3], GLdouble velocity) {
//	for (int i = 0; i < 3; ++i)
//		centerOfObject[i] += vector[i] * velocity;
//}
//
//void mouseFunc(int button, int state, int x, int y) {
//	if (button == GLUT_LEFT_BUTTON &&
//		state == GLUT_DOWN) {
//
//		if (x <= width / 2) {
//			angle -= 10;
//		}
//		else {
//			angle += 10;
//		}
//	}
//
//	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
//		GLint viewport[4] = { 0 };
//		GLdouble modelview[16] = { 0 };
//		GLdouble projection[16] = { 0 };
//		GLfloat winX, winY, winZ;
//		GLdouble posX, posY, posZ, nPosX, nPosY, nPosZ, fPosX, fPosY, fPosZ;
//
//		// 뷰포트, 프로젝션 행렬, 모델뷰 행렬 설정
//		glGetIntegerv(GL_VIEWPORT, viewport);
//		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
//		glGetDoublev(GL_PROJECTION_MATRIX, projection);
//
//		// 스크린 좌표계의 마우스 좌표값을 변환
//		winX = (float)x;
//		winY = (float)viewport[3] - (float)y;
//		glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
//		std::cout << winZ << std::endl;
//		gluUnProject(winX, winY, 0, modelview, projection, viewport, &nPosX, &nPosY, &nPosZ);
//		gluUnProject(winX, winY, 1, modelview, projection, viewport, &fPosX, &fPosY, &fPosZ);
//
//		posX = (nPosX + fPosX) / 2;
//		posY = (nPosY + fPosY) / 2;
//		posZ = (nPosZ + fPosZ) / 2;
//
//		GLdouble velocity = 0.1;
//		GLdouble pointer[3] = { posX, posY, posZ };
//
//		for (int i = 0; i < 4; ++i) {
//			pointToVector(centerOfObject[i], pointer);
//			normalizeVector(dir);
//			moveCenterOfObject(centerOfObject[i], unitVector, velocity);
//		}
//	}
//	else if (button == GLUT_RIGHT_BUTTON) {
//		if (state == GLUT_DOWN) {
//			mouseCurButton = GLUT_RIGHT_BUTTON;
//			mouseCurPositionX = x;
//			mouseCurPositionY = y;
//		}
//		else if (state == GLUT_UP) {
//			mouseCurButton = GLUT_LEFT_BUTTON;
//
//		}
//
//	}
//
//	glutPostRedisplay();
//}
//
//void mouseMotionFunc(int x, int y) {
//
//	if (mouseCurButton == GLUT_RIGHT_BUTTON) {
//		int dx = x - mouseCurPositionX;
//		int dy = y - mouseCurPositionY;
//
//		mouseCurPositionX = x;
//		mouseCurPositionY = y;
//
//		if (dx > 0 && dy > 0) {
//
//
//			fov -= 0.5;
//			if (fov < 10.0f) {
//				fov = 10.0f; // 시야각의 최소값
//			}
//		}
//		else if (dx < 0 && dy < 0) {
//
//			fov += 0.5;
//			if (fov > 120.0f) {
//				fov = 120.0f; // 시야각의 최대값
//			}
//		}
//
//		glutPostRedisplay();
//	}
//}
//
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);							//항상 필요
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(width, height);
//	glutInitWindowPosition(200, 200);
//	glutCreateWindow("Coordinates");
//	init();
//	glutDisplayFunc(display);
//	glutMouseFunc(mouseFunc);
//	glutMotionFunc(mouseMotionFunc);
//	glutMainLoop();
//}