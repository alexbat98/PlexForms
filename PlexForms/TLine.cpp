#include "TLine.h"

//TLine::TLine() : TBase(LINE, "", 10)
//{
//	this->left = nullptr;
//	this->right = nullptr;
//}

TLine::TLine(TPoint * left, TPoint * right) : TBase(LINE, left->getName() + " " + right->getName(), 7)
{
	this->left = left;
	this->right = right;
}

TLine::TLine(const TLine & src) : TBase(LINE, src.left->getName() + " " + src.right->getName(), 7)
{
	this->left = src.left;
	this->right = src.right;

	this->fType = src.fType;
	this->name = src.name;
	this->clickableRadius = src.clickableRadius;
	this->isVisible = src.isVisible;
	this->color = src.color;
	this->thickness = src.thickness;
	this->multiplicity = src.multiplicity;
}

TLine & TLine::operator=(const TLine & src)
{
	this->left = src.left;
	this->right = src.right;

	this->fType = src.fType;
	this->name = src.name;
	this->clickableRadius = src.clickableRadius;
	this->isVisible = 1;
	this->color = 0;
	this->thickness = src.clickableRadius;
	this->multiplicity = 1;

	return *this;
}

TLine::~TLine()
{
	//left = nullptr;
	//right = nullptr;
}

void TLine::reserve()
{
	TBase *tmp = left;
	left = right;
	right = tmp;

	int space = name.find(" ");
	std::string part = name.substr(0, space);
	name.erase(0, space + 1);
	name = name + " " + part;
}

void TLine::show(System::Drawing::Graphics ^ g)
{
	if (isVisible == 1)
	{
		uint8_t red = (color & 0x00FF0000) >> 16;
		uint8_t green = (color & 0x0000FF00) >> 8;
		uint8_t blue = (color & 0x000000FF);

		g->DrawLine(gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(red, green, blue), (float)thickness),
			((TPoint *)left)->getX(),
			((TPoint *)left)->getY(),
			((TPoint *)right)->getX(),
			((TPoint *)right)->getY());
	}
}

void TLine::move(int dx, int dy)
{
	if (left->getType() == LINE)
	{
		((TLine *)(left))->move(dx, dy);
	}
	else
	{
		((TPoint *)(left))->move(dx, dy);
	}

	if (right->getType() == LINE)
	{
		((TLine *)(right))->move(dx, dy);
	}
	else
	{
		((TPoint *)(right))->move(dx, dy);
	}
}

void TLine::updateMultiplicity(int flag)
{
	multiplicity++;
	if (multiplicity == 4) multiplicity = 1;
}

int TLine::distance(int x, int y)
{
	float a, b, c, h;

	int lx = ((TPoint*)left)->getX();
	int ly = ((TPoint*)left)->getY();
	int rx = ((TPoint*)right)->getX();
	int ry = ((TPoint*)right)->getY();

	a = (float)sqrt((lx - x) * (lx - x) + (ly - y) * (ly - y));
	b = (float)sqrt((rx - x) * (rx - x) + (ry - y) * (ry - y));
	c = (float)sqrt((lx - rx) * (lx - rx) + (ly - ry) * (ly - ry));
	float p = (float)0.5 * (a + b + c);

	float area = sqrt(p * (p - a) * (p - b) *  (p - c));
	h = area * 2 / c;

	if (h <= clickableRadius && a >= 20 && b >= 20 &&
		((x >= lx && y >= ly && x <= rx && y <= ry) ||
		(x <= lx && y <= ly && x >= rx && y >= ry) ||
		(x >= lx && y <= ly && x <= rx && y >= ry) ||
		(x <= lx && y >= ly && x >= rx && y <= ry)))
		return 1;
	else
		return 0;
}

void TLine::setLeft(TBase * newLeft)
{
	left = newLeft;
}

void TLine::setRight(TBase * newRight)
{
	right = newRight;
}

TBase* TLine::getLeft()
{
	return left;
}

TBase* TLine::getRight()
{
	return right;
}

std::string TLine::toString()
{
	std::string res = "";
	res += "LINE|";
	res += name + '|';
	res += std::to_string(isVisible) + '|';
	res += std::to_string(clickableRadius) + '|';
	res += std::to_string(thickness) + '|';
	res += std::to_string(color) + '|';
	res += std::to_string(multiplicity) + '|';

	return res;
}

TLine::TLine(std::string src)
{
	std::string words[8];
	int k;

	strToWords(src, words, k);
	this->fType = LINE;
	this->name = words[1];
	this->isVisible = stoi(words[2]);
	this->clickableRadius = stoi(words[3]);
	this->thickness = stoi(words[4]);
	this->color = stoi(words[5]);
	this->multiplicity = stoi(words[6]);

	left = nullptr;
	right = nullptr;
}
