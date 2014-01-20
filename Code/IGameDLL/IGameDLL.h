#ifndef IGAMEDLL_H
#define IGAMEDLL_H

#include <Windows.h>


class IGameDLL
{
public:
	virtual void Init() = 0;

	virtual void GameLoop() = 0;

	virtual void Release() = 0;
};


extern "C" {
   void CreateGameDLL(IGameDLL **GDLL);
   typedef void (*CREATEGDLL)(IGameDLL **GDLL);
   
   void ReleaseGameDLL(IGameDLL **GDLL);
   typedef void (*RELEASEGDLL)(IGameDLL **GDLL);
 }

class RebGDL
{
	HMODULE mDll;
	IGameDLL * GDLL;
public:
	void LoadGameDLL();

	IGameDLL * GetGDLL();

	void ReleaseGameDLL();

};



#endif