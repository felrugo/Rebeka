#include "DefEnts.h"



TEntTerrain::TEntTerrain()
{
	name = "Terrain";
	TComponent * tc = new TCompVisTerrain();
	temps.push_back(tc);
}


