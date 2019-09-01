/*
=========================================================================
  GLF Library Demo - Bitmapped Text

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
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glfStartBitmapDrawing();

	glTranslatef(-1.5, 0.5, 0);
	glScalef(4, 4, 1);
	glfDrawBString("Welcome to GLF Library");
	glLoadIdentity();
	glTranslatef(-1.9, -0.5, 0);
	glScalef(2.9, 2.9, 1);
	glfDrawBString("This string is printed by bitmapped font!");

	glfStopBitmapDrawing();
	glFlush();
	glutSwapBuffers();
}


void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-2, 2, -2, 2);
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
	(void)glutCreateWindow("GLF Bitmapped Text");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glClearColor(0, 0, 0, 0);
	glfLoadBMFFont("../fonts/fixedsys.bmf");

	glutTimerFunc(30, timf, 0);
	glutMainLoop();
}
