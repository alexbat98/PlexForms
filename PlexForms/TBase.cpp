#include "TBase.h"

TBase::TBase()
{

}

TBase::TBase(FType fType, std::string name, int clickableRadius)
{
	this->fType = fType;
	this->name = name;
	this->clickableRadius = clickableRadius;

	this->isVisible = 1;
	this->color = 0;
	this->thickness = clickableRadius; //подумать
	this->multiplicity = 1;
}
TBase::~TBase()
{

}

int TBase::getMultiplicity()
{
	return multiplicity;
}

int TBase::getColor()
{
	return color;
}
void TBase::setColor(int color)
{
	this->color = color;
}

int TBase::getThickness()
{
	return thickness;
}
void TBase::setThickness(int thickness)
{
	this->thickness = thickness;
}

int TBase::getClickableRadius()
{
	return clickableRadius;
}

void TBase::changeVisibility()
{
	this->isVisible = this->isVisible == 1 ? 0 : 1;
}

std::string TBase::getName()
{
	return name;
}

FType TBase::getType()
{
	return fType;
}