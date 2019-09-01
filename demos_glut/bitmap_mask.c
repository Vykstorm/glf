/*
=========================================================================
  GLF Library Demo - Bitmapped Symbols Test (Masked)

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
#include "texture.h"
#include "../glf.h"

int WindW, WindH;
char s[]="GLF Library";
float a=20.0f;
int cur_sym=0;
unsigned *teximage;  
GLuint texture;

/*=================== Load Texture =========================================*/
void LoadTexture(char *fn)
{
	int texwid, texht;
	int texcomps;
 
	teximage = read_texture(fn, &texwid, &texht, &texcomps);
	if (!teximage)
	{
		printf("Sorry, can't read texture file...");
		exit(0);
	}

	glBindTexture(GL_TEXTURE_2D, texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);

	/* Texture parameters, LINEAR scaling for better texture quality */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

	free(teximage);
} 


void Draw(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(0, 0);
		glTexCoord2f(4, 0); glVertex2f(10, 0);
		glTexCoord2f(4, 4); glVertex2f(10, 10);
		glTexCoord2f(0, 4); glVertex2f(0, 10);
	glEnd();

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

	for (i=0; i<cur_sym; i++) glfDrawBMaskSymbol(s[i]);
	
	if (cur_sym < strlen(s))
	{
		glPushMatrix();
		glScalef(a, a, 0);
		glfDrawBMaskSymbol(s[cur_sym]);
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
		case 27: glfClose(); exit(0); break;
	}
}

void timf(int value)
{
	glutPostRedisplay();
	glutTimerFunc(20, timf, 0);
}

int main(int argc, char *argv[])
{
	WindW = 800;
	WindH = 600;

	glfInit();
	glutInit(&argc, argv);
	glutInitWindowSize(WindW, WindH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	(void)glutCreateWindow("GLF Bitmapped Symbols Demo (Masked)");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glClearColor(0, 0, 0, 1);
	glfLoadBMFFont("../fonts/fixedsys.bmf");

	LoadTexture("texture.rgb");

	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glutTimerFunc(1, timf, 0);
	glutMainLoop();
	
	return 0;
}
