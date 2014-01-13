#ifndef REBSDL_H
#define REBSDL_H
#include "SDL.h"
#include "..\RebWindowSystem\IWindowManager.h"
#include <string>
#include <map>
#include <vector>

class SDLWinManager : public IWindowManager
{
	std::map<std::string, SDL_Window*> windows;

	std::map<std::string, SDL_GLContext> glcontexts;

	std::vector<std::string> keys;

	int finv(std::string name);
public:
	void InitManager();

	void ReleaseManager();
		
	 void CreateWin(std::string name, int w, int h, int posx = 0, int posy = 0);

	 void DestroyWindow(std::string name);

	 void* GetWindow(std::string name);

	 void EnableRender(std::string name);

	 void DisableRender(std::string name);

	 void SwapWindow(void * window);

	 void TrapMouse(bool trap);

	 ~SDLWinManager();
};





#endif