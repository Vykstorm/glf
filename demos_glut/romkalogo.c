/*
==============================================================================
|  GLF Library Demo - Romka Graphics Logotype
| 
|  Author: Roman Podobedov
|  Email: romka@ut.ee
|  WEB: http://romka.demonews.com
|  Date: 13 July 2000
|  
|  Copyright (C) 2000, Romka Graphics
|  This program is freely distributable without any license or permissions.
==============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "../glf.h"

int WindW, WindH;
float a, b, c;
int aa, ang;
int font;
char temp[512];


void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_LINE_SMOOTH);

  glColor3f(0, 0.8, 0);
  
  glPushMatrix();
  glRotatef(30, 0, 1, 0);
  glScalef(a, a, a);

  if (a < 0.8) a += a/8+0.02;
  else
  {
    
    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    glTranslatef(-15+b, -1.5, 0);
    if (b < 15) b += b/20 + 0.2;
    glfDraw3DWiredString("Graphics");
    glPopMatrix();
  }

  glPushMatrix();
  glTranslatef(-2, 0.5, 0);
  glfDraw3DWiredSymbol('R');
  glPopMatrix();

  glTranslatef(-0.5, 0.5, 0);
  glfDraw3DWiredString("mka");

  glPushMatrix();
  glTranslatef(-0.7, -0.2, 1);
  glRotatef(ang, 0, 1, 0);
  ang += 2;
  if (ang > 359) ang = ang-360;
  glutWireSphere(0.45, 15, 15);
  glPopMatrix();

  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}


void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-0.6, 0.6, -0.5, 0.5, 2, 14);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -9.0);
  
  WindW = width;
  WindH = height;
}

static void Key(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27: exit(0);
             break;
  }
}

void timf(int value)
{
  glutPostRedisplay();
  glutTimerFunc(40, timf, 0);
}


void main(int argc, char *argv[])
{
  WindW = 640;
  WindH = 480;

  glfInit();
  font = glfLoadFont("../fonts/techno1.glf");
  glfSetSymbolDepth(0.2);
  glfSetCurrentFont(font);
  
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  (void)glutCreateWindow("GLF Demo - Romka Graphics Logotype");

  glutFullScreen();
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);
  glutTimerFunc(40, timf, 0);

  glClearColor(0, 0, 0, 0);

  a = 0;
  b = 0;
  c = 0;
  ang = 0;
  aa = 0;
  
  glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
  glEnable(GL_BLEND);
  glutMainLoop();
}

