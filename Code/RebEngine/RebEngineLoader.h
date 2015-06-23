#ifndef REBENGINELOADER_H
#define REBENGINELOADER_H

#include <Windows.h>


class IEngineLib
{
public:
	virtual void Init() = 0;

	virtual void GameLoop() = 0;

	virtual void Release() = 0;
};


extern "C" {
	void LoadEngineLib(IEngineLib **GEL);
	typedef void(*LOADEL)(IEngineLib **GEL);
   
   void ReleaseEngineLib(IEngineLib **GDLL);
   typedef void(*RELEASEEL)(IEngineLib **GDLL);
 }

class RebEL
{
	HMODULE mDll;
	IEngineLib * GEL;
public:
	void LoadEngine();

	IEngineLib * GetGEL();

	void ReleaseEngine();

};



#endif