#ifndef REBUISYSTEM
#define REBUISYSTEM

#include "..\RebRenderer\IRenderDevice.h"

class RebUISystem
{
	IRenderDevice * IRD;

public:
	RebUISystem(IRenderDevice * sird);
};

#endif