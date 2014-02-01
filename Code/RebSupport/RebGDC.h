#ifndef REBGDC_H
#define REBGDC_H

#include "../RebRenderer/IRenderer.h"
#include "..\RebWindowSystem\RebWindowSystem.h"
#include "..\RebAudio\RebAudioSystem.h"
#include "..\RebEntitySystem\RebEntitySystem.h"

class RebGDC
{
public:
	IWindowManager * winm;
	IRenderDevice * rd;
	IMEH * meh;
	void * window;
	RebGDC()
	{
		winm = 0;
		rd = 0;
		meh = 0;
		window = 0;
	}
};


#endif