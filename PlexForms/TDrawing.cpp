#include "TDrawing.h"
#include "TLine.h"
#include <string>  

std::string TDrawing::getNextName()
{
	std::string res = "";
	res = nextChr;
	nextChr++;

	return res;
}

TDrawing::TDrawing()
{
	nextChr = 65;
}

TDrawing::TDrawing(const TDrawing& src)
{
	curPlex = src.curPlex;
	nextChr = src.nextChr;
}

TDrawing& TDrawing::operator=(const TDrawing& src)
{
	curPlex = src.curPlex;
	nextChr = src.nextChr;

	return *this;
}

TDrawing::~TDrawing()
{
	//
}

void TDrawing::addLine(int x1, int y1, int x2, int y2)
{
	TPoint *p1 = curPlex.findPoint(x1, y1);
	if (p1 == nullptr)
	{
		p1 = new TPoint(getNextName(), x1, y1);
	}

	TPoint *p2 = curPlex.findPoint(x2, y2);
	if (p2 == nullptr)
	{
		p2 = new TPoint(getNextName(), x2, y2);
	}

	curPlex.addLine(new TLine(p1, p2));
}
void TDrawing::deleteLine(std::string name)
{

}

void TDrawing::save(std::string path)
{
	curPlex.save(path);
}
void TDrawing::open(std::string path)
{
	curPlex.open(path);
}

void TDrawing::showPointNames(System::Drawing::Graphics^ g)
{
	curPlex.showPointNames(g);
}
void TDrawing::showNearesPointNames(System::Drawing::Graphics^ g, int x, int y)
{
	curPlex.showNearesPointNames(g, x, y);
}

void TDrawing::draw(System::Drawing::Graphics^ g)
{
	curPlex.draw(g);
}

void TDrawing::recolor(int color) 
{
	curPlex.recolor(color);
}

void TDrawing::movePoint(int x, int y, int dx, int dy)
{
	curPlex.movePoint(x, y, dx, dy);
}

void TDrawing::moveLine(std::string name, int dx, int dy)
{
	//
}

void TDrawing::moveDrawing(int dx, int dy)
{
	curPlex.movePlex(dx, dy);
}