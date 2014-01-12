#ifndef REBGL_VCM_H
#define REBGL_VCM_H

#include "..\RebRenderer\IRenderDevice.h"
#include "assimp\Importer.hpp"
#include "assimp\cimport.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"

class RebVertexChacheManager : public IVertexChacheManager
{
	std::vector<RebVertexChache*> RVCs;

	IRenderDevice * prd;

public:

	RebVertexChacheManager(IRenderDevice * srd);

	void CreateChache(std::string name, std::vector<RebVertexBuffer> RVB);

	void DeleteChache(UINT CID);

	RebVertexChache * GetVertexChache(std::string cname);

	RebVertexChache * GetVCByFile(std::string filename); /* return 0 if VC doesn1t exists */

	void CreateChacheFromFile(std::string cname, std::string filename);

	void Render();

	void Release();

	~RebVertexChacheManager();
};

#endif