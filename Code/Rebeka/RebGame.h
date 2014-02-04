#ifndef REBGAME_H
#define REBGAME_H



#include "..\IGameDLL\IGameDLL.h"
#include "../RebRenderer/IRenderer.h"
#include "..\RebWindowSystem\RebWindowSystem.h"
#include "..\RebAudio\RebAudioSystem.h"
#include "..\RebEntitySystem\RebEntitySystem.h"
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"
#include "..\RebSupport\RebString.h"

class RebGame : public IGameDLL
{
public:
	Renderer rend;
	RebAudioSystem ras;
	RebWindowSystem winsys;
	IWindowManager * winm;
	IRenderDevice * rd;
	RebEntitySystem * res;
	RebFileSystem rfs;
	void * window;
	

RebGDC * mGDC;
void Init();

void GameLoop();

void Release();
};







#endif