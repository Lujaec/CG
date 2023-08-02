//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#include<GL/glut.h>
//#include<iostream>
//using namespace std;
//
//int width, height, nrChannels;
//unsigned char* img1 = stbi_load("carDoor.jpg", &width, &height, &nrChannels, 0);
//unsigned int texture;
//
//void init(void)
//{
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_DEPTH_TEST);
// 
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//        GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//        GL_NEAREST);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
//
//    glEnable(GL_TEXTURE_2D);
//
//    stbi_image_free(img1);
//}
//
//void display(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    /*glBegin(GL_QUADS);
//    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.0);
//    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.0);
//    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.0);
//    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.0);
//    glEnd();*/
//
//    /*glBegin(GL_QUADS);
//    glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
//    glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
//    glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
//    glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
//    glEnd();*/
//
//    //구에 텍스쳐 입히기
//    GLUquadricObj* sphere = NULL;
//    sphere = gluNewQuadric();
//    gluQuadricDrawStyle(sphere, GLU_FILL);
//    gluQuadricTexture(sphere, true);
//    gluQuadricNormals(sphere, GLU_SMOOTH);
//    //Making a display list
//  
//    gluSphere(sphere, 1.0, 20, 20);
//    glEndList();
//  
//
//
//    glFlush();
//}
//
//int main(int argc, char** argv){
//        glutInit(&argc, argv);
//        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//        glutInitWindowSize(1000, 1000);
//        glutInitWindowPosition(100, 100);
//        glutCreateWindow(argv[0]);
//        init();
//        glutDisplayFunc(display);
//        glutMainLoop();
//        return 0;
//}
//
