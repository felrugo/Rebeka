#include "..\IGameDLL\IGameDLL.h"

bool game;

int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)             
{
	RebGDL rgdl;
	rgdl.LoadGameDLL();
	rgdl.GetGDLL()->Init();
	rgdl.GetGDLL()->GameLoop();
	rgdl.GetGDLL()->Release();
	rgdl.ReleaseGameDLL();
	return 0;
}