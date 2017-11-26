#pragma once
#include <Windows.h>
#include <windows.h>
#include "resource.h"
#include "Shape.h"
#include <windowsx.h>
#include "Header.h"
#include <vector>
#include <fstream>
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
#include "RibbonFramework.h"
#include "ribbon.h"
using namespace std;

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
vector <CShape*> manghinh;
bool check;
Point diembd;
Point diemkt;
Point dichuyen;
CShape* shape = NULL;
Mode type = line;
DashStyle style = DashStyleSolid;
int size = 2;
Pen* pen = NULL;
Brush* brush = NULL;
COLORREF color;
BOOL OpenFile(HWND hwnd, WCHAR str[]);
BOOL SaveFile(HWND hwnd, WCHAR str[]);
void saveToBinaryFile(string filePath);
void loadFromBinaryFile(string filePath);
COLORREF MyCreateColor(HWND hwnd)
{
	CHOOSECOLOR cc;
	static COLORREF crCustClr[16];
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)crCustClr;
	cc.rgbResult = RGB(0, 0, 0);
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	ChooseColor(&cc);
	return cc.rgbResult;
}
void VeHinh(Point& bd,Point& kt)
{
	if (abs(bd.X - kt.X) > abs(bd.Y - kt.Y))
	{
		if (bd.X > kt.X)
			kt.X = bd.X - abs(bd.Y - kt.Y);
		else
			kt.X = bd.X + abs(bd.Y - kt.Y);
	}
	else
	{
		if (bd.Y > kt.Y)
			kt.Y = bd.Y - abs(bd.X - kt.X);
		else
			kt.Y = bd.Y + abs(bd.X - kt.X);
	}
}
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, int Show)
{
	CoInitialize(NULL);
	MSG	msg;
	HWND hwnd;
	WNDCLASS wc;
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Paint";
	wc.hInstance = hIns;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = 0;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(hIns,MAKEINTRESOURCE(IDI_ICON1));
	RegisterClass(&wc);
	hwnd = CreateWindow(L"Paint", L"Paint", WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hIns, NULL);
	ShowWindow(hwnd, Show);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HMENU menu;
	static int select = ID_DRAWSHAPE_LINE;
	static WCHAR str[255];
	//pen = new Pen(Color(255, 0, 0, 0), size);
	switch (msg)
	{
	case WM_CREATE:
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		InitializeFramework(hwnd);
		break;
	case WM_LBUTTONDOWN:
	{
					diembd.X = GET_X_LPARAM(lParam);
					diembd.Y = GET_Y_LPARAM(lParam);
					shape = Paint::create(type);
					check = true;
					SetCapture(hwnd);
	}
		break;
	case WM_MOUSEMOVE:
	{
						 if (check == true)
						 {
							 dichuyen.X = GET_X_LPARAM(lParam);
							 dichuyen.Y = GET_Y_LPARAM(lParam);
							 if (type == rectangle || type == ellipse)
								 if (wParam&MK_SHIFT)							
									VeHinh(diembd,dichuyen);
							 InvalidateRect(hwnd, NULL, FALSE);
						 }
	}
		break;
	case WM_LBUTTONUP:
	{
						 ReleaseCapture();
						 check = false;
						 diemkt.X = GET_X_LPARAM(lParam);
						 diemkt.Y = GET_Y_LPARAM(lParam);
						 pen = new Pen(Color(255, 0, 0, 0), size);
						 pen->SetDashStyle(style);
						 shape = Paint::create(type);
						 if (type == rectangle || type == ellipse)
							if (wParam&MK_SHIFT)							
							 		VeHinh(diembd,diemkt);
						 shape->SetData(diembd, diemkt,pen,brush);
						 manghinh.push_back(shape);
						 InvalidateRect(hwnd, NULL, FALSE);
	}
		break;
	case WM_PAINT:
	{
					 hdc = BeginPaint(hwnd, &ps);
					 RECT rect;
					 GetClientRect(hwnd, &rect);
					 HDC hdc1 = CreateCompatibleDC(hdc);
					 HBITMAP bitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
					 SelectObject(hdc1, bitmap);
					 FillRect(hdc1, &rect, (HBRUSH)(COLOR_WINDOW + 1));
					 Graphics* graphics = new Graphics(hdc1);
					 for (int i = 0; i < manghinh.size(); i++)
					 {
						 manghinh[i]->Draw(graphics);
					 }
					 if (check == true)
					 {
						 pen = new Pen(Color(255, 0, 0, 0),size);
						 pen->SetDashStyle(style);
						 shape->SetData(diembd, dichuyen, pen, brush);
						 shape->Draw(graphics);
					 }
					 BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdc1, 0, 0, SRCCOPY);
					 delete graphics;
					 EndPaint(hwnd, &ps);
	}
		break;
	case WM_COMMAND:
	{
					   int id = LOWORD(wParam);
					   int event = HIWORD(wParam);
					   switch (id)
					   {
					   case ID_FILE_NEW:
						   manghinh.clear();
						   InvalidateRect(hwnd, NULL, TRUE);
						   break;
					   case ID_FILE_OPEN:
						   OpenFile(hwnd, str); 
						   manghinh.clear();
						   shape = new CImage(str);
						   manghinh.push_back(shape);
						   InvalidateRect(hwnd, NULL, 0);
						   break;
					   case ID_FILE_SAVE:
						   SaveFile(hwnd, str);
						   break;
					   case ID_FILE_EXIT:
						   DestroyWindow(hwnd);
						   break;
					   case ID_EDIT_UNDO:
						   manghinh.pop_back();
						   InvalidateRect(hwnd, NULL, TRUE);
						   break;
					   case ID_EDIT_CLEAR:
						   manghinh.clear();
						   InvalidateRect(hwnd, NULL, TRUE);
					   case ID_DRAWSHAPE_LINE:
						   type = line;
						   break;
					   case ID_DRAWSHAPE_RECTANGLE:
						   type = rectangle;
						   break;
					   case ID_DRAWSHAPE_ELLIPSE:
						   type = ellipse;
						   break;
					   case ID_STYLE_DASH:
						   style = Gdiplus::DashStyle::DashStyleDash;
						   break;
					   case ID_STYLE_DOT:
						   style = Gdiplus::DashStyle::DashStyleDot;
						   break;
					   case ID_STYLE_SOLID:
						   style = Gdiplus::DashStyle::DashStyleSolid;
						   break;
					   case ID_STYLE_DASHDOT:
						   style = Gdiplus::DashStyle::DashStyleDashDot;
						   break;
					   case ID_SIZE_1:
						   size = 2;
						   break;
					   case ID_SIZE_2:
						   size = 4;
						   break;
					   case ID_SIZE_3:
						   size = 6;
						   break;
					   }
					   
	}
		break;
	case WM_DESTROY:
	{
					   GdiplusShutdown(gdiplusToken);
					   DestroyFramework();
					   PostQuitMessage(0);
	}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
BOOL OpenFile(HWND hwnd, WCHAR str[])

{
	OPENFILENAMEW file = { 0 };
	WCHAR sz[255];
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	file.hwndOwner = hwnd;
	file.lStructSize = sizeof(file);
	file.lpstrFile = sz;
	file.lpstrFile[0] = L'\0';
	file.lpstrFilter = L"image(*.png)\0*.png\0All Files (*.*)\0*.*\0";
	file.nMaxFile = sizeof(sz);
	file.nFilterIndex = 1;
	if (!GetOpenFileName(&file))
		return FALSE;
	wcscpy(str, file.lpstrFile);
	return TRUE;
}
BOOL SaveFile(HWND hwnd, WCHAR str[])
{
	OPENFILENAMEW filename = { 0 };
	WCHAR sz[255] = L"*.png";
	filename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	filename.hwndOwner = hwnd;
	filename.lStructSize = sizeof(filename);
	filename.lpstrFile = sz;
	filename.lpstrFilter = L"image(*.png)\0*.png\0All Files (*.*)\0*.*\0";
	filename.nMaxFile = sizeof(sz);
	filename.nFilterIndex = 1;
	if (!GetSaveFileName(&filename))
		return FALSE;
	wcscpy(str, filename.lpstrFile);
	return TRUE;
}
