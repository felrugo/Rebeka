#ifndef REBUISYSTEM
#define REBUISYSTEM

#include "..\RebGraphic\IRenderDevice.h"

class RebUISystem
{
	IRenderDevice * IRD;

public:
	RebUISystem(IRenderDevice * sird);
};

#endif