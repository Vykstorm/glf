/*
=========================================================================
  GLF Library Demo - Symbols Test

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

void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0, 1, 0);
  glLoadIdentity();
  glTranslatef(-0.7, 0.8, 0);
  glScalef(0.14, 0.14, 1);
  glfDrawSolidString("0123456789");

  glLoadIdentity();
  glTranslatef(-1, 0.55, 0);
  glScalef(0.12, 0.12, 1);
  glfDrawSolidString("ABCDEFGHIJKLM");

  glLoadIdentity();
  glTranslatef(-1, 0.35, 0);
  glScalef(0.12, 0.12, 1);
  glfDrawSolidString("NOPQRSTUVWXYZ");

  glLoadIdentity();
  glTranslatef(-0.7, 0.1, 0);
  glScalef(0.12, 0.12, 1);
  glfDrawSolidString("abcdefghijklm");

  glLoadIdentity();
  glTranslatef(-0.7, -0.1, 0);
  glScalef(0.12, 0.12, 1);
  glfDrawSolidString("nopqrstuvwxyz");

  glLoadIdentity();
  glTranslatef(-0.75, -0.4, 0);
  glScalef(0.12, 0.12, 1);
  glfDrawSolidString("!\"#$%&'()*+,-./");

  glLoadIdentity();
  glTranslatef(-0.9, -0.7, 0);
  glScalef(0.12, 0.12, 1);
  glfDrawSolidString(":;<=>?@[\\]^_`{|}~");

  glFlush();
}


void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-1.16, 1.16, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
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

void main(int argc, char *argv[])
{
  WindW = 640;
  WindH = 480;

  glfInit();
  glfLoadFont("../fonts/times_new1.glf");
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB);
  (void)glutCreateWindow("GLF Demo - Symbols Test");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);

  glClearColor(0, 0, 0, 0);
  glutMainLoop();
}
