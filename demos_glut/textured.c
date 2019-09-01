/*
=========================================================================
  GLF Library Demo - Textured Symbols Test

  Author: Roman Podobedov
  Email: romka@ut.ee
  WEB: http://romka.demonews.com
=========================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "../glf.h"
#include "texture.h"

int WindW, WindH;
int font1;
unsigned *teximage;

void LoadTexture()
{
  int texwid, texht;
  int texcomps;
  char fn[]="texture.rgb";
 
  teximage = read_texture(fn, &texwid, &texht, &texcomps);
  if (!teximage)
  {
    printf("Sorry, can't read texture file...\n");
    exit(0);
  }
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texwid, texht, 0, GL_RGBA, GL_UNSIGNED_BYTE, teximage);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
} 

void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  glTranslatef(-1.0, 0.5, 0);
  glScalef(0.3, 0.3, 1);
  glEnable(GL_TEXTURE_2D);
  glfDrawSolidStringF(font1, "Textured");
  glLoadIdentity();
  glTranslatef(-0.5, -0.2, 0);
  glScalef(0.3, 0.3, 1);
  glfDrawSolidStringF(font1, "Text");

  glFlush();
  glutSwapBuffers();
}


void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.33, 1.33, -1, 1);
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
  font1 = glfLoadFont("../fonts/techno1.glf");
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  (void)glutCreateWindow("GLF Demo - Textured Text");
  LoadTexture();

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);
  glClearColor(0, 0, 0, 0);
  glfSetSymbolSpace(0.2);
  glfEnable(GLF_TEXTURING);
  
  glutMainLoop();
}
