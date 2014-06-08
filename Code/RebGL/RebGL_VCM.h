#ifndef REBGL_VCM_H
#define REBGL_VCM_H


#include <gl\glew.h>
#include "..\RebRenderer\IRenderDevice.h"
#include "assimp\Importer.hpp"
#include "assimp\cimport.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"



class RebAssimpMH : public IModelHandler
{
RebVertexCache RVC;
IRenderDevice * prd;
public:
RebAssimpMH(IRenderDevice * srd);
bool LoadModel(std::string file);
RebVertexCache GetRVC();
};


class RebVertexCacheManager : public IVertexCacheManager
{
	std::vector<RebVertexCache*> RVCs;

	IRenderDevice * prd;

public:

	RebVertexCacheManager(IRenderDevice * srd);

	void CreateCache(std::string name, std::vector<RebVertexBuffer> RVB);

	void DeleteCache(RebVertexCache* rvc);

	RebVertexCache * GetVertexCache(std::string cname);

	RebVertexCache * GetVCByFile(std::string filename); /* return 0 if VC doesn1t exists */

	void CreateCacheFromFile(std::string cname, std::string filename);

	std::vector<RebVertexCache*> * GetRVCs();

	void Release();

	~RebVertexCacheManager();
};

#endif