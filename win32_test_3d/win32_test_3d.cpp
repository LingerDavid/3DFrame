#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#include "lg3D\lgVector.h"
#include "lg3D\lgFace.h"
#include "lg3D\lgCamera.h"
#include "lg3D\lgPoint.h"
#include "lg3D\lgDisplay.h"
#include "lg3D\lgMatrix.h"
#include "lg3D\lgDisplay.h"
#include "lg3D\lgTriangle.h"
#include "lg3D\lgObject.h"
#include "lg3D\lgIO.h"
#include "lg3D\lgTexture.h"

#ifndef PI
#define PI 3.1415926
#endif

#define WND_WIDTH 800
#define WND_HEIGHT 700

lgCamera glgCamera;
lgDisplay glgDisplay;
lgObject glgObject, glgObject2, glgObject3, glgObject4, glgTerrian;
lgCamera::lgWindow glgWindow;
lgIO glgIO;
lgTexture glgTexture;

double gStep = PI / 18;

#define ANIMATE_TIMER 0

LRESULT CALLBACK WndProc(HWND hwnd,UINT Msg,
						 WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
			LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASS wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[]=TEXT("Matrix");
	wndclass.cbClsExtra = NULL;
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance =hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("RegisterClass failed\n"), NULL, 0);
		return -1;
	}
	hwnd=CreateWindow(szAppName,
		TEXT("Matrix"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	glgIO.lgGetBitmapFromFile("texture/wood02.bmp", glgTexture.m_lgBmpTexture[0]);
	glgIO.lgGetBitmapFromFile("texture/earthcolormap01.bmp", glgTexture.m_lgBmpTexture[1]);
	glgIO.lgGetBitmapFromFile("texture/wall01.bmp", glgTexture.m_lgBmpTexture[2]);

	lgEluer tlgEeluer;
	glgCamera.lgSetWindowOrg(200, 100);
	glgCamera.lgSetWorldPoint(lgPoint(0.0, 0.0, 0.0));

	glgObject.lgCreateStandardCube(1);
	glgObject.lgSetWorldPoint(lgPoint(0, 0, 5));
	glgObject.lgCalPrimitiveVertexNormal();
	glgObject.lgInitAllFacesTexture(&glgTexture);
	glgObject.lgRotate(45.0 / 180 * PI, lgVector(0.0, 0.0, 0.0, 0.0, 1.0, 0.0));

	glgTerrian.lgCreateTerrian(30, 30, glgTexture, lgTexture::BMP, 1);
	glgTerrian.lgSetWorldPoint(lgPoint(0, 0, 5));
	glgTerrian.lgCalPrimitiveVertexNormal();

	glgIO.lgGetObjectFromPLGFile("lgModels/lgPLG/tank1.plg", glgObject3);
	glgObject3.lgSetWorldPoint(lgPoint(0.0, 0.0, 20));
	glgObject3.lgCalPrimitiveVertexNormal();
	glgObject3.lgInitAllFacesTexture(&glgTexture);
	glgObject3.lgZoom(lgVector(0.0, 0.0, 0.0, 0.1, 0.0, 0.0));
	glgObject3.lgZoom(lgVector(0.0, 0.0, 0.0, 0.0, 0.1, 0.0));
	glgObject3.lgZoom(lgVector(0.0, 0.0, 0.0, 0.0, 0.0, 0.1));

	glgIO.lgGetObjectFromPLGFile("lgModels/lgPLG/towerg1.plg", glgObject2);
	glgObject2.lgSetWorldPoint(lgPoint(0.0, -2.0, 15));
	glgObject2.lgInitAllFacesTexture(&glgTexture);
	glgObject2.lgCalPrimitiveVertexNormal();
	glgObject2.lgZoom(lgVector(0.0, 0.0, 0.0, 0.1, 0.0, 0.0));
	glgObject2.lgZoom(lgVector(0.0, 0.0, 0.0, 0.0, 0.1, 0.0));
	glgObject2.lgZoom(lgVector(0.0, 0.0, 0.0, 0.0, 0.0, 0.1));


	glgIO.lgGetObjectFromASCFile("lgModels/lgASC/sphere01.asc", glgObject4);
	glgObject4.lgSetWorldPoint(lgPoint(0.0, 0.0, 10.0));
	glgObject4.lgGetBoundingRectBox();
	glgObject4.lgCalPrimitiveVertexNormal();
	glgObject4.lgInitAllFacesTexture(&glgTexture);

	glgWindow = glgCamera.lgGetWindow();

	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);

	//SetTimer(hwnd, ANIMATE_TIMER, 300, NULL);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void RotatePixel(lgPoint& tlgPoint, double angle)
{
	lgVector tlgVector(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	tlgPoint.lgRotate(angle, tlgVector);
}

void RotateTriangle(lgTriangle& tlgTriangle, double angle)
{
	lgVector tlgVector(0.0, 0.0, 5.0, 0.0, 1.0, 5.0);
	tlgTriangle.lgRotate(angle, tlgVector);
}

void MoveTriangle(lgTriangle& tlgTriangle)
{
	lgVector tlgVector(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	tlgTriangle.lgMove(tlgVector);
}

void RotateObject(lgObject&  tlgObject, double angle, lgVector tlgVector)
{
	tlgVector.lgNormalize();
	tlgObject.lgRotate(angle, tlgVector);
}

void MoveObject(lgObject& tlgObject)
{
	lgVector tlgVector(0.0, 0.0, 0.0, 0.0, -0.1, 0.0);
	tlgObject.lgMove(tlgVector);
}

void RotateCamera(lgCamera& tlgCamera)
{
	static double minX = -5.0, maxX = 5.0, curX = 0.0, step = 0.5,
		minAngle = -PI / 10, maxAngle = PI / 10, curAngle = 0.0, stepAngle = PI / 100;
	static int dir = 1;
	lgEluer tlgEluer;
	curX = curX + dir * step;
	curAngle = curAngle + (-dir) * stepAngle;
	if (curX > maxX)
	{
		dir = -dir;
		curX = maxX;
		curAngle = minAngle;
	}
	else if (curX < minX)
	{
		dir = -dir;
		curX = minX;
		curAngle = maxAngle;
	}
	glgCamera.lgSetWorldPoint(lgPoint(curX, 0.0, 0.0));
	tlgEluer.lgSetHeading(curAngle);
	glgCamera.lgSetEluer(tlgEluer);
}

void DrawBmpPixels(void* dc, const lgBmp& tlgBmp)
{
	int r = tlgBmp.m_lgBmpInfo.bmiHeader.biHeight,
		c = tlgBmp.m_lgBmpInfo.bmiHeader.biWidth,
		bit = tlgBmp.m_lgBmpInfo.bmiHeader.biBitCount,
		i = 0, 
		j = 0, 
		red = 0,
		green = 0, 
		blue = 0;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			red = tlgBmp.m_lgBuffer[(i * c + j) * bit / 8 + 2];
			green = tlgBmp.m_lgBuffer[(i * c + j) * bit / 8 + 1];
			blue = tlgBmp.m_lgBuffer[(i * c + j) * bit / 8];
			SetPixel((HDC)dc, j, i,  RGB(red, green, blue));
		}
	}
}


LRESULT CALLBACK WndProc(HWND hWnd,UINT Msg,
						 WPARAM wParam,LPARAM lParam)
{
	enum
	{
		LBUTTONDOWN,
		LBUTTONUP
	};
	static bool first=TRUE;
	int SCREEN_WIDTH,SCREEN_HEIGHT;
	PAINTSTRUCT ps;
	HDC hdc, comphdc;
	HBITMAP hbitmap;
	static int state = LBUTTONUP;
	int dirx = 1, diry = 1;

	RECT rect,rt, windowRect;

	rect.left = glgWindow.m_WindowX;
	rect.top = glgWindow.m_WindowY;
	rect.right = rect.left + glgWindow.m_WindowWidth;
	rect.bottom = rect.top + glgWindow.m_WindowHeight;

	rt.left = rt.top = 0;
	rt.right = rect.right - rect.left;
	rt.bottom = rect.bottom - rect.top;


	GetClientRect(hWnd, &windowRect);

	static lgPOINT mps, nmps;
	lgEluer tEluer;
	lgPOINT pts[4];
	pts[0].x = rect.left;
	pts[0].y = rect.top;
	pts[1].x = rect.left;
	pts[1].y = rect.bottom;
	pts[2].x = rect.right;
	pts[2].y = rect.bottom;
	pts[3].x = rect.right;
	pts[3].y = rect.top;

	rect.left += 1;
	rect.top += 1;
	switch(Msg)
	{
	case WM_SIZE:
		//ÖÃÖÐ
		if(first)
		{
			SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
			SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
			MoveWindow(hWnd,(SCREEN_WIDTH-WND_WIDTH) / 2,(SCREEN_HEIGHT-WND_HEIGHT) / 2,WND_WIDTH,WND_HEIGHT,TRUE);
			first = FALSE;
		}
		return 0;
	case WM_TIMER:
		//MoveObject(glgObject);
		//RotateObject(glgObject, gStep, lgVector(0.0, 0.0, 0.0, 1.0, 0.0, 0.0));
		RotateCamera(glgCamera);
		//RotateObject(glgObject2, gStep, lgVector(0.0, 0.0, 0.0, 0.0, 1.0, 0.0));
		//RotateObject(glgObject3, gStep, lgVector(0.0, 0.0, 0.0, 0.0, 0.0, 1.0));
		//RotateObject(glgObject4, gStep, lgVector(0.0, 0.0, 0.0, 0.0, 1.0, 0.0));
		InvalidateRect(hWnd, &rect, FALSE);
		return 0;
	case WM_LBUTTONDOWN:
		mps.x = LOWORD(lParam);
		mps.y = HIWORD(lParam);
		if (mps.x >= rect.left + windowRect.left
			&& mps.x <= rect.right + windowRect.left
			&& mps.y >= rect.top + windowRect.top
			&& mps.y <= rect.bottom + windowRect.top)
		{
			SetCursor(LoadCursor(nullptr, IDC_HAND));
			state = LBUTTONDOWN;

		}
		return 0;
	case WM_LBUTTONUP:
		if (state != LBUTTONUP)
		{
			state = LBUTTONUP;
		}
		return 0;
	case WM_MOUSEMOVE:
		nmps.x = LOWORD(lParam);
		nmps.y = HIWORD(lParam);
		if (nmps.x >= rect.left + windowRect.left
			&& nmps.x <= rect.right + windowRect.left
			&& nmps.y >= rect.top + windowRect.top
			&& nmps.y <= rect.bottom + windowRect.top)
		{
			SetCursor(LoadCursor(nullptr, IDC_HAND));
			if (state == LBUTTONDOWN)
			{
				if (nmps.x - mps.x < 0)
				{
					dirx = -1;
				}
				else
				{
					dirx = 1;
				}
				if (nmps.y - mps.y < 0)
				{
					diry = -1;
				}
				else
				{
					diry = 1;
				}
				RotateObject(glgObject4, (int)(nmps.y - mps.y) * diry % 360 * PI * 0.5 / 180, lgVector(0.0, 0.0, 0.0, -1 * diry, 0.0, 0.0));
				RotateObject(glgObject4, ((int)(nmps.x - mps.x) * dirx % 360 * PI * 0.5 / 180), lgVector(0.0, 0.0, 0.0, 0.0, -1 * dirx, 0.0));
				InvalidateRect(hWnd, &rect, FALSE);
				mps = nmps;
			}
		}
		return 0;
	case WM_PAINT:
		// TODO: Add any drawing code here...
		hdc = BeginPaint(hWnd, &ps);
		comphdc = CreateCompatibleDC(hdc);
		hbitmap = CreateCompatibleBitmap(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
		SelectObject(comphdc, hbitmap);
		FillRect(comphdc, &windowRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//DrawBmpPixels(comphdc, glgTexture.m_lgBmpTexture[0]);
		//object
		//glgTerrian.lgDraw(comphdc, glgCamera, lgTexture::BMP, 1);
		//glgObject3.lgDraw(comphdc, glgCamera, lgTexture::BMP, 0);
		//glgObject.lgDraw(comphdc, glgCamera, lgTexture::BMP, 0);
		//glgObject2.lgDraw(comphdc, glgCamera, lgTexture::BMP, 2);
		glgObject4.lgDraw(comphdc, glgCamera, lgTexture::BMP, 0);
		StretchBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, comphdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SRCCOPY);
		//window borber
		glgDisplay.lgDrawLine(hdc, pts[0], pts[1]);
		glgDisplay.lgDrawLine(hdc, pts[1], pts[2]);
		glgDisplay.lgDrawLine(hdc, pts[2], pts[3]);
		glgDisplay.lgDrawLine(hdc, pts[3], pts[0]);
		glgDisplay.lgDrawWorldAxises(hdc, glgCamera);
		DeleteObject(hbitmap);
		DeleteObject(comphdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		return 0;
	}
	return DefWindowProc(hWnd,Msg,wParam,lParam);
}
