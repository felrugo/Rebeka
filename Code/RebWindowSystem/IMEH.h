#ifndef IMEH_H
#define IMEH_H

#include "..\RebSupport\RebGDC.h"
#include "EventListeners.h"

class IMEH
{
public:
	virtual void Init(RebGDC * data) = 0;

	virtual void Release() = 0;

	virtual void AddEvent(RebEvent Event) = 0;

	virtual void TranslateEvent(RebEvent * Event) = 0;

	virtual void RegisterKeyEventListener(IKeyListener* ikl) = 0;

	virtual void UnRegisterKeyEventListener(IKeyListener* ikl) = 0;

	virtual void RegisterMouseEventListener(IMouseListener* iml) = 0;

	virtual void UnRegisterMouseEventListener(IMouseListener* iml) = 0;

	virtual ~IMEH() {};
};



extern "C"
{
	void CreateMEH(IMEH ** meh);
	typedef void (*CREATEMEH)(IMEH ** meh);
   
	void ReleaseMEH(IMEH ** meh);
	typedef void (*RELEASEMEH)(IMEH ** meh);
}


#endif