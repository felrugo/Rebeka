#ifndef RGL
#define RGL
#include "..\RebSupport\RebGDC.h"

class RebGameLogic
{
	RebGDC * mGDC;
public:
	RebGameLogic(RebGDC * gdc);
	void Update();

};


#endif