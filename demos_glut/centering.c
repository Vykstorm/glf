/*
=========================================================================
  GLF Library Demo - Vector Text Centering
 
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

	glColor3f(1, 1, 0);

	glBegin(GL_LINES);	
		glVertex3f(-0.5, 1, 0);
		glVertex3f(-0.5, -1, 0);
	glEnd();

	glPushMatrix();
	glTranslatef(-0.5, 0.3, 0);
	glScalef(0.1, 0.1, 1);
	glfStringCentering(GL_TRUE);
	glfDrawSolidString("Centered text");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.3, 0);
	glScalef(0.1, 0.1, 1);
	glfStringCentering(GL_FALSE);
	glfDrawSolidString("Not Centered text");
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}


void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(-1.333, 1.333, -1, 1);
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


int main(int argc, char *argv[])
{
  WindW = 640;
  WindH = 480;

  glfInit();
  glfLoadFont("../fonts/times_new1.glf");
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  (void)glutCreateWindow("GLF Demo - Vector Text Centering");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);
  glutTimerFunc(40, timf, 0);

  glClearColor(0, 0, 0, 0);
  glutMainLoop();
    return 0;
}

