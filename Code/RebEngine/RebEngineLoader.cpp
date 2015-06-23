#include "RebEngineLoader.h"

void RebEL::LoadEngine()
{
	mDll = LoadLibrary("Rebeka.dll");
	LOADEL _LoadEL = 0;
	_LoadEL = (LOADEL)GetProcAddress(mDll, "LoadEL");
	_LoadEL(&GEL);
}


void RebEL::ReleaseEngine()
{
	RELEASEEL _ReleaseEL = 0;
	_ReleaseEL = (RELEASEEL)GetProcAddress(mDll, "ReleaseEL");
	_ReleaseEL(&GEL);
}

IEngineLib * RebEL::GetGEL()
{
	return GEL;
}