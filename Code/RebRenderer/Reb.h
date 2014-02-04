#ifndef REB_H
#define REB_H

#include <string>
#include <vector>
#include "..\Reb3D\Reb3d.h"


enum Methold {R_TRIANGLES, R_QUADS};

enum MatrixMode
{
	MM_MODELVIEW,
	MM_PROJECTIONVIEW
};


enum PhysicState { PS_NOPS, PS_STATIC, PS_MOOVABLE, PS_SOFTBODY};


typedef struct RebColor
{
	union 
	{
		struct
		{
	float fR;
	float fG;
	float fB;
	float fA;
		};
		float c[4];
	};
} REBCOLOR;

struct RebMaterial
{
	UINT id;
	RebColor cDiffuse;
	RebColor cAmbient;
	RebColor cSpecular;
	RebColor cEmissive;
	float fPower;
};

struct RebTexture
{
	UINT id;
	float fAlpha;
	std::string chName;
	void * pData;
	RebColor * ColKeys;
	DWORD nColors;

};

struct RebSkin
{
	UINT id;
	bool bAlpha;
	UINT nMaterial;
	UINT nTexture[8];
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
	RebSkin skin;
	
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