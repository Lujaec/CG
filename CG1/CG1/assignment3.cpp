#include<GL/glut.h>
#include<iostream>
#include<cmath>
int width = 700, height = 700;

GLdouble zoom = 100;
GLboolean redisplay = false;

GLdouble centerOfObject[4][3] = {
	{0.1, 0.1, 0.1},
	{0.2, 0.5, 0.3},
	{0, 0, 0},
	{0, 0, 0}
};

GLfloat color[4][3] = {
	{1, 0, 0},
	{0, 0, 1},
	{1, 1, 0},
	{0, 1, 0}
};

GLfloat angle = 0.0f;


void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(zoom, 1, 0.0001, 100);
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
}

void drawCoordinate() {
	
	glPushMatrix();
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
	glPopMatrix();
}

void drawCube(GLfloat c[3]) {
	glPushMatrix();
	glColor3f(c[0], c[1], c[2]);
	glutWireCube(0.1);
	glPopMatrix();
}

void drawSphere(GLfloat offset[3], GLfloat c[3]) {
	glPushMatrix();
	glColor3f(c[0], c[1], c[2]);
	glPopMatrix();

}

void display()
{
	/* clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawCoordinate();

	if (redisplay) {
		for (int i = 0; i < 2; i++) {

			glPushMatrix();
			glRotatef(angle, 0, 0, 1);
			glTranslatef(centerOfObject[i][0], centerOfObject[i][1], centerOfObject[i][2]);
			drawCube(color[i]);
			glPopMatrix();
		}
	}
	else {
		for (int i = 0; i < 2; i++) {

			glPushMatrix();
			glTranslatef(centerOfObject[i][0], centerOfObject[i][1], centerOfObject[i][2]);
			drawCube(color[i]);
			glPopMatrix();
		}
	}


	redisplay = true;
	glFlush();
}

GLdouble* pointToVector(GLdouble s[3], GLdouble e[3]) {
	GLdouble vector[3] = { e[0] - s[0], e[1] - s[1], e[2] - s[2] };
	return vector;
}

GLdouble* normalizeVector(GLdouble* vector) {
	double len = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
	GLdouble normalizedVector[3] = {vector[0] / len, vector[1] / len, vector[2] / len};
	return normalizedVector;
}

void moveCenterOfObject(GLdouble* centerOfObject, GLdouble vector[3], GLdouble velocity) {
	for (int i = 0; i < 3; ++i)
		centerOfObject[0] += vector[0] * velocity;
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON &&
		state == GLUT_DOWN) {
		
		if (x <= width / 2) {
			angle -= 10;
		}
		else {
			angle += 10;
		}
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		GLint viewport[4] = {0};
		GLdouble modelview[16] = {0};
		GLdouble projection[16] = {0};
		GLfloat winX, winY, winZ;
		GLdouble posX, posY, posZ;

		// 뷰포트, 프로젝션 행렬, 모델뷰 행렬 설정
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		for (int i = 0; i < 4; ++i) {
			modelview[i * 4 + 3] = 1;
		}
		for (int i = 0; i < 4; ++i) {
			std::cout << modelview[i * 4] << " " << modelview[i * 4 + 1] << " " << modelview[i * 4 + 2] << " " << modelview[i * 4 + 3] << " " << std::endl;
			
		}

		std::cout << std::endl;
		/*for (int i = 0; i < 4; ++i) {
			std::cout << projection[i * 4] << " " << projection[i * 4 + 1] << " " << projection[i * 4 + 2] << " " << projection[i * 4 + 3] << " " << std::endl;
		}*/

		// 스크린 좌표계의 마우스 좌표값을 변환
		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

		std::cout << posX << " " << posY << " " << posZ << std::endl;
		std::cout << winX << " " << winY << " " << winZ << std::endl;
		

		GLdouble velocity = 0.2;
		GLdouble pointer[3] = { posX, posY, posZ };
		for (int i = 0; i < 4; ++i) {
			GLdouble* dir = pointToVector(centerOfObject[i], pointer);
			GLdouble* unitVector = normalizeVector(dir);

			moveCenterOfObject(centerOfObject[i], unitVector, velocity);
		}
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);							//항상 필요
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Coordinates");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	glutMainLoop();
}
