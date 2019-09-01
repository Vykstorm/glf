/*
=========================================================================
  GLF Library Demo - Solid Text
 
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

  glColor3f(1, 1, 0);
  glPushMatrix();
  glRotatef(a, 0, 0, 1);
  a++;
  if (a > 359) a = 0;
  glTranslatef(-1.2, 0, 0);
  glScalef(0.25, 0.25, 1);
  glfDrawSolidString("Solid text!");
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
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

void timf(int value)
{
  glutPostRedisplay();
  glutTimerFunc(40, timf, 0);
}


void main(int argc, char *argv[])
{
  WindW = 600;
  WindH = 300;

  a = 0;
  glfInit();
  glfLoadFont("../fonts/times_new1.glf");
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  (void)glutCreateWindow("GLF Demo - Solid Text");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);
  glutTimerFunc(40, timf, 0);

  glClearColor(0, 0, 0, 0);
  glutMainLoop();
}
