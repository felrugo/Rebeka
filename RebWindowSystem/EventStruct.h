#ifndef EVENTSTRUCT_H
#define EVENTSTRUCT_H

#include "RebKeys.h"


enum EventType {WE_QUIT, WE_KEYDOWNEVENT, WE_KEYUPEVENT, WE_WINDOWEVENT, WE_MOUSEMOTIONEVENT, WE_MOUSEKEYDOWNEVENT, WE_MOUSEKEYUPEVENT, WE_MOUSEWHEELEVENT, WE_USEREVENT, WE_GAMEEVENT};



struct RebQuitEvent
{
	EventType Type;
	unsigned int compid;
	void* data;
};

struct RebUserEvent
{
	EventType Type;
	unsigned int compid;
	void* data;
};

struct RebKeyEvent
{
	EventType Type;
	RebKey keysym;
	unsigned __int8 state;
	unsigned int WindowID;
	unsigned int compid;
};

struct RebMouseKeyEvent
{
	EventType Type;
    unsigned long int windowID;    /**< The window with mouse focus, if any */
    unsigned long int which;       /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
   unsigned __int8 button;       /**< The mouse button index */
    unsigned __int8 state;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
    unsigned __int8 padding1;
    unsigned __int8 padding2;
    long int x;           /**< X coordinate, relative to window */
    long int y;           
};


struct RebMouseMotionEvent
{
	EventType Type;
    unsigned long int windowID;    /**< The window with mouse focus, if any */
    unsigned long int which;       /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
    unsigned long int state;       /**< The current button state */
    long int x;           /**< X coordinate, relative to window */
    long int y;           /**< Y coordinate, relative to window */
   long int xrel;        /**< The relative motion in the X direction */
    long int yrel;        /**< The relative motion in the Y direction */
};


typedef union RebEvent
{
	EventType Type;
	RebQuitEvent quit;
	RebMouseMotionEvent mousemot;
	RebMouseKeyEvent mousekey;
	RebUserEvent user;
	RebKeyEvent key;
	unsigned int compid;
}RebEvent;

#endif