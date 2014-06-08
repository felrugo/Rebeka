#include "RebGL_VCM.h"


void RebVertexCacheManager::CreateCache(std::string name, std::vector<RebVertexBuffer> RVB)
{
	RebVertexCache * RVC = new RebVertexCache;
	RVC->name = name;
	RVC->RVBs = RVB;
	RVCs.push_back(RVC);
}



void RebVertexCacheManager::CreateCacheFromFile(std::string cname, std::string filename)
{
	RebVertexCache * rvc = new RebVertexCache;
	RebVertexBuffer rvb;
	

	const aiScene* scene = aiImportFile (filename.c_str(), aiProcessPreset_TargetRealtime_Fast); // TRIANGLES!
  if (!scene) {
	  delete rvc;
    return;
  }
  for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {
    const aiMesh* mesh = scene->mMeshes[m_i];
	rvb.Reset();
	rvb.ID = m_i;
	rvb.met = R_TRIANGLES;
	rvb.name = mesh->mName.C_Str();
	rvb.Renderable = true;
	rvb.materialid = mesh->mMaterialIndex;
	if(rvb.name.find("PS_Static_") != std::string::npos)
	{
		rvb.ps = PS_STATIC;
		rvb.Renderable = false;
	}
	if(rvb.name.find("PS_Moovable_") != std::string::npos)
	{
		rvb.ps = PS_MOOVABLE;
		rvb.Renderable = false;
	}

	for (unsigned int v_i = 0; v_i < mesh->mNumFaces; v_i++) {
		aiFace af = mesh->mFaces[v_i];
		for (int fi = 0; fi < 3; fi++)
		{
			if (mesh->HasPositions ()) {
			aiVector3D vp = mesh->mVertices[af.mIndices[fi]];
		RebVector rv(vp.x, vp.y, vp.z);
		rvb.vertices.push_back(rv);
			}

			 if (mesh->HasNormals ()) {
				 aiVector3D vn = mesh->mNormals[af.mIndices[fi]];
		RebVector rv(vn.x, vn.y, vn.z);
		rvb.normals.push_back(rv);
      }

			if (mesh->HasTextureCoords(0)) {
				aiVector3D vt = mesh->mTextureCoords[0][af.mIndices[fi]];
		RebVector rv(vt.x, vt.y, 0.0f);
		rvb.texturecoords.push_back(rv);
      }

		}
     
    }
	rvb.mm = MM_MODELVIEW;
	
	rvc->AddBuffer(rvb);
  }

  RebSkin rs;

  for(unsigned int mati = 0; mati < scene->mNumMaterials; mati++)
  {
	  RebMaterial rm;
	  UINT tabid = 0;
	  aiString path;
	  aiColor3D col;
	  if(scene->mMaterials[mati]->Get(AI_MATKEY_NAME, path) == AI_SUCCESS)
		  rm.name = path.data;
		
	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_AMBIENT, col)){
		  rm.amb.fR = col.r;
		rm.amb.fG = col.g;
		rm.amb.fB = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_DIFFUSE, col)){
		  rm.dif.fR = col.r;
		rm.dif.fG = col.g;
		rm.dif.fB = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_EMISSIVE, col)){
		  rm.emi.fR = col.r;
		rm.emi.fG = col.g;
		rm.emi.fB = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_SPECULAR, col)){
		  rm.spe.fR = col.r;
		rm.spe.fG = col.g;
		rm.spe.fB = col.b;
	  }




	  while(scene->mMaterials[mati]->GetTexture(aiTextureType_AMBIENT, tabid, &path) == AI_SUCCESS)
	  {
		  RebTexture rt;
		  rt.filename = path.data;
		  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
		  rm.ambtextures.push_back(rt);
		  tabid++;
	  }
	  tabid = 0;
	  while(scene->mMaterials[mati]->GetTexture(aiTextureType_DIFFUSE, tabid, &path) == AI_SUCCESS)
	  {
		  RebTexture rt;
		  rt.filename = path.data;
		  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
		  rm.diftextures.push_back(rt);
		  tabid++;
	  }


	  tabid = 0;
	  while(scene->mMaterials[mati]->GetTexture(aiTextureType_SPECULAR, tabid, &path) == AI_SUCCESS)
	  {
		  RebTexture rt;
		  rt.filename = path.data;
		  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
		  rm.spetextures.push_back(rt);
		  tabid++;
	  }

	  tabid = 0;
	  while(scene->mMaterials[mati]->GetTexture(aiTextureType_EMISSIVE, tabid, &path) == AI_SUCCESS)
	  {
		  RebTexture rt;
		  rt.filename = path.data;
		  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
		  rm.emitextures.push_back(rt);
		  tabid++;
	  }

	  rm.id = mati;
	  rs.materials.push_back(rm);
  }



  rvc->name = cname;
  rvc->filename = filename;
  rvc->transf.Identity();
  rvc->skin = rs;
  /*obs.push_back(new RebVertexCache(*rvc));*/
  RVCs.push_back(rvc);
    aiReleaseImport (scene);
}

void RebVertexCacheManager::DeleteCache(RebVertexCache * rvc)
	{
		if(rvc = 0)
			return;
		UINT CID;
		for(CID = 0; CID < RVCs.size(); CID++)
		{
			if(RVCs[CID] == rvc)
			{
				delete RVCs[CID];
			RVCs[CID] = 0;
			RVCs.erase(RVCs.begin() + CID);
			}
		}
		}
	

	RebVertexCache * RebVertexCacheManager::GetVertexCache(std::string cname)
	{
		for (unsigned int i = 0; i < RVCs.size(); i++)
		{
			if(RVCs[i]->name == cname)
			{
				return RVCs[i];
			}
		}
		return 0;
	}

	RebVertexCache * RebVertexCacheManager::GetVCByFile(std::string filename) /* if VC doesn't exists return 0 */
	{
		for (unsigned int i = 0; i < RVCs.size(); i++)
		{
			if(RVCs[i]->filename == filename)
			{
				return RVCs[i];
			}
		}
		return 0;
	}

	

	
	RebVertexCacheManager::RebVertexCacheManager(IRenderDevice * srd)
	{
		prd = srd;
		RVCs.clear();
	}
	

	void RebVertexCacheManager::Release()
	{
		for (unsigned int i = 0; i < RVCs.size(); i++)
		{
			if(RVCs[i] != 0)
			{
			delete RVCs[i];
			RVCs[i] = 0;
			}
		}
	RVCs.clear();
	}



	std::vector<RebVertexCache*> * RebVertexCacheManager::GetRVCs()
	{
		return &RVCs;
	}


	

	RebVertexCacheManager::~RebVertexCacheManager()
	{
		Release();
	}


	bool RebAssimpMH::LoadModel(std::string file)
	{
		RebVertexCache * rvc = new RebVertexCache;
	RebVertexBuffer rvb;
	

	const aiScene* scene = aiImportFile (file.c_str(), aiProcessPreset_TargetRealtime_Fast); // TRIANGLES!
  if (!scene) {
	  delete rvc;
    return false;
  }
  for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {
    const aiMesh* mesh = scene->mMeshes[m_i];
	rvb.Reset();
	rvb.ID = m_i;
	rvb.met = R_TRIANGLES;
	rvb.name = mesh->mName.C_Str();
	rvb.Renderable = true;
	rvb.materialid = mesh->mMaterialIndex;
	if(rvb.name.find("PS_Static_") != std::string::npos)
	{
		rvb.ps = PS_STATIC;
		rvb.Renderable = false;
	}
	if(rvb.name.find("PS_Moovable_") != std::string::npos)
	{
		rvb.ps = PS_MOOVABLE;
		rvb.Renderable = false;
	}

	for (unsigned int v_i = 0; v_i < mesh->mNumFaces; v_i++) {
		aiFace af = mesh->mFaces[v_i];
		for (int fi = 0; fi < 3; fi++)
		{
			if (mesh->HasPositions ()) {
			aiVector3D vp = mesh->mVertices[af.mIndices[fi]];
		RebVector rv(vp.x, vp.y, vp.z);
		rvb.vertices.push_back(rv);
			}

			 if (mesh->HasNormals ()) {
				 aiVector3D vn = mesh->mNormals[af.mIndices[fi]];
		RebVector rv(vn.x, vn.y, vn.z);
		rvb.normals.push_back(rv);
      }

			if (mesh->HasTextureCoords(0)) {
				aiVector3D vt = mesh->mTextureCoords[0][af.mIndices[fi]];
		RebVector rv(vt.x, vt.y, 0.0f);
		rvb.texturecoords.push_back(rv);
      }

		}
     
    }
	rvb.mm = MM_MODELVIEW;
	
	rvc->AddBuffer(rvb);
  }

  RebSkin rs;

  for(unsigned int mati = 0; mati < scene->mNumMaterials; mati++)
  {
	  RebMaterial rm;
	  UINT tabid = 0;
	  aiString path;
	  aiColor3D col;
	  if(scene->mMaterials[mati]->Get(AI_MATKEY_NAME, path) == AI_SUCCESS)
		  rm.name = path.data;
		
	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_AMBIENT, col)){
		  rm.amb.fR = col.r;
		rm.amb.fG = col.g;
		rm.amb.fB = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_DIFFUSE, col)){
		  rm.dif.fR = col.r;
		rm.dif.fG = col.g;
		rm.dif.fB = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_EMISSIVE, col)){
		  rm.emi.fR = col.r;
		rm.emi.fG = col.g;
		rm.emi.fB = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_SPECULAR, col)){
		  rm.spe.fR = col.r;
		rm.spe.fG = col.g;
		rm.spe.fB = col.b;
	  }




	  while(scene->mMaterials[mati]->GetTexture(aiTextureType_AMBIENT, tabid, &path) == AI_SUCCESS)
	  {
		  RebTexture rt;
		  rt.filename = path.data;
		  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
		  rm.ambtextures.push_back(rt);
		  tabid++;
	  }
	  tabid = 0;
	  while(scene->mMaterials[mati]->GetTexture(aiTextureType_DIFFUSE, tabid, &path) == AI_SUCCESS)
	  {
		  RebTexture rt;
		  rt.filename = path.data;
		  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
		  rm.diftextures.push_back(rt);
		  tabid++;
	  }


	  tabid = 0;
	  while(scene->mMaterials[mati]->GetTexture(aiTextureType_SPECULAR, tabid, &path) == AI_SUCCESS)
	  {
		  RebTexture rt;
		  rt.filename = path.data;
		  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
		  rm.spetextures.push_back(rt);
		  tabid++;
	  }

	  tabid = 0;
	  while(scene->mMaterials[mati]->GetTexture(aiTextureType_EMISSIVE, tabid, &path) == AI_SUCCESS)
	  {
		  RebTexture rt;
		  rt.filename = path.data;
		  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
		  rm.emitextures.push_back(rt);
		  tabid++;
	  }

	  rm.id = mati;
	  rs.materials.push_back(rm);
	  return true;
  }



  rvc->name = file;
  rvc->filename = file;
  rvc->transf.Identity();
  rvc->skin = rs;
  /*obs.push_back(new RebVertexCache(*rvc));*/
  RVC = *rvc;
    aiReleaseImport (scene);
	}