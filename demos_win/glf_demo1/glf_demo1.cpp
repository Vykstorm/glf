//=========================================================================
//  GLF Library Demo - Win Demo
//
//  Author: Roman Podobedov
//  Email: romka@ut.ee
//  WEB: http://romka.demonews.com
//=========================================================================

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <direct.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../../glf.h"

// Windows parameters
int winX = 0, winY = 0;
int winWidth = 800, winHeight = 600;
char *className = "OpenGL";
char *windowName = "GLF Win Demo";
HDC hDC;
HDC hDCFrontBuffer;
HGLRC hGLRC;

int font1, font2;
float text_angle=0; // Text rotation angle

// Light attributes
GLfloat light_ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat light_specular[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat light_position[] = {0.0f, 100.0f, 0.0f, 1.0f};


/*=================== Main Redraw Module ===================================*/
void Draw(HDC *hDC)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

	// Draw our 3D text
	glPushMatrix();
	glRotatef(text_angle, 0, 1, 0);
	text_angle += 1;
	glTranslatef(-5, 0, 0);
	glfDraw3DSolidString("GLF Library");
	glPopMatrix();


	// Go to 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw bitmapped text
	glDisable(GL_LIGHTING);
	glfStartBitmapDrawing();
	glTranslatef(-0.6f, 0.6f, 0);
	glfDrawBString("This is Win32 demo of GLF library");
	glfStopBitmapDrawing();
	glEnable(GL_LIGHTING);

	// Go back in 3D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-7, 7, -5, 5, 10, 300);
	glMatrixMode(GL_MODELVIEW);

	SwapBuffers(*hDC); /* Swap screen buffers */
}

// Main initialization
void Init()
{
	glClearColor(0, 0, 0, 1);

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Enable Light N0
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	// Enable lighting
	glEnable(GL_LIGHTING);

	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
	
	// GLF initialization and font loading
	glfInit();
	font1 = glfLoadFont("../../fonts/techno1.glf");
	font2 = glfLoadBMFFont("../../fonts/fixedsys.bmf");
}

// Set projection
void setProjection(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-7, 7, -5, 5, 10, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void resize(void)
{
    glViewport(0, 0, winWidth, winHeight);
    setProjection();
}

void setupPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	/* size of this pfd */
		1,				/* version num */
		PFD_DRAW_TO_WINDOW |
		PFD_DOUBLEBUFFER |
		PFD_SUPPORT_OPENGL,		/* support OpenGL */
		16,				/* pixel type */
		0,				/* 8-bit color depth */
		0, 0, 0, 0, 0, 0,		/* color bits (ignored) */
		0,				/* no alpha buffer */
		0,				/* alpha bits (ignored) */
		0,				/* no accumulation buffer */
		0, 0, 0, 0,			/* accum bits (ignored) */
		16,				/* depth buffer */
		0,				/* no stencil buffer */
		0,				/* no auxiliary buffers */
		PFD_MAIN_PLANE,			/* main layer */
		0,				/* reserved */
		0, 0, 0,			/* no layer, visible, damage masks */
	};

	int SelectedPixelFormat;
	BOOL retVal;

	SelectedPixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (SelectedPixelFormat == 0)
	{
		(void) MessageBox(WindowFromDC(hDC),
		"Failed to find acceptable pixel format.",
		"OpenGL application error",
		MB_ICONERROR | MB_OK);
		exit(1);
    }

	retVal = SetPixelFormat(hDC, SelectedPixelFormat, &pfd);
	if (retVal != TRUE)
	{
		(void) MessageBox(WindowFromDC(hDC),
			"Failed to set pixel format.",
			"OpenGL application error",
			MB_ICONERROR | MB_OK);
		exit(1);
	}
}

LRESULT APIENTRY WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
	static UINT timer;
	static int omx, omy, mx, my;
  
	switch (message)
	{
		case WM_CREATE:
			timer = SetTimer(hWnd, 1, 1, NULL);
			return 0;
		case WM_DESTROY:
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hGLRC);
			KillTimer(hWnd, timer);
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
		if (hGLRC)
		{
			winWidth = (int) LOWORD(lParam);
			winHeight = (int) HIWORD(lParam);
			resize();
			return 0;
    		}
		case WM_PAINT:
	    if (hGLRC)
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			Draw(&hDC);
  			EndPaint(hWnd, &ps);
			return 0;
	    }
	    break;

		// Timer event
		case WM_TIMER:
			InvalidateRect(hWnd, NULL, FALSE);
			return 0;

		case WM_CHAR:
	    switch ((int)wParam) 
		{
			case VK_ESCAPE: /* Esc is pressed */
				DestroyWindow(hWnd);
				return 0;
      		default:
		        break;
		}
	    break;
		default:
			break;
   }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

/* Main Function */
int APIENTRY WinMain(
    HINSTANCE hCurrentInst,
    HINSTANCE hPreviousInst,
    LPSTR lpszCmdLine,
    int nCmdShow)
{
	WNDCLASS wndClass;
	HWND hWnd;
	DWORD dwExStyle;
	MSG msg;
	HDC hdc;

	/* Get current screen resolution */
	hdc = GetDC(NULL);  
	winWidth = GetDeviceCaps(hdc, HORZRES);
	winHeight = GetDeviceCaps(hdc, VERTRES);


	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = (WNDPROC) WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hCurrentInst;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className;
	RegisterClass(&wndClass);

	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	/* Create a window of the previously defined class */
	hWnd = CreateWindowEx(dwExStyle,
		className,		/* Window class's name */
		windowName,		/* Title bar text */
		/* The window's style */
		WS_OVERLAPPEDWINDOW |
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		winX, winY,		/* Position */
		winWidth, winHeight,	/* Size */
		NULL,			/* Parent window's handle */
		NULL,			/* Menu handle */
		hCurrentInst,		/* Instance handle */
		NULL);			/* No additional data */


	hDC = GetDC(hWnd);
	hDCFrontBuffer = hDC;
	setupPixelFormat(hDC);
	hGLRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hGLRC);

	/* Map the window to the screen */
	ShowWindow(hWnd, nCmdShow);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	Init();
	setProjection();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ReleaseDC(hWnd, hDC);
	return msg.wParam;
}
