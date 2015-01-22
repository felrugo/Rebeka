#ifndef REBENV
#define REBENV

#include "RebGL.h"



class RebEnv : public IGameEnv
{
	std::vector<RebTerrain*> Terrains;
public:
	RebEnv();
	RebTerrain * CreateTerrain();
	RebTerrain * CreateTerrain(std::string hmf);
	std::vector<RebTerrain*> * GetTerrains();
	void DeleteTerrain(RebTerrain * del);
};



#endif