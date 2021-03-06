//
//  main.c
//  OpenGL-05-点画线升级版!
//
//  Created by 王鹏华 on 16/9/13.
//  Copyright © 2016年 condentast. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/gltypes.h>
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

void display(void)
{
    GLubyte fly[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//1
        0x03, 0x80, 0x01, 0xC0, 0x06, 0XC0, 0x03, 0x60,//2
        0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,//3
        0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,//4
        0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,//5
        0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,//6
        0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,//7
        0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,//8
        0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,//9
        0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,//10
        0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,//11
        0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,//12
        0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,//13
        0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,//14
        0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,//15
        0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08 //16
    };
    
    GLubyte halftone[] = {
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//1
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//2
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//3
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//4
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//5
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//6
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//7
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//8
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//9
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//10
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//11
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//12
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//13
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//14
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//15
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,//16
    };
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glRectf(25.0, 25.0, 125.0, 125.0);
    glEnable(GL_POLYGON_STIPPLE);
    glPolygonStipple(fly);
    glRectf(125.0, 25.0, 225.0, 125.0);
    glPolygonStipple(halftone);
    glRectf(225.0, 25.0, 325.0, 125.0);
    glDisable(GL_POLYGON_STIPPLE);
    glFlush();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(350, 150);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

