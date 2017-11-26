#pragma once
#include "Shape.h"
enum Mode
{
	line,
	rectangle,
	ellipse,
};
class Paint
{
public:
	Paint(){};
	~Paint(){};
	static CShape* create(Mode mode)
	{
		switch (mode)
		{
		case line:
			return new CLine();
			break;
		case rectangle:
			return new CRectangle();
			break;
		case ellipse:
			return new CEllipse();
			break;
		default:
			return NULL;
			break;
		}
	}

};