#pragma once
#include "TBase.h"
#include "strToWords.h"

class TPoint :
	public TBase
{
private:
	int x;
	int y;

	friend void strToWords(std::string src, std::string *words, int &size);
public:
	//TPoint();
	TPoint(std::string name, int x, int y);
	TPoint(const TPoint& src);
	TPoint(std::string src);
	TPoint& operator=(const TPoint& src);
	~TPoint();

	virtual void show(System::Drawing::Graphics^ g);
	virtual void move(int dx, int dy);
	virtual void updateMultiplicity(int);
	virtual int distance(int cx, int cy);

	int getX();
	int getY();
	void setX(int _x);
	void setY(int _y);

	std::string toString();
};