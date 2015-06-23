#ifndef REBEKA_H
#define REBEKA_H



#include "..\RebEngine\RebEngineLoader.h"
#include "../RebGraphic/RebGraphicSystem.h"
#include "..\RebWindowSystem\RebWindowSystem.h"
#include "..\RebAudio\RebAudioSystem.h"
#include "..\RebEntitySystem\RebEntitySystem.h"
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"
#include "..\RebSupport\RebTimer.h"
#include "..\RebSupport\RebString.h"
#include "..\RebSupport\RebVL.h"

class Rebeka : public IEngineLib
{
public:
	RebGraphicSystem rgs;
	RebAudioSystem ras;
	RebWindowSystem winsys;
	IWindowManager * winm;
	IRenderDevice * rd;
	RebEntitySystem * res;
	RebFileSystem * rfs;
	void * window;
	bool gr;
	

RebGDC * mGDC;


void Init();

void GameLoop();

void Release();
};







#endif