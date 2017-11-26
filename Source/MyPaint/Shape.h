#pragma once
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
class CShape
{
protected:
	Point batdau;
	Point ketthuc;
	Pen* pen;
	Brush* brush;
public:
	virtual CShape* Create()=0;
	virtual void Draw(Graphics*) = 0;
	virtual void SetData(Point, Point,Pen*,Brush*) = 0;
	void setPen(Pen*);
	void setBrush(Brush*);
	virtual int gettype() = 0;
	RECT* getPoint();
	Pen* getpen();
	Brush* getbrush();
	CShape();

};
// đường thẳng
class CLine : public CShape
{
public:
	CShape* Create();
	void Draw(Graphics*);
	void SetData(Point bd, Point kt,Pen*,Brush*);
	int gettype();
};
// HCN
class CRectangle :public CShape
{
public:
	CShape* Create();
	void Draw(Graphics*);
	void SetData(Point bd, Point kt,Pen*, Brush*);
	int gettype();
};
//elip
class CEllipse :public CShape
{
public:
	CShape* Create();
	void Draw(Graphics*);
	void SetData(Point bd, Point kt, Pen*, Brush*);
	int gettype();
};
class CImage :public CShape
{
	Image *img;
public:
	CShape* Create();
	void SetData(Point bd, Point kt, Pen*, Brush*);
	int gettype();
	CImage(WCHAR str[]);
	void Draw(Graphics*);
};
