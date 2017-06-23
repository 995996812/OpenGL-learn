//
//  main.c
//  OpenGL-GLUT-02
//
//  Created by 王鹏华 on 16/9/12.
//  Copyright © 2016年 condentast. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/gltypes.h>
#include <GLUT/GLUT.h>

void display(void){
    //清除颜色
    glClear(GL_COLOR_BUFFER_BIT);
    //设置物体颜色
    glColor3f(1.0, 0.8, 1.0);
    //绘制物体
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush();
}

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("第二个OpenGL程序");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
