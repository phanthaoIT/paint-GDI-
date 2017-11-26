#include "Shape.h"
#include "Header.h"

CShape::CShape()
{
	pen = new Pen(Color(255, 0, 0, 0), 2);
	brush = new SolidBrush(Color(255, 0, 0, 0));
}

RECT* CShape::getPoint()
{
	RECT* toado = new RECT();
	toado->left = this->batdau.X;
	toado->top = this->batdau.Y;
	toado->right = this->ketthuc.X;
	toado->bottom = this->ketthuc.Y;
	return toado;
}
void CShape::setPen(Pen* pen)
{
	this->pen = pen;
}
void CShape::setBrush(Brush* brush)
{
	this->brush = brush;
}
Pen* CShape::getpen()
{
	return this->pen;
}
Brush* CShape::getbrush()
{
	return this->brush;
}

CShape* CLine::Create()
{
	return new CLine;
}
void CLine::Draw(Graphics* graphics)
{
	graphics->DrawLine(pen, batdau, ketthuc);
}
void CLine::SetData(Point bd, Point kt, Pen* pen, Brush* brush)
{
	this->batdau = bd;
	this->ketthuc = kt;
	this->pen = pen;
	this->brush = brush;
}
int CLine::gettype()
{
	return line;
}

CShape* CRectangle::Create()
{
	return new CRectangle;
}
void CRectangle::Draw(Graphics* graphics)
{
	graphics->DrawRectangle(pen, batdau.X, batdau.Y, ketthuc.X - batdau.X, ketthuc.Y - batdau.Y);
}
void CRectangle::SetData(Point bd, Point kt, Pen* pen, Brush* brush)
{
	this->batdau = bd;
	this->ketthuc = kt;
	this->pen = pen;
	this->brush = brush;
}
int CRectangle::gettype()
{
	return rectangle;
}

CShape* CEllipse::Create()
{
	return new CEllipse;
}
void CEllipse::Draw(Graphics * graphics)
{
	graphics->DrawEllipse(pen, batdau.X, batdau.Y, ketthuc.X - batdau.X, ketthuc.Y - batdau.Y);
}
void CEllipse::SetData(Point bd, Point kt, Pen* pen,Brush* brush)
{
	this->batdau = bd;
	this->ketthuc = kt;
	this->pen = pen;
	this->brush = brush;
}

int CEllipse::gettype()
{
	return ellipse;
}
void CImage::Draw(Graphics* graphics)
{
	graphics->DrawImage(img, Rect(0, 0, img->GetWidth(), img->GetHeight()));
}
CImage::CImage(WCHAR str[])
{
	img = new Image(str, 0);
}
CShape* CImage::Create()
{
	return NULL;
}
void CImage::SetData(Point bd, Point kt, Pen*, Brush*){}
int CImage::gettype(){ return 5; }