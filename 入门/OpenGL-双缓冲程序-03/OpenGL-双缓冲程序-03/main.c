//
//  main.c
//  OpenGL-双缓冲程序-03
//
//  Created by 王鹏华 on 16/9/12.
//  Copyright © 2016年 condentast. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/gltypes.h>
#include <GLUT/GLUT.h>
//设置自旋度数
static GLfloat spin = 0.0;

void init(void){
    //配置清楚颜色
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    //压入栈中
    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);
    //设置物体颜色
    glColor3f(1.0, 1.0, 1.0);
    //物体大小
    glRectf(-25.0, -25.0, 25.0, 25.0);
    //出栈
    glPopMatrix();
}

void spinDisplay(void){
    spin = spin + 2.0;
    if (spin > 360.0) {
        spin = spin - 360.0;
        glutPostRedisplay();

    }
}

void reshape(){
    glViewport(0, 0, 50, 50);
    glMatrixMode(GL_PROJECTION);
    //重塑模型
    glLoadIdentity();
    //设置坐标
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    //重塑模型
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
    switch (button) {
            //点击左边
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                glutIdleFunc(spinDisplay);
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            //点击鼠标
            if (state == GLUT_DOWN) {
                glutIdleFunc(NULL);
            }
        default:
            break;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("第三个OpenGL程序,双缓冲程序");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
