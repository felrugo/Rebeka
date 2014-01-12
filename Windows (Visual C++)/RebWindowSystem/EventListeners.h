#ifndef EVENTLISTENERS_H
#define EVENTLISTENERS_H

#include "EventStruct.h"

class IKeyListener
{
public:
	virtual void onKeyEvent(RebEvent keyev) {}
};

class IMouseListener
{
public:
	virtual void onMKeyEvent(RebEvent mev) {}

	virtual void onMMotionEvent(RebEvent mev) {}
};


#endif