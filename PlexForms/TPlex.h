#pragma once
#include "TPoint.h"
#include "TLine.h"
#include "TBase.h"

class TPlex
{
private:
	TBase *start;

	void attachToLeft(TLine *left, TLine *l);
public:
	TPlex(TLine *l = nullptr);
	TPlex(const TPlex &src);
	TPlex& operator=(const TPlex &src);
	~TPlex();

	void addLine(TLine *l);

	TLine* findLineWithPoint(std::string name);
	TLine* findLineWithPoint(int x, int y);

	TPoint* findPoint(std::string name);
	TPoint* findPoint(int x, int y);

	void movePlex(int dx, int dy);
	void movePoint(int x, int y, int dx, int dy);

	void draw(System::Drawing::Graphics^ g);

	void recolor(int color);

	void save(std::string path);
	void open(std::string path);

	void deleteLine(std::string name);

	void showPointNames(System::Drawing::Graphics^ g);
	void showNearesPointNames(System::Drawing::Graphics^ g, int x, int y);
};