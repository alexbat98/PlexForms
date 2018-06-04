#include "TPoint.h"

//TPoint::TPoint() : TBase(POINT, "", 10)
//{
//
//}

TPoint::TPoint(std::string name, int x, int y) : TBase(POINT, name, 10)
{
	this->x = x;
	this->y = y;
}

TPoint::TPoint(const TPoint& src) : TBase(POINT, src.name, 10)
{
	this->x = src.x;
	this->y = src.y;

	this->fType = src.fType;
	this->name = src.name;
	this->clickableRadius = src.clickableRadius;
	this->isVisible = src.isVisible;
	this->color = src.color;
	this->thickness = src.thickness;
	this->multiplicity = src.multiplicity;
}

TPoint::TPoint(std::string src)
{
	std::string words[12];
	int k;

	strToWords(src, words, k);
	this->fType = LINE;
	this->name = words[1];
	this->x = stoi(words[2]);
	this->y = stoi(words[3]);
	this->isVisible = stoi(words[4]);
	this->clickableRadius = stoi(words[5]);
	this->thickness = stoi(words[6]);
	this->color = stoi(words[7]);
	this->multiplicity = stoi(words[8]);
}

TPoint& TPoint::operator=(const TPoint& src)
{
	this->x = src.x;
	this->y = src.y;

	this->fType = src.fType;
	this->name = src.name;
	this->clickableRadius = src.clickableRadius;
	this->isVisible = src.isVisible;
	this->color = src.color;
	this->thickness = src.thickness;
	this->multiplicity = src.multiplicity;

	return *this;
}

TPoint::~TPoint()
{

}

void TPoint::show(System::Drawing::Graphics^ g)
{
	if (isVisible == 1)
	{
		uint8_t red = (color & 0x00FF0000) >> 16;
		uint8_t green = (color & 0x0000FF00) >> 8;
		uint8_t blue = (color & 0x000000FF);

		g->FillEllipse(
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(red, green, blue)),
			x - thickness,
			y - thickness,
			2 * thickness,
			2 * thickness);
	}
}

void TPoint::move(int dx, int dy)
{
	this->x += dx;
	this->y += dy;
}

void TPoint::updateMultiplicity(int flag)
{
	if (flag > 0)
		multiplicity++;
	else if (flag < 0)
		multiplicity--;

	if (multiplicity < 1)
		multiplicity = 1;
}

int TPoint::distance(int cx, int cy)
{
	int p = (x - cx) * (x - cx) + (y - cy) * (y - cy);
	if (p <= clickableRadius * clickableRadius)
		return 1;
	else
		return 0;
}

int TPoint::getX()
{
	return x;
}

int TPoint::getY()
{
	return y;
}

void TPoint::setX(int _x)
{
	x = _x;
}

void TPoint::setY(int _y)
{
	y = _y;
}

std::string TPoint::toString()
{
	std::string res = "";
	res += "POINT|";
	res += name + '|';
	res += std::to_string(x) + '|';
	res += std::to_string(y) + '|';
	res += std::to_string(isVisible) + '|';
	res += std::to_string(clickableRadius) + '|';
	res += std::to_string(thickness) + '|';
	res += std::to_string(color) + '|';
	res += std::to_string(multiplicity) + '|';

	return res;
}
