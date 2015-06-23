
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
	
public:
	TCompVisModel();

	std::string GetID()
	{
	return "TCompVisModel";
	}

	std::string GetType()
	{
	return "CompVisual";
	}

	Component * MakeComponent(RebGDC * data)
	{
		CompVisModel * cvt = new CompVisModel(data->rd);
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
public:
	TCompVisViewport();

	std::string GetID()
	{
	return "TCompVisViewport";
	}

	std::string GetType()
	{
	return "CompVisual";
	}

	Component * MakeComponent(RebGDC * data)
	{
		CompVisViewport * cvt = new CompVisViewport(data->rd);
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
	TCompVisTerrain()
	{
		
	}

	std::string GetID()
	{
	return "TCompVisTerrain";
	}

	std::string GetType()
	{
	return "CompVisual";
	}

	Component * MakeComponent(RebGDC * data)
	{
		CompVisTerrain * cvt = new CompVisTerrain(data->rd);
		cvt->AddParams(TParams);
		return cvt;
	}
};

#endif