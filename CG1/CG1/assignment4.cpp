#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

GLboolean redFlag = true, switchOne = false, switchTwo = false, switchLamp = false, amb1 = true, diff1 = true, spec1 = true, amb2 = true, diff2 = true, spec2 = true, amb3 = true, diff3 = true, spec3 = true;
double windowHeight = 800, windowWidth = 600, tmpWidth, tmpColumn, tmpHeight;
double roomX, roomY, roomZ;
double eyeX = 0.5, eyeY = 0.5, eyeZ = 0.5, refX = 0, refY = 0.3, refZ = 0;
double theta = 180.0, y = 1.36, z = 7.97888;

// 카메라 변수
GLfloat yaw = 0;
GLfloat pitch = 60.0f;
GLfloat cameraX = 0.5f;
GLfloat cameraY = 0.5f;
GLfloat cameraZ = 0.5f;
static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 1.0}, //1
    {1.0, 0.0, 1.0}, //2
    {1.0, 0.0, 0.0}, //3
    {0.0, 1.0, 0.0}, //4
    {0.0, 1.0, 1.0}, //5
    {1.0, 1.0, 1.0}, //6
    {1.0, 1.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 3, 2, 1}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};

static void getNormal3p
(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

void drawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
            v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
            v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX = 0, GLfloat ambY = 0, GLfloat ambZ = 0, GLfloat shine = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
            v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
            v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

void setMaterial(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX = 0, GLfloat ambY = 0, GLfloat ambZ = 0, GLfloat shine = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void setColorRGB(GLfloat* color, int r, int g, int b) {
    color[0] = (1.0) * r / 255;
    color[1] = (1.0) * g / 255;
    color[2] = (1.0) * b / 255;
}

void room()
{
    roomX = 1, roomZ = 1, roomY = 0.75;
    GLfloat color[3] = { 0 }, amb_coff, dif_coff;

    amb_coff = 0.4;
    dif_coff = 0.8;
    //말 사진 걸려있는 벽
    glPushMatrix();
    setColorRGB(color, 163, 154, 147);
    glColor3f(color[0], color[1], color[2]);
    glScalef(roomX, roomY, 0.01);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff, 50);
    glPopMatrix();


    amb_coff = 0.4;
    dif_coff = 0.8;
    //창 있는왼쪽 벽
    glPushMatrix();
    setColorRGB(color, 187, 183, 180);
    glColor3f(color[0], color[1], color[2]);
    glScalef(0.01, roomY, roomZ);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff, 50);
    glPopMatrix();



    //바닥
    amb_coff = 0.4;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 208, 207, 205);

    glColor3f(color[0], color[1], color[2]);
    glScalef(roomX, 0.0001, roomZ);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff, 50);
    glPopMatrix();
}

void bed() {
    GLfloat color[3] = { 0 };
    double width[10] = {}, column[10] = {}, height[10] = {}, amb_coff, dif_coff;

    width[0] = 0.25, column[0] = 0.4, height[0] = 0.1;
    width[1] = width[0], column[1] = column[0] / 2.5, height[1] = height[0];
    width[2] = width[0], column[2] = column[1], height[2] = height[1] / 3;
    width[3] = width[0], column[3] = column[1], height[3] = height[1] / 3;
    width[4] = width[0], column[4] = column[1], height[4] = height[1] / 3;
    width[5] = 0.02, column[5] = column[2] + column[3] + column[4], height[5] = height[0] * 2;// width  hard 코딩
    width[6] = width[0] - width[5], column[6] = column[2] + column[3] + column[4], height[6] = height[1] / 3 * 1.5;  //메트리스
    width[7] = width[6], column[7] = column[0] / 7, height[7] = height[6] / 3 * 1.5;

    tmpWidth = width[6] / 2; // 매트리스의 절반
    tmpColumn = column[6];
    tmpHeight = height[0];


    //침대의 검은 부분 0
    amb_coff = 0.8;
    dif_coff = 0.9;
    glPushMatrix();
    setColorRGB(color, 61, 49, 40);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(column[1], 0, 0);
    glScalef(column[0], height[0], width[0]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();


    //침대의 베이지 부분 맨 아래   1
    amb_coff = 0.35;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 219, 188, 147);
    glColor3f(color[0], color[1], color[2]);
    glScalef(column[1], height[1], width[1]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();

    //침대의 베이지 부분 맨 아래 바로 위  2
    amb_coff = 0.35;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 219, 188, 147);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height[1], 0);
    glScalef(column[2], height[2], width[2]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();

    //2 의 바로 옆    3
    amb_coff = 0.35;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 219, 188, 147);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(column[2], height[1], 0);
    glScalef(column[2], height[2], width[2]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();

    //3의 바로 옆      4
    amb_coff = 0.35;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 219, 188, 147);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(column[2] + column[3], height[1], 0);
    glScalef(column[4], height[4], width[4]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();

    //베이지색의 벽에 기대어 있는 부분 ../5
    amb_coff = 0.35;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 219, 188, 147);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height[0], 0);
    glScalef(column[5], height[5], width[5]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();

    //회색 매트리스  .. /6
    amb_coff = 0.2;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height[0] + height[2], width[5]);
    glScalef(column[6], height[6], width[6]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();


    //배개  .. /7
    amb_coff = 0.2;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height[0] + height[2] + height[6], width[5]);
    glScalef(column[7], height[7] + 0.01, width[7]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();
}

void desk() {
    GLfloat color[3] = { 0 };
    double gap_right_wall = 0.01;

    ///////// scale을 위한 길이
    double width_for_desk[10] = {}, column_for_desk[10] = {}, height_for_desk[10] = {}, amb_coff, dif_coff;
    column_for_desk[0] = roomX - tmpColumn - gap_right_wall, height_for_desk[0] = 0.015, width_for_desk[0] = tmpWidth * 2;
    column_for_desk[1] = column_for_desk[0] / 20, height_for_desk[1] = tmpHeight, width_for_desk[1] = width_for_desk[0];
    column_for_desk[2] = column_for_desk[0] / 5, height_for_desk[2] = tmpHeight * 2, width_for_desk[2] = width_for_desk[0];


    ////////// translate을 위한 좌표
    double x_for_desk[10] = {}, y_for_desk[10] = {}, z_for_desk[10] = {};
    x_for_desk[0] = tmpColumn, y_for_desk[0] = tmpHeight * 2, z_for_desk[0] = 0;
    x_for_desk[1] = tmpColumn, y_for_desk[1] = tmpHeight, z_for_desk[1] = 0;
    x_for_desk[2] = roomX - column_for_desk[2] - gap_right_wall, y_for_desk[2] = 0, z_for_desk[1] = 0;

    //plane
    amb_coff = 0.2;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 207, 206, 204);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(x_for_desk[0], y_for_desk[0], z_for_desk[0]);
    glScalef(column_for_desk[0], height_for_desk[0], width_for_desk[0]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();

    //왼쪽 다리
    amb_coff = 0.2;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 207, 206, 204);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(x_for_desk[1], y_for_desk[1], z_for_desk[1]);
    glScalef(column_for_desk[1], height_for_desk[1], width_for_desk[1]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();

    //오른쪽 다리
    amb_coff = 0.2;
    dif_coff = 0.8;
    glPushMatrix();
    setColorRGB(color, 207, 206, 204);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(x_for_desk[2], y_for_desk[2], z_for_desk[2]);
    glScalef(column_for_desk[2], height_for_desk[2], width_for_desk[2]);
    drawCube1(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();
}

void monitor() {
    GLfloat color[3] = { 0 };
    GLfloat amb_coff, dif_coff;
    GLUquadricObj* quadratic;
    float r_bottom = 0.04, pilir_height = 0.07;
    float r_middle = 0.005;

    quadratic = gluNewQuadric();
    gluQuadricDrawStyle(quadratic, GLU_FILL);

    amb_coff = 0.1;
    dif_coff = 0.9;
    glPushMatrix();
    setColorRGB(color, 201, 210, 240);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, pilir_height, 0);
    glScalef(4, 3, 0.4);

    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glutSolidCube(0.03);
    glPopMatrix();


    //원기둥
    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, pilir_height, 0);
    glRotatef(90, 1, 0, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    gluCylinder(quadratic, r_middle, r_middle, pilir_height, 32, 32);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quadratic, r_bottom, r_bottom, 0.01f, 32, 32);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glRotatef(90, 1, 0, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    gluCylinder(quadratic, r_bottom, 0, 0.01f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glRotatef(90, 1, 0, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    gluCylinder(quadratic, r_bottom, 0, 0.01f, 32, 32);
    glPopMatrix();
}

void lightOne()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.5, 0.9, 0.5, 1.0 }; //5 5 10

    //glEnable(GL_LIGHT0);

    if (amb1 == true) { glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); }
    else { glLightfv(GL_LIGHT0, GL_AMBIENT, no_light); }

    if (diff1 == true) { glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); }
    else { glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light); }

    if (spec1 == true) { glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); }
    else { glLightfv(GL_LIGHT0, GL_SPECULAR, no_light); }

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void lightTwo()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0, 0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 0, 0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.12, 0.22,0.75 };
    GLfloat light_target[] = { 0.5, 0.35, 0 };
    GLfloat spot_direction[3] = { light_target[0] - light_position[0], light_target[1] - light_position[1], light_target[2] - light_position[2] };

    for (int i = 0; i < 3; ++i)
        spot_direction[i] = (light_target[0] - light_position[i]);

    //glEnable( GL_LIGHT1);

    if (amb2 == true) { glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient); }
    else { glLightfv(GL_LIGHT1, GL_AMBIENT, no_light); }

    if (diff2 == true) { glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse); }
    else { glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light); }

    if (spec2 == true) { glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular); }
    else { glLightfv(GL_LIGHT1, GL_SPECULAR, no_light); }

    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

    glPopMatrix();
}

void photoFrame() {
    GLfloat color[3] = { 0 }, amb_coff, dif_coff;

    amb_coff = 0.2;
    dif_coff = 0.8;

    glPushMatrix();
    setColorRGB(color, 163, 154, 147);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0.8, 0.5, 0);
    glScalef(1.5, 2.5, 0.15);
    glutSolidCube(0.1);
    glPopMatrix();

}

void rug() {
    GLfloat color[3] = { 0 };
    GLfloat amb_coff, dif_coff;
    GLUquadricObj* quadratic;
    float r = 0.3, pilir_height = 0.01;

    quadratic = gluNewQuadric();
    gluQuadricDrawStyle(quadratic, GLU_FILL);

    amb_coff = 0.1;
    dif_coff = 0.7;

    //원기둥
    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glRotatef(90, 1, 0, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    gluCylinder(quadratic, r, r, pilir_height, 32, 32);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glRotatef(90, 1, 0, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    gluCylinder(quadratic, r, 0, 0.01f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glRotatef(90, 1, 0, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    gluCylinder(quadratic, r, 0, 0.01f, 32, 32);
    glPopMatrix();
}

void car(void)
{
    GLfloat color[3];
    double dif_coff = 0.8, amb_coff = 0.2;


    setColorRGB(color, 212, 34, 34);
    glColor3f(color[0], color[1], color[2]);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);

    glPushMatrix();
    glPushMatrix();
    glPushMatrix();                   // body
    glScalef(4, 1, 2);
    glutSolidCube(.5);
    glTranslatef(-.05, .3, 0);
    glScalef(0.6, 3, 2);
    glutSolidCube(.25);
    glTranslatef(-.12, .001, -.001);
    glScalef(1, 1.8, 2.48);
    glRotatef(230, 0, 0, 250);
    glutSolidCube(.1);
    glPopMatrix();
    glTranslatef(0, 0, .5);
    glPushMatrix();
    glTranslatef(-.4, -.2, 0);
    glutSolidTorus(.1, .2, 8, 8);       // wheel
    glTranslatef(1, 0, 0);
    glutSolidTorus(.1, .2, 8, 8);       // wheel
    glPopMatrix();
    glTranslatef(0, 0, -1);
    glPushMatrix();
    glTranslatef(-.4, -.2, 0);
    glutSolidTorus(.1, .2, 8, 8);       // wheel
    glTranslatef(1, 0, 0);
    glutSolidTorus(.1, .2, 8, 8);       // wheel
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void lamp() {
    GLfloat color[3] = { 0 };
    GLfloat amb_coff, dif_coff;
    GLUquadricObj* quadratic;
    float r1_bottom = 0.2, r1_top = 0.05, height1 = 0.1;
    float r2_bottom = 0, r2_top = 0, height2 = 0;
    float r3_bottom = 0, r3_top = 0, height3 = 0;
    float r1_sphere = 0.07;
    quadratic = gluNewQuadric();
    gluQuadricDrawStyle(quadratic, GLU_FILL);

    amb_coff = 0.1;
    dif_coff = 0.9;


    //원기둥
    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glRotatef(-90, 1, 0, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    gluCylinder(quadratic, r1_bottom, r1_top, height1, 32, 32);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height1 + 0.045, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glutSolidSphere(r1_sphere, 32, 32);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height1 + 0.3, 0);
    glScalef(0.5, 6, 0.5);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height1 + 0.045 + 0.6, 0);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glutSolidSphere(r1_sphere, 32, 32);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glRotatef(-30, 1, 0, 0);
    glTranslatef(0, height1 + 0.3 + 0.4, 0.4);
    glScalef(0.5, 3, 0.5);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height1 + 0.045 + 0.6 + 0.3, -0.15);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    glutSolidSphere(r1_sphere, 32, 32);
    glPopMatrix();



    glPushMatrix();
    setColorRGB(color, 245, 237, 230);
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0, height1 + 0.045 + 0.6 + 0.3, -0.35);
    setMaterial(color[0] * dif_coff, color[1] * dif_coff, color[2] * dif_coff, color[0] * amb_coff, color[1] * amb_coff, color[2] * amb_coff);
    gluCylinder(quadratic, r1_bottom / 1.5, r1_top, 2 * height1, 32, 32);
    glPopMatrix();
}

void rotateCamera() {
    //// 카메라의 방향 벡터를 계산
    //GLfloat cameraDirectionX = sin(cameraAngle);
    //GLfloat cameraDirectionY = 0.0f;
    //GLfloat cameraDirectionZ = cos(cameraAngle);

    //// gluLookAt 함수를 사용하여 카메라를 설정
    //gluLookAt(cameraX, cameraY, cameraZ,  // 카메라 위치
    //    cameraX + cameraDirectionX, cameraY + cameraDirectionY, cameraZ + cameraDirectionZ,  // 목표 지점
    //    0.0f, 1.0f, 0.0f);  // 상단 방향
}

// 디스플레이 콜백 함수
void rtdisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // 카메라 회전
    rotateCamera();

    // 여기서 물체를 그리거나 다른 렌더링 작업을 수행합니다.

    glFlush();
    glutSwapBuffers();
}

// 시간 콜백 함수
void timer(int value) {
    // 카메라 각도를 업데이트
    /*cameraAngle += 0.01f;*/

    // 디스플레이 함수를 호출하여 화면을 다시 그립니다.
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // 60프레임으로 설정
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 0.1, 100);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const double PI = 3.14;
    GLfloat cameraDirectionX = cos(yaw);
    GLfloat cameraDirectionY = 0;
        GLfloat cameraDirectionZ = sin(yaw);

    // gluLookAt 함수를 사용하여 카메라를 설정
    gluLookAt(cameraX, cameraY, cameraZ,  // 카메라 위치
        cameraX + cameraDirectionX, cameraY + cameraDirectionY, cameraZ + cameraDirectionZ,  // 목표 지점
        0.0f, 1.0f, 0.0f);  // 상단 방향
    /*gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, 0, 1, 0);*/
    glEnable(GL_LIGHTING);
    lightOne();
    lightTwo();

    room();
    bed();
    desk();

    glPushMatrix();
    glTranslatef(0.8, 0.23, 0.1);
    monitor();
    glPopMatrix();

    photoFrame();

    glPushMatrix();
    glTranslatef(0.6, 0.01, 0.65);
    rug();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6, 0.23, 0.1);
    glScalef(0.04, 0.04, 0.04);
    car();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, 0.0, 0.8);
    glScalef(0.2, 0.2, 0.2);
    glRotatef(-30, 0, 1, 0);
    lamp();
    glPopMatrix();
    glutSwapBuffers();
}



void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    //case 'w': // move eye point upwards along Y axis
    //    eyeY += 1.0 / 10;
    //    break;
    //case 's': // move eye point downwards along Y axis
    //    eyeY -= 1.0 / 10;
    //    break;
    //case 'a': // move eye point left along X axis
    //    eyeX -= 1.0 / 10;
    //    break;
    //case 'd': // move eye point right along X axis
    //    eyeX += 1.0 / 10;
        break;
    case 'o':  //zoom out
        eyeZ += 1.0 / 10;
        break;
    case 'i': //zoom in
        eyeZ -= 1.0 / 10;
        break;
    case 'q': //back to default eye point and ref point
        eyeX = 7.0; eyeY = 2.0; eyeZ = 15.0;
        refX = 0.0; refY = 0.0; refZ = 0.0;
        break;
    case 'j': // move ref point upwards along Y axis
        refY += 1.0 / 10;
        break;
    case 'n': // move ref point downwards along Y axis
        refY -= 1.0 / 10;
        break;
    case 'b': // move ref point left along X axis
        refX -= 1.0 / 10;
        break;
    case 'm': // move eye point right along X axis
        refX += 1.0 / 10;
        break;
    case 'k':  //move ref point away from screen/ along z axis
        refZ += 1.0 / 10;
        break;
    case 'l': //move ref point towards screen/ along z axis
        refZ -= 1.0 / 10;
        break;
    case '0': //to turn on and off light one
        if (switchOne == false)
        {
            switchTwo = false; amb2 = false; diff2 = false; spec2 = false;
            glDisable(GL_LIGHT1);
            switchOne = true; amb1 = true; diff1 = true; spec1 = true;
            glEnable(GL_LIGHT0);
            break;
        }
        else if (switchOne == true)
        {
            switchOne = false; amb1 = false; diff1 = false; spec1 = false; glDisable(GL_LIGHT0); break;
        }
    case '1': //to turn on and off light two
        if (switchTwo == false)
        {
            switchOne = false; amb1 = false; diff1 = false; spec1 = false;
            glDisable(GL_LIGHT0);
            switchTwo = true; amb2 = true; diff2 = true; spec2 = true;
            glEnable(GL_LIGHT1);

            break;
        }
        else if (switchTwo == true)
        {
            switchTwo = false; amb2 = false; diff2 = false; spec2 = false;
            glDisable(GL_LIGHT1); break;
        }

    case '2': //to turn on and off light two
        if (switchOne == true && switchTwo == true)
        {
            switchOne = false; amb1 = false; diff1 = false; spec1 = false;
            glDisable(GL_LIGHT0);
            switchTwo = false; amb2 = false; diff2 = false; spec2 = false;
            glDisable(GL_LIGHT1); break;
        }
        else
        {
            switchOne = true; amb1 = true; diff1 = true; spec1 = true;
            glEnable(GL_LIGHT0);
            switchTwo = true; amb2 = true; diff2 = true; spec2 = true;
            glEnable(GL_LIGHT1); break;
        }
    case '3': //turn Off all light
        switchOne = false; amb1 = false; diff1 = false; spec1 = false;
        glDisable(GL_LIGHT0);
        switchTwo = false; amb2 = false; diff2 = false; spec2 = false;
        glDisable(GL_LIGHT1); break;
    //case'4': //turn on/off ambient light 1
    //    if (amb1 == false) { amb1 = true; break; }
    //    else { amb1 = false; break; }
    //case'5':
    //    if (diff1 == false) { diff1 = true; break; }
    //    else { diff1 = false; break; }
    //case'6':
    //    if (spec1 == false) { spec1 = true; break; }
    //    else { spec1 = false; break; }
    //case'7': //turn on/off ambient light 2
    //    if (amb2 == false) { amb2 = true; break; }
    //    else { amb2 = false; break; }
    //case'8':
    //    if (diff2 == false) { diff2 = true; break; }
    //    else { diff2 = false; break; }
    //case'9':
    //    if (spec2 == false) { spec2 = true; break; }
    //    else { spec2 = false; break; }
    //case'e': //turn on/off ambient lamp light
    //    if (amb3 == false) { amb3 = true; break; }
    //    else { amb3 = false; break; }
    //case'r':
    //    if (diff3 == false) { diff3 = true; break; }
    //    else { diff3 = false; break; }
    //case't':
    //    if (spec3 == false) { spec3 = true; break; }
    //    else { spec3 = false; break; }
    case'z':
        pitch += 0.1f;
        break;
    case 'w': //turn on/off ambient lamp light
        pitch -= 0.1f;
        break;
    case 's':
        pitch += 0.1f;
        break;
    case 'a':
        yaw += 0.1f;
        break; 
    case 'd':
        yaw -= 0.1f;
        break;
    case 27:    // Escape key
        exit(1);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    std::cout << "To move Eye point:" << std::endl;
    std::cout << "w: up" << std::endl;
    std::cout << "s: down" << std::endl;
    std::cout << "a: left" << std::endl;
    std::cout << "d: right" << std::endl;
    std::cout << "i: zoom in" << std::endl;
    std::cout << "o: zoom out" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "To move Camera point:" << std::endl;
    std::cout << "j: up" << std::endl;
    std::cout << "n: down" << std::endl;
    std::cout << "b: left" << std::endl;
    std::cout << "m: right" << std::endl;
    std::cout << "l: move nearer" << std::endl;
    std::cout << "k: move far" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Press q to move to default position" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "For lighting:      " << std::endl;
    std::cout << "Light source 1 [the light on the right on the screen      " << std::endl;
    std::cout << "1: to turn on/off light one     " << std::endl;
    std::cout << "4: to turn on/off ambient light one     " << std::endl;
    std::cout << "5: to turn on/off diffusion light one     " << std::endl;
    std::cout << "6: to turn on/off specular light one      " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Light source 2 [the light on the left on the screen " << std::endl;
    std::cout << "2: to turn on/off light two     " << std::endl;
    std::cout << "7: to turn on/off ambient light two     " << std::endl;
    std::cout << "8: to turn on/off diffusion light two     " << std::endl;
    std::cout << "9: to turn on/off specular light two      " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "Lamp light (spot light)" << std::endl;
    std::cout << "3: to turn on/off lamp     " << std::endl;
    std::cout << "e: to turn on/off ambient lamp light    " << std::endl;
    std::cout << "r: to turn on/off diffusion lamp light      " << std::endl;
    std::cout << "t: to turn on/off specular lamp light      " << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "____________________" << std::endl;
    std::cout << "      " << std::endl;
    std::cout << "      " << std::endl;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("19011460 이유재");

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    //glutReshapeFunc(fullScreen);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    //glutIdleFunc(animate);


    glutMainLoop();

    return 0;
}
