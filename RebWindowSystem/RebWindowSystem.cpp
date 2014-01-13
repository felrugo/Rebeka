#include "RebWindowSystem.h"

RebWindowSystem::RebWindowSystem()
{
	wm = 0;
	mDLL = LoadLibrary("RebSDL.dll");
	runing = false;
}

void RebWindowSystem::CreateManager()
{
	if (runing == false)
	{
		CREATEWINDOWMANAGER _CreateWindowManager = 0;
		_CreateWindowManager = (CREATEWINDOWMANAGER)GetProcAddress(mDLL, "CreateWindowManager");
		_CreateWindowManager(&wm);
		CREATEMEH _CreateMEH = 0;
		_CreateMEH = (CREATEMEH)GetProcAddress(mDLL, "CreateMEH");
		_CreateMEH(&me);
		runing = true;
	}
}

void RebWindowSystem::DeleteManager()
{
	if(runing == true)
	{
		RELEASEWINDOWMANAGER _ReleaseWindowManager = 0;
		_ReleaseWindowManager = (RELEASEWINDOWMANAGER)GetProcAddress(mDLL, "ReleaseWindowManager");
		_ReleaseWindowManager(&wm);
		RELEASEMEH _ReleaseMEH = 0;
		_ReleaseMEH = (RELEASEMEH)GetProcAddress(mDLL, "ReleaseMEH");
		_ReleaseMEH(&me);
		runing = false;
	}
}


IWindowManager * RebWindowSystem::GetManager()
{
	return wm;
}

IMEH * RebWindowSystem::GetMEH()
{
	return me;
}


RebWindowSystem::~RebWindowSystem()
{
	DeleteManager();
}