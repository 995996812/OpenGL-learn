//
//  main.c
//  OpenGL-05
//
//  Created by 王鹏华 on 16/9/14.
//  Copyright © 2016年 condentast. All rights reserved.
//
/*
 */

#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/gltypes.h>
#include <GLUT/GLUT.h>

#define XStart -0.8
#define XEnd 0.8
#define YStart -0.8
#define YEnd 0.8
#define NumXPoints 11
#define NumYPoints 11
#define NumPoints (NumXPoints * NumYPoints)
#define NumPointsPerStrip (2 * NumPoints)
#define NumStrips (NumPoints - 1)
#define RestartIndex oxffff


void init(){
    GLuint vbo, ebo;
    GLfloat *vertices;
    GLushort *indices;
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 *NumPoints *sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    vertices = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    
    if (vertices == NULL) {
        fprintf(stderr, "Unable to map vertex buffer \n");
        exit(EXIT_FAILURE);
    }else{
        int i, j;
        GLfloat dx = (XEnd - XStart) / (NumXPoints - 1);
        GLfloat dy = (YEnd - YStart) / (NumYPoints - 1);
        GLfloat *tmp = vertices;
        int n =0;
        
        for (j = 0 ; j < NumYPoints; ++j) {
            GLfloat y = YStart + j * dy;
            for (i = 0; i < NumXPoints; ++i) {
                GLfloat x = XStart + i * dx;
                *tmp++ = x;
                *tmp++ = y;
            }
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glVertexPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);
    }
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumStrips * (NumPointsPerStrip + 1) * sizeof(GLushort), NULL, GL_STATIC_DRAW);
    indices = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    
    if (indices == NULL) {
        fprintf(stderr, "Unable to map index buffer \n");
        exit(EXIT_FAILURE);
    }else{
        int i, j;
        GLushort *index = indices;
        for (j = 0; j < NumStrips; ++j) {
            GLushort bottomRow = j * NumYPoints;
            GLushort topRow = bottomRow + NumYPoints;
            
            for (i = 0; i < NumYPoints; ++i) {
                *index++ = topRow + i;
                *index++ = bottomRow +i;
            }
            *index++ = *RestartIndex;
        }
    }
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    glutInit(&argc, argv);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(25, 25);
    
    
    return 0;
}

















