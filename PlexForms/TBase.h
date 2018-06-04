#pragma once
#include "FTypes.h"
#include <string>

class TBase
{
protected:
	FType fType;
	std::string name;
	int isVisible;
	int clickableRadius;
	int thickness;
	int color;
	int multiplicity;
public:
	TBase();
	TBase(FType fType, std::string name, int clickableRadius = 10);
	~TBase();

	virtual void show(System::Drawing::Graphics^ g) = 0;
	virtual void move(int dx, int dy) = 0;
	virtual void updateMultiplicity(int) = 0;
	virtual int distance(int x, int y) = 0;

	int getMultiplicity();

	int getColor();
	void setColor(int color);

	int getThickness();
	void setThickness(int thickness);

	int getClickableRadius();

	void changeVisibility();

	std::string getName();

	FType getType();
};