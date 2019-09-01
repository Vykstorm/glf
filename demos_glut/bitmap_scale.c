/*
=========================================================================
  GLF Library Demo - Bitmap Scaling

  Author: Roman Podobedov
  Email: romka@ut.ee
  WEB: http://romka.demonews.com
=========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <GL/glut.h>
#include "../glf.h"

int WindW, WindH;
char s[]="GLF Library";
float a=20.0f;
int cur_sym=0;

void Draw(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glfStartBitmapDrawing();

	glColor4f(1, 0, 1, 0.5);

	glLoadIdentity();
	glTranslatef(1, 2, 0);
	glScalef(10, 10, 0);
	a -= 1;
	if (a <= 1) 
	{
		a = 20.0f;
		if (cur_sym < strlen(s)) cur_sym++;
	};

	for (i=0; i<cur_sym; i++) glfDrawBSymbol(s[i]);
	
	if (cur_sym < strlen(s))
	{
		glPushMatrix();
		glScalef(a, a, 0);
		glfDrawBSymbol(s[cur_sym]);
		glPopMatrix();
	}

	glfStopBitmapDrawing();
	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	float a;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	a = (float)width/(float)height;
	gluOrtho2D(0, 4*a, 0, 4);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  
	WindW = width;
	WindH = height;
}

static void Key(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27: glfClose(); exit(0);
             break;
  }
}

void timf(int value)
{
  glutPostRedisplay();
  glutTimerFunc(20, timf, 0);
}

void main(int argc, char *argv[])
{
	WindW = 800;
	WindH = 600;

	glfInit();
	glutInit(&argc, argv);
	glutInitWindowSize(WindW, WindH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	(void)glutCreateWindow("GLF Demo - Bitmap Scaling");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glClearColor(0, 0, 0, 1);
	glfLoadBMFFont("../fonts/fixedsys.bmf");

	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	glEnable(GL_BLEND);

	glutTimerFunc(1, timf, 0);
	glutMainLoop();
}
