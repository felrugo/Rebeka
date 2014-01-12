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
	
	const aiScene* scene = aiImportFile (filename.c_str(), aiProcess_Triangulate); // TRIANGLES!
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
	if(rvb.name.find("PS_Static_"))
	{
		rvb.ps = PS_STATIC;
		rvb.Renderable = false;
	}
	if(rvb.name.find("PS_Moovable_"))
	{
		rvb.ps = PS_MOOVABLE;
		rvb.Renderable = false;
	}

    for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++) {
      if (mesh->HasPositions ()) {
        const aiVector3D* vp = &(mesh->mVertices[v_i]);
		RebVector rv(vp->x, vp->y, vp->z);
		rvb.vertices.push_back(rv);
      }
      if (mesh->HasNormals ()) {
        const aiVector3D* vn = &(mesh->mNormals[v_i]);

		RebVector rv(vn->x, vn->y, vn->z);
		rvb.normals.push_back(rv);
      }
      if (mesh->HasTextureCoords (0)) {
        const aiVector3D* vt = &(mesh->mTextureCoords[0][v_i]);
       
		RebVector rv(vt->x, vt->y, 0.0f);
		rvb.texturecoords.push_back(rv);
      }
      if (mesh->HasTangentsAndBitangents ()) {
        // NB: could store/print tangents here
      }
    }
	rvb.mm = MM_MODELVIEW;
	
	rvc->AddBuffer(rvb);
  }
  rvc->name = cname;
  rvc->filename = filename;
  rvc->transf.Identity();
  RVCs.push_back(rvc);
    aiReleaseImport (scene);
}

	void RebVertexCacheManager::DeleteCache(UINT CID)
	{
		if (CID < RVCs.size())
		{
		RVCs.erase(RVCs.begin() + CID);
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

	void RebVertexCacheManager::Render()
	{
		unsigned int i2;
		for (UINT i3 = 0; i3 < RVCs.size(); i3++)
		{
		for (UINT i = 0; i < RVCs[i3]->RVBs.size(); i++)
		{
			if(RVCs[i3]->RVBs[i].Renderable)
			{
				prd->ChangeMatrixMode(MM_MODELVIEW);
				prd->ResetMatrix();
				
				prd->TransformMatrix(RVCs[i3]->RVBs[i].trans * RVCs[i3]->transf * prd->GetViewportMat());
				i2 = 0;
				while (i2 < RVCs[i3]->RVBs[i].vertices.size())
				{
					prd->StartDraw( RVCs[i3]->RVBs[i].met);
					prd->Vertex3( RVCs[i3]->RVBs[i].vertices[i2]);
					i2++;
					prd->Vertex3( RVCs[i3]->RVBs[i].vertices[i2]);
					i2++;
					prd->Vertex3( RVCs[i3]->RVBs[i].vertices[i2]);
				prd->EndDraw();
				i2++;
				}
			}
		}
		}
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
			delete RVCs[i];
		}
	RVCs.clear();
	}

	RebVertexCacheManager::~RebVertexCacheManager()
	{
		Release();
	}