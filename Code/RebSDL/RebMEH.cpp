#include "RebMEH.h"

void CreateMEH(IMEH ** meh)
{
	*meh = new RebMEH;
}

void ReleaseMEH(IMEH ** meh)
{
	delete *meh;
}


void RebMEH::AddEvent(RebEvent * Event)
{
	events.push_back(*Event);
}

void RebMEH::CallKeyListeners(RebEvent keyevent)
{
	for (unsigned int i = 0; i < keylists.size(); i++)
	{
		keylists[i]->onKeyEvent(keyevent);
	}
}

void RebMEH::CallMouseListener(RebEvent mouseevent)
{
	if(mouseevent.Type == WE_MOUSEMOTIONEVENT)
	{
		for (unsigned int i = 0; i < mouselists.size(); i++)
		{
			mouselists[i]->onMMotionEvent(mouseevent);
		}
	}
	else
	{
		for (unsigned int i = 0; i < mouselists.size(); i++)
		{
			mouselists[i]->onMKeyEvent(mouseevent);
		}
	}
}

void RebMEH::PollGameEvent(RebEvent * Event)
{
	if (events.size() > 0)
	{
	*Event = events[0];
	events.erase(events.begin());
	}
}

void RebMEH::TranslateEvent(RebEvent * Event)
{
	SDL_Event ev;
	SDL_PollEvent(&ev);
	switch (ev.type)
	{
	case SDL_QUIT:
		Event->Type = WE_QUIT;
		Event->quit.Type = Event->Type;
		Event->quit.data = &ev.quit.timestamp;
		break;
	case SDL_KEYDOWN:
		Event->Type = WE_KEYDOWNEVENT;
		Event->key.keysym.sym = ev.key.keysym.sym;
		Event->key.Type = Event->Type;
		Event->key.keysym.mod = ev.key.keysym.mod;
		Event->key.keysym.scancode = ev.key.keysym.scancode;
		Event->key.state = ev.key.state;
		CallKeyListeners(*Event);
		break;
	case SDL_KEYUP:
		Event->Type = WE_KEYUPEVENT;
		Event->key.keysym.sym = ev.key.keysym.sym;
		Event->key.Type = Event->Type;
		Event->key.keysym.mod = ev.key.keysym.mod;
		Event->key.keysym.scancode = ev.key.keysym.scancode;
		Event->key.state = ev.key.state;
		CallKeyListeners(*Event);
		break;
	case SDL_MOUSEBUTTONDOWN:
		Event->Type = WE_MOUSEKEYDOWNEVENT;
		Event->mousekey.Type = Event->Type;
		Event->mousekey.button = ev.button.button;
		Event->mousekey.padding1 = ev.button.padding1;
		Event->mousekey.padding2 = ev.button.padding2;
		Event->mousekey.state = ev.button.state;
		Event->mousekey.which = ev.button.which;
		Event->mousekey.windowID = ev.button.windowID;
		Event->mousekey.x = ev.button.x;
		Event->mousekey.y = ev.button.y;
		CallMouseListener(*Event);
		break;

	case SDL_MOUSEBUTTONUP:
		Event->Type = WE_MOUSEKEYUPEVENT;
		Event->mousekey.Type = Event->Type;
		Event->mousekey.button = ev.button.button;
		Event->mousekey.padding1 = ev.button.padding1;
		Event->mousekey.padding2 = ev.button.padding2;
		Event->mousekey.state = ev.button.state;
		Event->mousekey.which = ev.button.which;
		Event->mousekey.windowID = ev.button.windowID;
		Event->mousekey.x = ev.button.x;
		Event->mousekey.y = ev.button.y;
		CallMouseListener(*Event);
		break;
	case SDL_MOUSEWHEEL:
		Event->Type = WE_MOUSEWHEELEVENT;
		Event->mousekey.Type = Event->Type;
		Event->mousekey.button = ev.button.button;
		Event->mousekey.padding1 = ev.button.padding1;
		Event->mousekey.padding2 = ev.button.padding2;
		Event->mousekey.state = ev.button.state;
		Event->mousekey.which = ev.button.which;
		Event->mousekey.windowID = ev.button.windowID;
		Event->mousekey.x = ev.button.x;
		Event->mousekey.y = ev.button.y;
		CallMouseListener(*Event);
		break;
	case SDL_MOUSEMOTION:
		Event->Type = WE_MOUSEMOTIONEVENT;
		Event->mousekey.Type = Event->Type;
		Event->mousemot.state = ev.motion.state;
		Event->mousemot.which = ev.motion.which;
		Event->mousemot.windowID = ev.motion.windowID;
		Event->mousemot.x = ev.motion.x;
		Event->mousemot.xrel = ev.motion.xrel;
		Event->mousemot.y = ev.motion.y;
		Event->mousemot.yrel = ev.motion.yrel;
		CallMouseListener(*Event);
		break;
	default:
		Event->Type = WE_GAMEEVENT;
		PollGameEvent(Event);
		break;
	}
}


void RebMEH::RegisterKeyEventListener(IKeyListener* ikl)
{
	keylists.push_back(ikl);
}

void RebMEH::UnRegisterKeyEventListener(IKeyListener* ikl)
{
	for (unsigned int i = 0; i < keylists.size(); i++)
	{
		if (keylists[i] = ikl)
		{
			keylists.erase(keylists.begin() + i);
		}
	}
}


void RebMEH::RegisterMouseEventListener(IMouseListener* iml)
{
	mouselists.push_back(iml);
}

void RebMEH::UnRegisterMouseEventListener(IMouseListener* iml)
{
	for (unsigned int i = 0; i < mouselists.size(); i++)
	{
		if (mouselists[i] = iml)
		{
			mouselists.erase(mouselists.begin() + i);
		}
	}
}


void RebMEH::Init()
{
}

void RebMEH::Release()
{
}

RebMEH::~RebMEH()
{
	Release();
}