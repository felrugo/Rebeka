#ifndef REBMEH_H
#define REBMEH_H
#include "..\RebWindowSystem\IMEH.h"
#include "SDL.h"
#include <vector>

class RebMEH : public IMEH
{
	std::vector<RebEvent> events;
	std::vector<IKeyListener*> keylists;
	std::vector<IMouseListener*> mouselists;

	bool runing;

public:
	void CallKeyListeners(RebEvent keyevent);

	void CallMouseListener(RebEvent mouseevent);

	void Init();

	void TranslateEvent(RebEvent * Event);

	void AddEvent(RebEvent Event);

	void ProcEvents();

	void PollGameEvent(RebEvent * Event);

	void RegisterKeyEventListener(IKeyListener* ikl);

	void UnRegisterKeyEventListener(IKeyListener* ikl);

	void RegisterMouseEventListener(IMouseListener* iml);

	void UnRegisterMouseEventListener(IMouseListener* iml);

	void Release();

	~RebMEH();
};





#endif