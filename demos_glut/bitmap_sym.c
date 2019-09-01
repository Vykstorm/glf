/*
=========================================================================
  GLF Library Demo - Bitmapped Symbols Test

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

void Draw(void)
{
	int i, j, c;

	glClear(GL_COLOR_BUFFER_BIT);

	glfStartBitmapDrawing();

	c = 0;
	for (i=0; i<16; i++)
 		for (j=0; j<16; j++)
		{
			glLoadIdentity();
			glTranslatef((float)j, (float)(16-i)*1.1-1, 0);
			glScalef(18, 18, 1);
			glfDrawBSymbol(c);
			c++;
		}
	glfStopBitmapDrawing();
	glFlush();
	glutSwapBuffers();
}


void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, 16, 0, 18);
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
	glutTimerFunc(30, timf, 0);
}

void main(int argc, char *argv[])
{
	WindW = 640;
	WindH = 480;

	glfInit();
	glutInit(&argc, argv);
	glutInitWindowSize(WindW, WindH);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	(void)glutCreateWindow("GLF Bitmapped Symbols Demo");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glClearColor(0, 0, 0, 0);
	glfLoadBMFFont("../fonts/impact.bmf");

	glutTimerFunc(30, timf, 0);
	glutMainLoop();
}
