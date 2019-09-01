/*
=========================================================================
  GLF Library Demo - Simply Text

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
  glPushMatrix();
  glTranslatef(-1.2, 0, 0);
  glScalef(0.25, 0.25, 1);
  glfDrawWiredString("Simply text!");
  glPopMatrix();
  glFlush();
}


void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-1.5, 1.5, -1, 1);
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
  WindW = 600;
  WindH = 300;

  glfInit();
  glfLoadFont("../fonts/times_new1.glf");
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB);
  (void)glutCreateWindow("GLF Demo - Simply Text");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);

  glClearColor(0, 0, 0, 0);
  glutMainLoop();
}
