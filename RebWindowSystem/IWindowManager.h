#ifndef IWINDOWMANAGER_H
#define IWINDOWMANAGER_H

#include <string>

class IWindowManager
{
public:
	virtual void InitManager() = 0;

	virtual void ReleaseManager() = 0;

	virtual void CreateWin(std::string name, int w, int h, int posx = 0, int posy = 0) = 0;

	virtual void DestroyWindow(std::string name) = 0;

	virtual void* GetWindow(std::string name) = 0;

	virtual void EnableRender(std::string name) = 0;

	virtual void SwapWindow(void * window) = 0;

	virtual void DisableRender(std::string name) = 0;

	virtual void TrapMouse(bool trap) = 0;

	virtual ~IWindowManager() {};
};

extern "C" {
	void CreateWindowManager(IWindowManager **interf);
	typedef void (*CREATEWINDOWMANAGER)(IWindowManager **interf);
   
	void ReleaseWindowManager(IWindowManager **interf);
	typedef void (*RELEASEWINDOWMANAGER)(IWindowManager **interf);
 }
#endif