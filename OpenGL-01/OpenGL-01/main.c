//
//  main.c
//  OpenGL-01
//
//  Created by 王鹏华 on 16/9/12.
//  Copyright © 2016年 condentast. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/gltypes.h>
#include <OpenGL/gl3.h>
#include <GLUT/GLUT.h>

void display (void);

int main(int argc, const char * argv[]) {
    // insert code here...
    //这个函数用来初始化GLUT库
    glutInit(&argc, argv);
    //指定窗口大小
    glutInitWindowSize (300, 300);
    //创建窗口
    glutCreateWindow ("第一个OpenGL程序");
    //在窗口上执行绘制方法
    glutDisplayFunc(display);
    //开始执行
    glutMainLoop();
    
    return 0;
}
void display (void)
{
    //确定窗口清除什么颜色,设置窗口清楚什么颜色.
    glClearColor(0.0,0.0,0.0,0.0);
    //设置清楚颜色之后,完成清楚窗口的任务
    glClear(GL_COLOR_BUFFER_BIT);
    //确定绘制物体时所使用的颜色,此后,所有绘制物体都将使用这种颜色,除非再次调用这个函数更改绘图颜色
    glColor3f(1.0,1.0,1.0);
    //指定绘制最终图像时所谁用的坐标系统,决定图像如何映射到屏幕上
    glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
    
    //绘制图像的坐标写在begin和end中间
    glBegin(GL_POLYGON);
    //多边形的角是由glvertex3f函数定义的,参数是x,y,z
    glVertex3f(0.25,0.25,0.0);
    glVertex3f(0.75,0.25,0.0);
    glVertex3f(0.75,0.75,0.0);
    glVertex3f(0.25,0.75,0.0);
    glEnd();
    //确保绘图命令的实际执行.
    glFlush ();
}
