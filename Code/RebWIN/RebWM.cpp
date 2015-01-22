#include "RebWM.h"

void CreateWindowManager(IWindowManager **interf)
{
	*interf = new RebWM();
}

void ReleaseWindowManager(IWindowManager **interf)
{
	delete *interf;
}

RebWM::RebWM()
{
	wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = GetModuleHandle(0);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = L"OpenGL";
    RegisterClass(&wndClass);
}

	void ReleaseManager();
		
	 void RebWM::CreateWin(std::string name, int w, int h, int posx = 0, int posy = 0)
	 {
		  hWnd = CreateWindow(
			  L"OpenGL", (LPCWSTR) name.c_str(),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        posx, posy, w, h,
        NULL, NULL, GetModuleHandle(0), (void*)this);

    /* display window */
    ShowWindow(hWnd, 0);
    UpdateWindow(hWnd);


	 }

	 void DestroyWindow(std::string name);

	 void* GetWindow(std::string name);

	 void EnableRender(std::string name);

	 void DisableRender(std::string name);

	 void SwapWindow(void * window);

	 void TrapMouse(bool trap);