#ifndef REBGRAPHICELEMENTS_H
#define REBGRAPHICELEMENTS_H

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
	virtual RebVector GetPos() = 0;

	virtual RebVector GetColor() = 0;

	virtual RebMatrix * GetViewm() = 0;
};

class RebTerrain
{
protected:
	std::vector<float> Hps;
	unsigned int stepx;
	unsigned int stepy;
	unsigned int textureid;
	float stepsize;
	RebMatrix trans;
public:
	virtual void Draw() = 0;
	virtual RebMatrix GetTrans() { return trans; }

};

class RebVertexBuffer
{
public:
	
	virtual std::vector<RebVector> * GetVertices() = 0;

	virtual std::vector<RebVector> * GetNormals() = 0;

	virtual std::vector<RebVector> * GetTextureCoords() = 0;

	virtual void SetRenderable(bool s) = 0;

	virtual bool isRenderable() = 0;

	virtual UINT GetMaterialID() = 0;

	virtual void Draw() = 0;

	virtual void SetName(std::string sname) = 0;

	virtual void SetTrans(RebMatrix set) = 0;

	virtual RebMatrix * GetTrans() = 0;

	virtual void SetMaterialID(UINT set) = 0;


	
};


class RebVertexCache
{
protected:
	std::vector<RebVertexBuffer*> RVBs;
	RebMatrix transf;
	std::string name;
	RebSkin skin;
	std::string filename;

public:

	virtual void AddBuffer(RebVertexBuffer * abuff) = 0;
	
	virtual void SetName(std::string sname) = 0;

	virtual std::string GetName() = 0;

	virtual std::string GetFileName() = 0;

	virtual RebSkin GetSkin() = 0;

	virtual std::vector<RebVertexBuffer*> * GetRVBs() = 0;

	virtual void SetTrans(RebMatrix set) = 0;

	virtual RebMatrix * GetTrans() = 0;

	virtual void SetSkin(RebSkin sskin) = 0;

	virtual void SetFileName(std::string sfname) = 0;

	virtual void DeleteBuffer(UINT VBID) = 0;


	

};





#endif