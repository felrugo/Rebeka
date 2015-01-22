#ifndef REBWM_H
#define REBWM_H

#include "..\RebWindowSystem\IWindowManager.h"
#include "..\RebWindowSystem\IMEH.h"
#include <Windows.h>
#include <string>
#include <map>
#include <vector>

class RebWM : public IWindowManager
{

WNDCLASS wndClass;
HWND hWnd;
MSG msg;

HDC hDC;
HGLRC hGLRC;
HPALETTE hPalette;



public:

static LRESULT APIENTRY
WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam);

	RebWM();

	~RebWM();
		
	 void CreateWin(std::string name, int w, int h, int posx = 0, int posy = 0);

	 void DestroyWindow(std::string name);

	 void* GetWindow(std::string name);

	 void EnableRender(std::string name);

	 void DisableRender(std::string name);

	 void SwapWindow(void * window);

	 void TrapMouse(bool trap);
};


#endif