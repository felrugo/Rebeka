
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
	std::string mf;
public:
	CompVisModel(IRenderDevice * sird, std::string smf);

	void LoadModel(std::string filename);

	std::string GetID()
	{
		return "CompVisModel";
	}
};


class TCompVisModel : public TComponent
{
	IRenderDevice * IRD;
	std::string ModelFile;
public:
	TCompVisModel(IRenderDevice * sird, std::string mf);

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
		CompVisModel * cvt = new CompVisModel(IRD, ModelFile);
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

#endif