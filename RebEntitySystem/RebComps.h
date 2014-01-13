
#ifndef REBCOMPS_H
#define REBCOMPS_H


#include "RebEntity.h"




class CompInput : public Component
{
protected:
	IMEH * ievh;
public:
	std::string GetType()
	{
		return "CompInput";
	}
};


class CompInpKey : public CompInput, public IKeyListener
{
public:
	CompInpKey(IMEH* sim)
	{
		ievh = sim;
	}

	std::string GetID()
	{
		return "CompInpKey";
	}

	void onKeyEvent(RebEvent * re)
	{

	}

};



#endif