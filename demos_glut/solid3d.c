/*
=========================================================================
  GLF Library Demo - 3D Solid Text
 
  Author: Roman Podobedov
  Email: romka@ut.ee
  WEB: http://romka.demonews.com
=========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include "../glf.h"

int WindW, WindH;
float b, d;
float a, c, minx, miny, maxx, maxy;
int font1, font2;
float aa, ang;

char message[7][40];

int cur_sym;    /* Current symbol */
int cur_string; /* Current string */
char mode;      /* current mode */
int cur_sdelay;
int cur_symdelay; 

void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0, 0.8, 0);
  glPushMatrix();
  glRotatef(a, 1, 1, 1);
  a += 2;
  if (a > 359) a -= 360;
  glTranslatef(-1, 0, 0);
  glfDraw3DSolidString("GLF");  
  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}


void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-0.665, 0.665, -0.5, 0.5, 2, 14);
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
  glutTimerFunc(30, timf, 0);
}

void main(int argc, char *argv[])
{
  GLfloat light_ambient[] = {0.3, 0.3, 1.0, 1.0};
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_position[] = {0.0f, 0.0f, 1.0f, 0.0f};
  
  WindW = 640;
  WindH = 480;

  a = 0;

  glfInit();
  font1 = glfLoadFont("../fonts/techno1.glf");
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  (void)glutCreateWindow("GLF Test");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);
  glClearColor(0, 0, 0, 0);
  glfSetSymbolSpace(0.2);
  glfSetSymbolDepth(0.2);
  glfDisable(GLF_TEXTURING);

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LESS);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glutTimerFunc(30, timf, 0);
  glutMainLoop();
}
