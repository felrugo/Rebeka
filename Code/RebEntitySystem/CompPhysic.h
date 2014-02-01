#ifndef COMPPHYSIC_H
#define COMPPHYSIC_H

#include "RebEntity.h"
#include "..\bullet-2.82-r2704\src\btBulletDynamicsCommon.h"

class CompPhysic : public Component
{	
public:
	std::string GetType()
	{
		return "CompPhysic";
	}
};





class CompPhyModel : public CompPhysic
{
	btDynamicsWorld * DW;
	IRenderDevice * IRD;
	std::string mf;
public:

	CompPhyModel(btDynamicsWorld * SDW, IRenderDevice * SIRD, std::string smf);

	void LoadPhysic();

	void SetPhysicState(PhysicState sps);

	std::string GetID()
	{
		return "CompPhyModel";
	}

	PhysicState GetPhysicState();


};

class TCompPhyModel : public TComponent
{
	btDynamicsWorld * DW;
	IRenderDevice * IRD;
	std::string mf;
public:
	TCompPhyModel(btDynamicsWorld * SDW, IRenderDevice * SIRD)
	{
		DW = SDW;
		IRD = SIRD;
	}
	std::string GetID()
	{
		return "TCompPhyModel";
	}

	std::string GetType()
	{
		return "CompPhysic";
	}

	Component * MakeComponent()
	{
		Component * ret = new CompPhyModel(DW, IRD, mf);
		return ret;
	}
};

#endif