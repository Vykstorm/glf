/*
=========================================================================
  GLF Library Demo - 3D Text

  Author: Roman Podobedov
  Email: romka@ut.ee
  WEB: http://romka.demonews.com
=========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "../glf.h"

int WindW, WindH;
int a;

void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0, 1, 0);
  glPushMatrix();

  glRotatef(a, 1, 1, 1);
  a += 3;
  if (a > 359) a = a - 360;

  glTranslatef(-1.5, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  glfDraw3DWiredString("3D Text");
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}


void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-0.5, 0.5, -0.5, 0.5, 2, 14);
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

  a = 0;
  glfInit();
  glfLoadFont("../fonts/techno1.glf");
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  (void)glutCreateWindow("GLF Demo - 3D Text");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);
  glClearColor(0, 0, 0, 0);
  glutTimerFunc(40, timf, 0);
  glfSetSymbolSpace(0.2);
  glutMainLoop();
}
