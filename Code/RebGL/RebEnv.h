#ifndef REBENV
#define REBENV

#include "..\RebRenderer\IRenderDevice.h"



class RebEnv : public IGameEnv
{
	std::vector<RebTerrain*> Terrains;
public:
	RebEnv();
	RebTerrain * CreateTerrain();
	std::vector<RebTerrain*> * GetTerrains();
	void DeleteTerrain(RebTerrain * del);
};



#endif