#ifndef REB_H
#define REB_H

#include <string>
#include <vector>
#include "..\Reb3D\Reb3d.h"
#include "..\RebSupport\RebVL.h"


enum Methold {R_TRIANGLES, R_QUADS};

enum MatrixMode
{
	MM_MODELVIEW,
	MM_PROJECTIONVIEW
};


enum PhysicState { PS_NOPS, PS_STATIC, PS_MOOVABLE, PS_SOFTBODY};

enum LightType {LT_SPOT, LT_POINT};


typedef RebVector RebColor;

struct RebTexture;

struct RebMaterial
{
	UINT id;
	std::string name;
	RebColor amb;
	RebColor dif;
	RebColor spe;
	RebColor emi;
	std::vector<RebTexture> ambtextures;
	std::vector<RebTexture> diftextures;
	std::vector<RebTexture> spetextures;
	std::vector<RebTexture> emitextures;
};

struct RebTexture
{
	UINT id;
	std::string filename;
};

struct RebSkin
{
	std::vector<RebMaterial> materials;
};


class RebLight
{
protected:
	RebVector pos;
	RebColor color;
	LightType lt;
	RebMatrix view;
public:

};

class RebTerrain
{
public:

	std::vector<float> Hps;
	unsigned int stepx;
	unsigned int stepy;
	unsigned int textureid;
	unsigned int stepsize;
	RebMatrix trans;

	RebTerrain()
	{
		Hps.clear();
		stepx = stepy = textureid = 0;
		stepsize = 1;
		trans.Identity();
	}

};

struct RebVertexBuffer
{

	std::vector<RebVector> vertices;
	std::vector<RebVector> normals;
	std::vector<RebVector> texturecoords;
	MatrixMode mm;
	bool Renderable;
	PhysicState ps;
	RebMatrix trans;
	std::string name;
	Methold met;
	UINT ID;
	UINT materialid;
	
	UINT readpoint;

	RebVertexBuffer()
	{
		vertices.clear();
		normals.clear();
		texturecoords.clear();
		mm = MM_MODELVIEW;
		met = R_TRIANGLES;
		ps = PS_NOPS;
		readpoint = 0;
		trans.Identity();
		Renderable = true;
	}

	void Reset()
	{
		vertices.clear();
		normals.clear();
		texturecoords.clear();
		mm = MM_MODELVIEW;
		met = R_TRIANGLES;
		readpoint = 0;
		Renderable = true;
	}

	~RebVertexBuffer()
	{
		vertices.clear();
	}
};


struct RebVertexCache
{

	std::vector<RebVertexBuffer> RVBs;
	RebMatrix transf;
	std::string name;
	RebSkin skin;
	std::string filename;

	RebVertexCache()
	{
		RVBs.clear();
		transf.Identity();
	}

	void AddBuffer(RebVertexBuffer abuff)
	{
		RVBs.push_back(abuff);
	}

	void DeleteBuffer(UINT VBID)
	{
		if (VBID < RVBs.size())
		{
		RVBs.erase(RVBs.begin() + VBID);
		}
	}

	void SetRenderable(UINT VBID)
	{
		if (VBID < RVBs.size())
			RVBs[VBID].Renderable = true;
	}

	void SetUnRenderable(UINT VBID)
	{
		if (VBID < RVBs.size())
			RVBs[VBID].Renderable = false;
	}

	~RebVertexCache()
	{
		RVBs.clear();
	}

};





#endif