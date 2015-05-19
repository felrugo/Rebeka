#include "RebGL_VCM.h"


RebGLVertexBuffer::RebGLVertexBuffer()
{
	vertices.clear();
	normals.clear();
	texturecoords.clear();
	Renderable = true;
	trans.Identity();
	materialid = 0;
	vbo[0] = vbo[1] = vbo[2] = 0;
	loaded = false;
}

std::vector<RebVector> * RebGLVertexBuffer::GetVertices()
{
	return &vertices;
}

std::vector<RebVector> * RebGLVertexBuffer::GetNormals()
{
	return &normals;
}

std::vector<RebVector> * RebGLVertexBuffer::GetTextureCoords()
{
	return &texturecoords;
}

void RebGLVertexBuffer::SetRenderable(bool s)
{
	Renderable = s;
}

bool RebGLVertexBuffer::isRenderable()
{
	return Renderable;
}

UINT RebGLVertexBuffer::GetMaterialID()
{
	return materialid;
}

RebMatrix * RebGLVertexBuffer::GetTrans()
{
	return &trans;
}

void RebGLVertexBuffer::SetName(std::string sname)
{
	name = sname;
}

void RebGLVertexBuffer::SetTrans(RebMatrix set)
{
	trans = set;
}

void RebGLVertexBuffer::SetMaterialID(UINT set)
{
	materialid = set;
}


void RebGLVertexBuffer::LoadIntoGL()
{
	if (loaded == false)
	{
		glGenBuffers(3, vbo);
		
		float * buffdata;
		unsigned long size = vertices.size() * 3;
		buffdata = new float[size];
		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			buffdata[(i * 3)] = vertices[i].x;
			buffdata[(i * 3)+1] = vertices[i].y;
			buffdata[(i * 3)+2] = vertices[i].z;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), buffdata, GL_STATIC_DRAW);

		delete[] buffdata;
		size = normals.size() * 3;
		buffdata = new float[size];
		for (unsigned int i = 0; i < normals.size(); i++)
		{
			buffdata[(i * 3)] = normals[i].x;
			buffdata[(i * 3) + 1] = normals[i].y;
			buffdata[(i * 3) + 2] = normals[i].z;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), buffdata, GL_STATIC_DRAW);

		delete[] buffdata;

		if (texturecoords.size() > 0)
		{

			size = texturecoords.size() * 2;
			buffdata = new float[size];
			for (unsigned int i = 0; i < texturecoords.size(); i++)
			{
				buffdata[(i * 2)] = texturecoords[i].x;
				buffdata[(i * 2) + 1] = texturecoords[i].y;
			}

			glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);

			glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), buffdata, GL_STATIC_DRAW);

			delete[] buffdata;
		}
		loaded = true;

	}



}

void RebGLVertexBuffer::Draw()
{
	if (!loaded)
		LoadIntoGL();


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);         // for vertex coordinates
	
	// do same as vertex array except pointer
	glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
	glVertexPointer(3, GL_FLOAT, 0, 0);               // last param is offset, not ptr

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);         // for vertex coordinates

	// do same as vertex array except pointer
	glEnableClientState(GL_NORMAL_ARRAY);             // activate vertex coords array
	glNormalPointer(GL_FLOAT, 0, 0);

	if (texturecoords.size() > 0)
	{

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);         // for vertex coordinates

		// do same as vertex array except pointer
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);             // activate vertex coords array
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
	}

	// draw 6 quads using offset of index array
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);            // deactivate vertex array
	glDisableClientState(GL_NORMAL_ARRAY);            // deactivate vertex array
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);            // deactivate vertex array

	// bind with 0, so, switch back to normal pointer operation
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}

void RebGLVertexBuffer::UnLoad()
{
	if (loaded)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(3, vbo);
		loaded = false;
	}
}

RebGLVertexBuffer::~RebGLVertexBuffer()
{
	UnLoad();
	vertices.clear();
	normals.clear();
	texturecoords.clear();
}




RebGLVertexCache::RebGLVertexCache()
{
	RVBs.clear();
	transf.Identity();
}

void RebGLVertexCache::AddBuffer(RebVertexBuffer * abuff)
{
	RVBs.push_back(abuff);
}

void RebGLVertexCache::SetName(std::string sname)
{
	name = sname;
}

std::string RebGLVertexCache::GetName()
{
	return name;
}

std::string RebGLVertexCache::GetFileName()
{
	return filename;
}

void RebGLVertexCache::SetTrans(RebMatrix set)
{
	transf = set;
}

void RebGLVertexCache::SetSkin(RebSkin sskin)
{
	skin = sskin;
}

RebMatrix * RebGLVertexCache::GetTrans()
{
	return &transf;
}

void RebGLVertexCache::SetFileName(std::string sfname)
{
	filename = sfname;
}

RebSkin RebGLVertexCache::GetSkin()
{
	return skin;
}

std::vector<RebVertexBuffer*> * RebGLVertexCache::GetRVBs()
{
	return &RVBs;
}

void RebGLVertexCache::DeleteBuffer(UINT VBID)
{

}









void RebVertexCacheManager::CreateCache(std::string name, std::vector<RebVertexBuffer> RVB)
{
	RebVertexCache * RVC = new RebGLVertexCache;
	RVC->SetName(name);
	//RVC->Get = RVB;
	RVCs.push_back(RVC);
}



void RebVertexCacheManager::CreateCacheFromFile(std::string cname, std::string filename)
{
	RebVertexCache * rvc = new RebGLVertexCache;
	RebVertexBuffer * rvb;
	

	const aiScene* scene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_Fast); // TRIANGLES!
  if (!scene) {
	  delete rvc;
    return;
  }
  for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {
    const aiMesh* mesh = scene->mMeshes[m_i];
	//rvb.Reset();
	rvb = new RebGLVertexBuffer();
	//rvb.ID = m_i;
	//rvb.met = R_TRIANGLES;
	rvb->SetName(mesh->mName.C_Str());
	//rvb.Renderable = true;
	rvb->SetMaterialID(mesh->mMaterialIndex);
	/*if(rvb.name.find("PS_Static_") != std::string::npos)
	{
		rvb.ps = PS_STATIC;
		rvb.Renderable = false;
	}
	if(rvb.name.find("PS_Moovable_") != std::string::npos)
	{
		rvb.ps = PS_MOOVABLE;
		rvb.Renderable = false;
	}*/

	for (unsigned int v_i = 0; v_i < mesh->mNumFaces; v_i++) {
		aiFace af = mesh->mFaces[v_i];
		for (int fi = 0; fi < 3; fi++)
		{
			if (mesh->HasPositions ()) {
			aiVector3D vp = mesh->mVertices[af.mIndices[fi]];
		RebVector rv(vp.x, vp.y, vp.z);
		rvb->GetVertices()->push_back(rv);
			}

			 if (mesh->HasNormals ()) {
				 aiVector3D vn = mesh->mNormals[af.mIndices[fi]];
		RebVector rv(vn.x, vn.y, vn.z);
		rvb->GetNormals()->push_back(rv);
      }

			if (mesh->HasTextureCoords(0)) {
				aiVector3D vt = mesh->mTextureCoords[0][af.mIndices[fi]];
		RebVector rv(vt.x, vt.y, 0.0f);
		rvb->GetTextureCoords()->push_back(rv);
      }

		}
     
    }
	//rvb.mm = MM_MODELVIEW;
	
	rvc->AddBuffer(rvb);
  }
  // LOAD MATERIAL
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
		  rm.amb.x = col.r;
		rm.amb.y = col.g;
		rm.amb.z = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_DIFFUSE, col)){
		  rm.dif.x = col.r;
		rm.dif.y = col.g;
		rm.dif.z = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_EMISSIVE, col)){
		  rm.emi.x = col.r;
		rm.emi.y = col.g;
		rm.emi.z = col.b;
	  }

	  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_SPECULAR, col)){
		  rm.spe.x = col.r;
		rm.spe.y = col.g;
		rm.spe.z = col.b;
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



  rvc->SetName(cname);
  rvc->SetFileName(filename);
  //rvc->transf.Identity();
  rvc->SetSkin(rs);
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
			if(RVCs[i]->GetName() == cname)
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
			if(RVCs[i]->GetFileName() == filename)
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


	//bool RebAssimpMH::LoadModel(std::string file)
	//{
	//	RebVertexCache * rvc = new RebVertexCache;
	//RebVertexBuffer rvb;
	//

	//const aiScene* scene = aiImportFile (file.c_str(), aiProcessPreset_TargetRealtime_Fast); // TRIANGLES!
 // if (!scene) {
	//  delete rvc;
 //   return false;
 // }
 // for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) {
 //   const aiMesh* mesh = scene->mMeshes[m_i];
	//rvb.Reset();
	//rvb.ID = m_i;
	//rvb.met = R_TRIANGLES;
	//rvb.name = mesh->mName.C_Str();
	//rvb.Renderable = true;
	//rvb.materialid = mesh->mMaterialIndex;
	//if(rvb.name.find("PS_Static_") != std::string::npos)
	//{
	//	rvb.ps = PS_STATIC;
	//	rvb.Renderable = false;
	//}
	//if(rvb.name.find("PS_Moovable_") != std::string::npos)
	//{
	//	rvb.ps = PS_MOOVABLE;
	//	rvb.Renderable = false;
	//}

	//for (unsigned int v_i = 0; v_i < mesh->mNumFaces; v_i++) {
	//	aiFace af = mesh->mFaces[v_i];
	//	for (int fi = 0; fi < 3; fi++)
	//	{
	//		if (mesh->HasPositions ()) {
	//		aiVector3D vp = mesh->mVertices[af.mIndices[fi]];
	//	RebVector rv(vp.x, vp.y, vp.z);
	//	rvb.vertices.push_back(rv);
	//		}

	//		 if (mesh->HasNormals ()) {
	//			 aiVector3D vn = mesh->mNormals[af.mIndices[fi]];
	//	RebVector rv(vn.x, vn.y, vn.z);
	//	rvb.normals.push_back(rv);
 //     }

	//		if (mesh->HasTextureCoords(0)) {
	//			aiVector3D vt = mesh->mTextureCoords[0][af.mIndices[fi]];
	//	RebVector rv(vt.x, vt.y, 0.0f);
	//	rvb.texturecoords.push_back(rv);
 //     }

	//	}
 //    
 //   }
	//rvb.mm = MM_MODELVIEW;
	//
	//rvc->AddBuffer(rvb);
 // }

 // RebSkin rs;

 // for(unsigned int mati = 0; mati < scene->mNumMaterials; mati++)
 // {
	//  RebMaterial rm;
	//  UINT tabid = 0;
	//  aiString path;
	//  aiColor3D col;
	//  if(scene->mMaterials[mati]->Get(AI_MATKEY_NAME, path) == AI_SUCCESS)
	//	  rm.name = path.data;
	//	
	//  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_AMBIENT, col)){
	//	  rm.amb.x = col.r;
	//	rm.amb.y = col.g;
	//	rm.amb.z = col.b;
	//  }

	//  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_DIFFUSE, col)){
	//	  rm.dif.x = col.r;
	//	rm.dif.y = col.g;
	//	rm.dif.z = col.b;
	//  }

	//  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_EMISSIVE, col)){
	//	  rm.emi.x = col.r;
	//	rm.emi.y = col.g;
	//	rm.emi.z = col.b;
	//  }

	//  if(AI_SUCCESS == scene->mMaterials[mati]->Get(AI_MATKEY_COLOR_SPECULAR, col)){
	//	  rm.spe.x = col.r;
	//	rm.spe.y = col.g;
	//	rm.spe.z = col.b;
	//  }




	//  while(scene->mMaterials[mati]->GetTexture(aiTextureType_AMBIENT, tabid, &path) == AI_SUCCESS)
	//  {
	//	  RebTexture rt;
	//	  rt.filename = path.data;
	//	  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
	//	  rm.ambtextures.push_back(rt);
	//	  tabid++;
	//  }
	//  tabid = 0;
	//  while(scene->mMaterials[mati]->GetTexture(aiTextureType_DIFFUSE, tabid, &path) == AI_SUCCESS)
	//  {
	//	  RebTexture rt;
	//	  rt.filename = path.data;
	//	  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
	//	  rm.diftextures.push_back(rt);
	//	  tabid++;
	//  }


	//  tabid = 0;
	//  while(scene->mMaterials[mati]->GetTexture(aiTextureType_SPECULAR, tabid, &path) == AI_SUCCESS)
	//  {
	//	  RebTexture rt;
	//	  rt.filename = path.data;
	//	  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
	//	  rm.spetextures.push_back(rt);
	//	  tabid++;
	//  }

	//  tabid = 0;
	//  while(scene->mMaterials[mati]->GetTexture(aiTextureType_EMISSIVE, tabid, &path) == AI_SUCCESS)
	//  {
	//	  RebTexture rt;
	//	  rt.filename = path.data;
	//	  prd->GetSkinManager()->AddTexture(path.data, &rt.id);
	//	  rm.emitextures.push_back(rt);
	//	  tabid++;
	//  }

	//  rm.id = mati;
	//  rs.materials.push_back(rm);
	//  return true;
 // }



 // rvc->name = file;
 // rvc->filename = file;
 // rvc->transf.Identity();
 // rvc->skin = rs;
 // /*obs.push_back(new RebVertexCache(*rvc));*/
 // RVC = *rvc;
 //   aiReleaseImport (scene);
	//}