#include "IGameDLL.h"

void RebGDL::LoadGameDLL()
{
	mDll = LoadLibrary("Rebeka.dll");
	CREATEGDLL _CreateGameDLL = 0;
	_CreateGameDLL = (CREATEGDLL)GetProcAddress(mDll, "CreateGameDLL");
	_CreateGameDLL(&GDLL);
}


void RebGDL::ReleaseGameDLL()
{
	RELEASEGDLL _ReleaseGameDLL = 0;
	_ReleaseGameDLL = (RELEASEGDLL)GetProcAddress(mDll, "ReleaseGameDLL");
	_ReleaseGameDLL(&GDLL);
}

IGameDLL * RebGDL::GetGDLL()
{
	return GDLL;
}