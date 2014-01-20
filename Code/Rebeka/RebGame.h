#ifndef REBGAME_H
#define REBGAME_H

#include "..\IGameDLL\IGameDLL.h"
#include "../RebRenderer/IRenderer.h"
#include "..\RebWindowSystem\RebWindowSystem.h"
#include "..\RebAudio\RebAudioSystem.h"
#include "..\RebEntitySystem\RebEntitySystem.h"

class RebGame : public IGameDLL
{
	Renderer rend;
	RebAudioSystem ras;
	RebWindowSystem winsys;
	IWindowManager * winm;
	void* window;
	IRenderDevice * rd;
	RebEntitySystem res;
public:
void Init();

void GameLoop();

void Release();
};







#endif