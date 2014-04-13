
#ifndef COMPVISUAL_H
#define COMPVISUAL_H


#include "RebEntity.h"

class CompVisual : public Component
{
protected:
	IRenderDevice * IRD;
	RebVertexCache * rvc;
public:

	std::string GetType()
	{
		return "CompVisual";
	}
};


class CompVisModel : public CompVisual
{
	
public:
	CompVisModel(IRenderDevice * sird);

	void update();

	void LoadModel(std::string filename);

	std::string GetID()
	{
		return "CompVisModel";
	}
};


class TCompVisModel : public TComponent
{
	IRenderDevice * IRD;
public:
	TCompVisModel(IRenderDevice * sird);

	std::string GetID()
	{
	return "TCompVisModel";
	}

	std::string GetType()
	{
	return "CompVisual";
	}

	Component * MakeComponent()
	{
		CompVisModel * cvt = new CompVisModel(IRD);
		return cvt;
	}
};



class CompVisViewport : public CompVisual
{
public:
	CompVisViewport(IRenderDevice * SIRD);

	void update();

	std::string GetID()
	{
		return "CompVisViewport";
	}

	void SetActiveViewport();
};

class TCompVisViewport : public TComponent
{
IRenderDevice * IRD;
public:
	TCompVisViewport(IRenderDevice * sird);

	std::string GetID()
	{
	return "TCompVisViewport";
	}

	std::string GetType()
	{
	return "CompVisual";
	}

	Component * MakeComponent()
	{
		CompVisViewport * cvt = new CompVisViewport(IRD);
		return cvt;
	}


};


class CompVisTerrain : public CompVisual
{
	std::string curloaded;

	RebTerrain * ter;

public:
	CompVisTerrain(IRenderDevice * sird);

	~CompVisTerrain();

	void update();

	void CreateTerrain();

	std::string GetID()
	{
		return "CompVisTerrain";
	}
};

class TCompVisTerrain : public TComponent
{
	IRenderDevice * IRD;
public:
	TCompVisTerrain(IRenderDevice * sird)
	{
		IRD = sird;
	}

	std::string GetID()
	{
	return "TCompVisTerrain";
	}

	std::string GetType()
	{
	return "CompVisual";
	}

	Component * MakeComponent()
	{
		CompVisTerrain * cvt = new CompVisTerrain(IRD);
		cvt->AddParams(TParams);
		return cvt;
	}
};

#endif