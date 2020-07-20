
#include <Windows.h>//import window header
#include <gl/GL.h>//import open gl header
#include <math.h>  


#pragma comment (lib, "OpenGL32.lib")  //setting library

#define WINDOW_TITLE "Practical 2 Exercise" //setting window name

double moveX = 0;
double moveY = 0;
double red = 1.0;
double green = 1.0;
double blue = 1.0;
int qNo = 1;
double starD = 0;


#define MAX_CHAR        128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;

		lists = glGenLists(MAX_CHAR);

		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) //window listener check wheater receive any message
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);// vk = virtual key can right click go to definition go all the key
		else if (wParam == VK_LEFT)
		{
			if (qNo == 2)
				starD -= 45.0;
			else
			moveX -= 0.2;
			

			
		}
		else if (wParam == VK_RIGHT)
		{
			if (qNo == 2)
				starD += 45.0;
			else
			moveX += 0.2;
			
		}
		else if (wParam == VK_UP)
		{
			moveY += 0.1;
		}
		else if (wParam == VK_DOWN)
		{
			moveY -= 0.1;
		}
		else if (wParam == 'R')
		{
			red = 1.0;
			green = 0;
			blue = 0;
		}
		else if (wParam == 'G')
		{
			red = 0;
			green = 1.0;
			blue = 0;
		}
		else if (wParam == 'B')
		{
			red = 0;
			green = 0;
			blue = 1.0;
		}
		else if (wParam == VK_SPACE)
		{
			if (qNo == 2)
				starD = 0;
			else
			{
				red = 1;
				green = 1;
				blue = 1;
				moveX = 0;
				moveY = 0;
			}
			
			
		}
		else if (wParam == '1')
		{
			qNo = 1;
		}
		else if (wParam == '2')
		{
			qNo = 2;
		}
		else if (wParam == '3')
		{
			qNo = 3;
		}
		else if (wParam == '4')
		{
			qNo = 4;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;//transparency 8bit/1 byte
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;// z buffer
	pfd.cStencilBits = 0;//shadow 

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
double scalecount = 1.0;
void ques4()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.6, -0.9);
	drawString("ENTER '1', '2','3','4' to change between questions 1-4");

	glLoadIdentity();
	glScalef(scalecount,scalecount, 1.0);
	scalecount += 0.001;

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.1, 0.1);
	glVertex2f(0.1, 0.1);
	glVertex2f(0.1, -0.1);
	glVertex2f(-0.1, -0.1);
	glEnd();

}

double sred = 1;
double sgreen = 1;
double sblue = 1;


void ques2()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	int s = sys.wSecond;
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.6, -0.9);
	drawString("ENTER '1', '2','3','4' to change between questions 1-4");
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.6, -0.8);
	drawString("ENTER '<-' or '->' to to rotate,space will reset.");

	glLoadIdentity();
	glRotatef(starD, 0, 0, 1);
	

	glBegin(GL_POLYGON);
	glColor3f(sred, sgreen, sblue);
	glVertex2f(-0.243, -0.185);
	glVertex2f(-0.15, 0.1);
	glVertex2f(0.15, 0.1);
	glVertex2f(0.243,-0.185);
	glVertex2f(0, -0.362);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(sred, sgreen, sblue);
	glVertex2f(0.15, 0.1);
	glVertex2f(0.576, 0.081);
	glVertex2f(0.243, -0.185);

	glVertex2f(0.243, -0.185);
	glVertex2f(0.356, -0.596);
	glVertex2f(0, -0.362);

	glVertex2f(0, -0.362);
	glVertex2f(-0.356, -0.596);
	glVertex2f(-0.243, -0.185);

	glVertex2f(-0.243, -0.185);
	glVertex2f(-0.576, 0.081);
	glVertex2f(-0.15, 0.1);

	glVertex2f(-0.15, 0.1);
	glVertex2f(0, 0.5);
	glVertex2f(0.15, 0.1);
	glEnd();

	


	if (s % 2 == 0)
	{
		sred -= 0.00005;
	}

	else if (s % 3 == 0)
	{
		sblue -= 0.00003;
	}
	 else if (s % 4 == 0)
	{
		 sred += 0.00008;
	}
	 else if (s % 5 == 0)
	{
		 sred = 0.7;
		 sgreen = 0.5;
		 sblue = 0.6;
	}
	 else if (s % 7 == 0)
	{
		sred -= 0.0001;
		sblue += 0.0001;
		sgreen = 0.4;
	}
	 else if (s % 11 == 0)
	{
		sgreen += 0.0001;
		sblue -= 0.00005;
		sred -= 0.00005;
	}
	 
}

double rotateCount = 0;
void ques3()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.6, -0.9);
	drawString("ENTER '1', '2','3','4' to change between questions 1-4");
	

	double pi = 3.142;
	int n = 100;
	glPointSize(10.0);
	glLoadIdentity();
	glRotatef(rotateCount, 0, 0, 1);
	rotateCount += 0.02;
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2f(0.65 * cos(2 * pi / n ), 0.65 * sin(2 * pi / n ));
	glEnd();
	

	

}

void ques1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.6, -0.95);
	drawString("ENTER '1', '2','3','4' to change between questions 1-4");
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.6, -0.85);
	drawString("ENTER arrow key to move the object,space to reset.");
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.6, -0.75);
	drawString("ENTER 'R','G','B' to change pre set color.");



	glLoadIdentity();
	glTranslatef(moveX, moveY, 0);
	glBegin(GL_QUADS);
	glColor3f(red, green, blue);
	glVertex2f(-0.3, 0);
	glVertex2f(-0.3, 0.3);
	glVertex2f(0.3, 0.3);
	glVertex2f(0.3, 0);
	glEnd();


}
void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	
	if (qNo == 1)
	{
		ques1();
		scalecount = 1;
	}
	else if (qNo == 2)
	{
		glPopMatrix();
		ques2();
		scalecount = 1;
	}
	else if (qNo == 3)
	{
		glPopMatrix();
		ques3();
		scalecount = 1;
	}
	else if (qNo == 4)
	{
		glPopMatrix();
		ques4();
		
	}



	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}

//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------