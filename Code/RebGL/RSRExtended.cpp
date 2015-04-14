#include "RebGL_SS.h"



RSRExtended::RSRExtended(IRenderDevice * sird)
{
	ird = sird;
	RVCs = ird->GetVertexCacheManager()->GetRVCs();
	RebFileSystem rfs;
	rfs.GetAllFiles("..\\..");

	extended.AddShaderFile(rfs.Search("defff.rfs", ""));
	extended.AddShaderFile(rfs.Search("deffv.rvs", ""));
	extended.Link();
	programHandle = extended.GetHandle();

texCloc = glGetAttribLocationARB(programHandle, "texCoord");

lp = glGetUniformLocationARB(programHandle, "Light.Position");

Light.A = glGetUniformLocationARB(programHandle, "Light.La");
Light.D = glGetUniformLocationARB(programHandle, "Light.Ld");
Light.S = glGetUniformLocationARB(programHandle, "Light.Ls");

Material.A = glGetUniformLocationARB(programHandle, "Material.Ka");
Material.D = glGetUniformLocationARB(programHandle, "Material.Kd");
Material.S = glGetUniformLocationARB(programHandle, "Material.Ks");

shine = glGetUniformLocationARB(programHandle, "Material.Shininess");

texloc = glGetUniformLocationARB(programHandle, "Tex1");

glUniform1i(texloc, 0);

extended.Use();


}



void RSRExtended::TerrainRender()
{
	glUseProgramObjectARB(0);
	std::vector<RebTerrain*> * ters = ird->GetEnv()->GetTerrains();
	for(unsigned int i = 0; i < ters->size(); i++)
	{
		ird->TransformMatrix(ters->at(i)->trans * ird->GetViewportMat());

		glBegin(GL_TRIANGLE_STRIP);
		for(unsigned int i2 = 0; i2 < ters->at(i)->Hps.size(); i2++)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			//ird->Vertex3(ters->at(i)->Hps[i2]);
		}
		glEnd();
	}

}


	void RSRExtended::Render()
	{
		
			ird->Clear(1, 1);
		ird->ResetMatrix();

		TerrainRender();
		ird->ResetMatrix();

		extended.Use();

		glUniform3f(Light.A, 1.0, 1.0, 1.0);
		glUniform3f(Light.D, 1.0, 1.0, 1.0);
		glUniform3f(Light.S, 1.0, 1.0, 1.0);


		glUniform1f(shine, 1.0);

		glUniform3f(lp, 0.0, 0.0, 0.0);

		unsigned int i2;
		for (UINT i3 = 0; i3 < RVCs->size(); i3++)
		{
			RebSkin rs = RVCs->at(i3)->skin;
		for (UINT i = 0; i < RVCs->at(i3)->RVBs.size(); i++)
		{
			if(RVCs->at(i3)->RVBs[i].Renderable)
			{
				RebMaterial rm = rs.materials[RVCs->at(i3)->RVBs[i].materialid];
				ird->ChangeMatrixMode(MM_MODELVIEW);
				ird->ResetMatrix();
				
				ird->TransformMatrix(RVCs->at(i3)->RVBs[i].trans * RVCs->at(i3)->transf * ird->GetViewportMat());
				

				//glUniform3f(Material.A, rm.amb.fR, rm.amb.fG, rm.amb.fB);
				//glUniform3f(Material.D, rm.dif.fR, rm.dif.fG, rm.dif.fB);
				//glUniform3f(Material.S, rm.spe.fR, rm.spe.fG, rm.spe.fB);


				i2 = 0;
				while (i2 < RVCs->at(i3)->RVBs[i].vertices.size())
				{
					glActiveTexture(GL_TEXTURE0);
					if(rm.diftextures.size() > 0)
					ird->BindTexture(rm.diftextures[0].id);
					ird->StartDraw( RVCs->at(i3)->RVBs[i].met);
					for (short t = 0; t < 3; t++)
					{
					if(RVCs->at(i3)->RVBs[i].texturecoords.size() > i2+t)
					glTexCoord3fv(RVCs->at(i3)->RVBs[i].texturecoords[i2+t].glv());
					if(RVCs->at(i3)->RVBs[i].normals.size() > i2+t)
					glNormal3fv(RVCs->at(i3)->RVBs[i].normals[i2+t].glv());
					if(RVCs->at(i3)->RVBs[i].vertices.size() > i2+t)
					glVertex3fv(RVCs->at(i3)->RVBs[i].vertices[i2+t].glv());
					}
				ird->EndDraw();
				i2 += 3;
				}
			}
		}
		}
	}

	RSRExtended::~RSRExtended()
	{

	}