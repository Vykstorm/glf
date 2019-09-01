/*
=========================================================================
  GLF Library Demo - Multiple Bitmapped Fonts

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
int font1, font2, font3, font4, font5;

void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	
	glPushMatrix();
	glfSetCurrentBMFFont(font1);
	glfStartBitmapDrawing();
	glTranslatef(0.5, 3, 0);
	glScalef(4, 4, 0);
	glfDrawBString("This string is printed by font 1");
	glfStopBitmapDrawing();
	glPopMatrix();

	glPushMatrix();
	glfSetCurrentBMFFont(font2);
	glfStartBitmapDrawing();
	glTranslatef(0.5, 2.5, 0);
	glScalef(4, 4, 0);
	glfDrawBString("This string is printed by font 2");
	glfStopBitmapDrawing();
	glPopMatrix();

	glPushMatrix();
	glfSetCurrentBMFFont(font3);
	glfStartBitmapDrawing();
	glTranslatef(0.5, 2, 0);
	glScalef(4, 4, 0);
	glfDrawBString("This string is printed by font 3");
	glfStopBitmapDrawing();
	glPopMatrix();
	
	glPushMatrix();
	glfSetCurrentBMFFont(font4);
	glfStartBitmapDrawing();
	glTranslatef(0.5, 1.5, 0);
	glScalef(4, 4, 0);
	glfDrawBString("This string is printed by font 4");
	glfStopBitmapDrawing();
	glPopMatrix();

	glPushMatrix();
	glfSetCurrentBMFFont(font5);
	glfStartBitmapDrawing();
	glTranslatef(0.5, 1, 0);
	glScalef(4, 4, 0);
	glfDrawBString("This string is printed by font 5");
	glfStopBitmapDrawing();
	glPopMatrix();


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
	(void)glutCreateWindow("Multiple Bitmapped Fonts");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glClearColor(0, 0, 0, 1);
	font1 = glfLoadBMFFont("../fonts/fixedsys.bmf");
	font2 = glfLoadBMFFont("../fonts/times_new.bmf");
	font3 = glfLoadBMFFont("../fonts/impact.bmf");
	font4 = glfLoadBMFFont("../fonts/courier.bmf");
	font5 = glfLoadBMFFont("../fonts/arial.bmf");

	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	glEnable(GL_BLEND);

	glutTimerFunc(1, timf, 0);
	glutMainLoop();
}
