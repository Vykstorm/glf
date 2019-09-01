/*
=========================================================================
| GLF Library Demo - Console Demo
|
| Author: Roman Podobedov
| Email: romka@ut.ee
| WEB: http://romka.demonews.com
=========================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include "../glf.h"

#define SDELAY 40
#define SYMDELAY 1

#define MODE_PRINT 1
#define MODE_DELAY 2

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

void printfunc()
{
  char aaa;

  if (mode == MODE_PRINT)
  {
    if (cur_symdelay <= 0) 
    {
      cur_symdelay = SYMDELAY;
      glfPrintChar(message[cur_string][cur_sym]);
      aaa = message[cur_string][cur_sym];
      cur_sym++;
      if (cur_sym > (int)strlen(&message[cur_string][0]))
      {
        cur_sym = 0;
        cur_string++;
        if (cur_string > 6) cur_string = 0;
        mode = MODE_DELAY;
        return;
      }
    }
    cur_symdelay--;
  }
  if (mode == MODE_DELAY)
  {
    cur_sdelay--;
    if (cur_sdelay < 0) 
    {
      cur_sdelay = SDELAY;
      mode = MODE_PRINT;
    }
  }
}

void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_LINE_SMOOTH);

  /* Draw Romka Logo */
  glColor3f(0, 0.8, 0);
  
  glPushMatrix();
  glRotatef(30, 0, 1, 0);
  glScalef(a, a, a);

  if (a < 0.8) a += a/8+0.02;
  else
  {
    
    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    glTranslatef(-15+b, -1.5, 0);
    if (b < 15) b += b/20 + 0.2;
    glfDraw3DWiredString("Graphics");
    glPopMatrix();
  }

  glPushMatrix();
  glTranslatef(-2, 0.5, 0);
  glfDraw3DWiredSymbol('R');
  glPopMatrix();

  glTranslatef(-0.5, 0.5, 0);
  glfDraw3DWiredString("mka");

  glPushMatrix();
  glTranslatef(-0.7, -0.2, 1);
  glRotatef(ang, 0, 1, 0);
  ang += 2;
  if (ang > 359) ang = ang-360;
  glutWireSphere(0.45, 15, 15);
  glPopMatrix();

  glPopMatrix();
  
  /* Draw console */
  printfunc();
  glColor3f(0.1, 1, 0.2);
  glPushMatrix();
  glTranslatef(-2.5, -0.8, 0);
  glScalef(0.09, 0.09, 1);
  glfConsoleDraw(); 
  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}


void Reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-0.66, 0.66, -0.5, 0.5, 2, 14);
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
  WindW = 640;
  WindH = 480;

  a = 0; b = 0; c = 0;
  ang = 0;
  aa = 0;

  glfInit();
  font1 = glfLoadFont("../fonts/techno0.glf");
  font2 = glfLoadFont("../fonts/techno1.glf");
  glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  (void)glutCreateWindow("GLF Demo - Console Demo");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(Key);
  glClearColor(0, 0, 0, 0);
  glfSetSymbolSpace(0.2);
  glfSetSymbolDepth(0.2);
  glfDisable(GLF_TEXTURING);
  glfSetConsoleParam(40, 8);
  glfSetConsoleFont(font1);

  strcpy(&message[0][0], "GLF Library\n");
  strcpy(&message[1][0], "Romka Graphics\n");
  strcpy(&message[2][0], "web: http://romka.demonews.com\n");
  strcpy(&message[3][0], "email: romka@ut.ee\n");
  strcpy(&message[4][0], "This is a console mode!\n");
  strcpy(&message[5][0], "You can use this mode like console\n");
  strcpy(&message[6][0], "\n");

  cur_sym = 0;
  cur_string = 0;
  cur_sdelay = SDELAY;
  cur_symdelay = SYMDELAY;
  mode = MODE_PRINT;
  glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
  glEnable(GL_BLEND);

  glutTimerFunc(30, timf, 0);
  glutMainLoop();
}
