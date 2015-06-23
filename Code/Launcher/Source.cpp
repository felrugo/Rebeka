#include "..\RebEngine\RebEngineLoader.h"

bool game;

int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)             
{
	RebEL rel;
	rel.LoadEngine();
	rel.GetGEL()->Init();
	rel.GetGEL()->GameLoop();
	rel.GetGEL()->Release();
	rel.ReleaseEngine();
	return 0;
}