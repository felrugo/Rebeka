#include "RebGL_SS.h"



RSRExtended::RSRExtended(IRenderDevice * sird)
{
	ird = sird;
	RVCs = ird->GetVertexCacheManager()->GetRVCs();

	programHandle = ird->GetShaderSystem()->GetProgramid("Extended");

ird->GetShaderSystem()->Link(programHandle);

texCloc = glGetAttribLocationARB(programHandle, "texCoord");

texloc = glGetUniformLocationARB(programHandle, "Tex1");

glUniform1i(texloc, 0);

ird->GetShaderSystem()->ActivateProgram(programHandle);


}



	void RSRExtended::Render()
	{
			ird->Clear(1, 1);
		ird->ResetMatrix();

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

				ird->MaterialSetup(rm);
				i2 = 0;
				while (i2 < RVCs->at(i3)->RVBs[i].vertices.size())
				{
					glActiveTexture(GL_TEXTURE0);
					ird->BindTexture(rm.diftextures[0].id);
					ird->StartDraw( RVCs->at(i3)->RVBs[i].met);
					if(RVCs->at(i3)->RVBs[i].texturecoords.size() > i2)
					ird->TextCoord2(RVCs->at(i3)->RVBs[i].texturecoords[i2].x, RVCs->at(i3)->RVBs[i].texturecoords[i2].y);
					if(RVCs->at(i3)->RVBs[i].normals.size() > i2)
					ird->Normal(RVCs->at(i3)->RVBs[i].normals[i2]);
					if(RVCs->at(i3)->RVBs[i].vertices.size() > i2)
					ird->Vertex3( RVCs->at(i3)->RVBs[i].vertices[i2]);
					i2++;
					if(RVCs->at(i3)->RVBs[i].texturecoords.size() > i2)
					ird->TextCoord2(RVCs->at(i3)->RVBs[i].texturecoords[i2].x, RVCs->at(i3)->RVBs[i].texturecoords[i2].y);
					if(RVCs->at(i3)->RVBs[i].normals.size() > i2)
					ird->Normal(RVCs->at(i3)->RVBs[i].normals[i2]);
					if(RVCs->at(i3)->RVBs[i].vertices.size() > i2)
					ird->Vertex3( RVCs->at(i3)->RVBs[i].vertices[i2]);
					i2++;
					if(RVCs->at(i3)->RVBs[i].texturecoords.size() > i2)
					ird->TextCoord2(RVCs->at(i3)->RVBs[i].texturecoords[i2].x, RVCs->at(i3)->RVBs[i].texturecoords[i2].y);
					if(RVCs->at(i3)->RVBs[i].normals.size() > i2)
					ird->Normal(RVCs->at(i3)->RVBs[i].normals[i2]);
					if(RVCs->at(i3)->RVBs[i].vertices.size() > i2)
					ird->Vertex3( RVCs->at(i3)->RVBs[i].vertices[i2]);
				ird->EndDraw();
				i2++;
				}
			}
		}
		}
	}

	RSRExtended::~RSRExtended()
	{

	}