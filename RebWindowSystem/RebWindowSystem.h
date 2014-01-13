#ifndef REBWINDOWSYSTEM_H
#define REBWINDOWSYSTEM_H
#include "IWindowManager.h"
#include "IMEH.h"
#include <Windows.h>

class RebWindowSystem
{

	IWindowManager * wm;
	IMEH * me;
	bool runing;
	HINSTANCE mDLL;

public:

	RebWindowSystem();

	void CreateManager();

	void DeleteManager();

	IWindowManager * GetManager();

	IMEH * GetMEH();

	~RebWindowSystem();
};

#endif