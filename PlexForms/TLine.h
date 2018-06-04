#pragma once
#include "TBase.h"
#include "TPoint.h"
#include "strToWords.h"

class TLine :
	public TBase
{
private:
	TBase *left;
	TBase *right;

	friend void strToWords(std::string src, std::string *words, int &size);
public:
	//TLine();
	TLine(TPoint *left, TPoint *right);
	TLine(const TLine &src);
	TLine(std::string src);
	TLine& operator=(const TLine &src);
	~TLine();

	void reserve();
	void show(System::Drawing::Graphics^ g);
	void move(int dx, int dy);
	void updateMultiplicity(int flag = 0);
	int distance(int cx, int cy);

	void setLeft(TBase *newLeft);
	void setRight(TBase *newRight);

	TBase* getLeft();
	TBase* getRight();

	std::string toString();
};