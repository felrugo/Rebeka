#include "RebEnv.h"

RebEnv::RebEnv()
{
	Terrains.clear();
}

RebTerrain * RebEnv::CreateTerrain()
{
	RebTerrain * ret = new RebTerrain();
	Terrains.push_back(ret);
	return ret;
}


RebTerrain * RebEnv::CreateTerrain(std::string hmf)
{
	RebTerrain * ret = new RebTerrain();

	Terrains.push_back(ret);
	return ret;
}

std::vector<RebTerrain*> * RebEnv::GetTerrains()
{
	return &Terrains;
}

void RebEnv::DeleteTerrain(RebTerrain * del)
{
	for(unsigned int i = 0; i < Terrains.size(); i++)
	{
		if(Terrains[i] == del)
		{
			delete Terrains[i];
			Terrains.erase(Terrains.begin() + i);
		}
	}
}