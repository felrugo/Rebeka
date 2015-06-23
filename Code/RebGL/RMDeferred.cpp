#include "RMDeferred.h"


RTT::RTT()
{


	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER ,fbo);

	glGenTextures(3, texts);
	for(int i = 0; i < 3; i++)
	{
	glBindTexture(GL_TEXTURE_2D, texts[i]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, 1280, 720, 0, GL_RGB, GL_FLOAT, 0);
	 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTextureARB(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, texts[i], 0);
	}

	GLuint depthrenderbuffer;
glGenRenderbuffersEXT(1, &depthrenderbuffer);
glBindRenderbufferEXT(GL_RENDERBUFFER, depthrenderbuffer);
glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);
glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
glDrawBuffersARB(3, DrawBuffers);



}


void RTT::Write()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER, fbo);
glViewport(0,0,1280,720);
// glMatrixMode( GL_PROJECTION );
//    glLoadIdentity( );
// 
//	GLfloat ratio;
//	ratio = ( GLfloat )1280 / ( GLfloat )720;
//    /* Set our perspective */
//    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
glDrawBuffersARB(3, DrawBuffers);

}

void RTT::Read()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
//glViewport(0,0,1280,720);
for(int i = 0; i < 3; i++)
{
glActiveTextureARB(GL_TEXTURE0 + i);
glBindTexture(GL_TEXTURE_2D, texts[i]);
}
}

int RTT::GetPostex()
{
	return texts[1];
}

void RTT::bind(GLuint handle)
{
	GLuint loc = glGetUniformLocationARB(handle, "color");
	glUniform1i(loc, 0);
	loc = glGetUniformLocationARB(handle, "pos");
	glUniform1i(loc, 1);
	loc = glGetUniformLocationARB(handle, "norm");
	glUniform1i(loc, 2);
}

RTT::~RTT()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
//glViewport(0,0,1280,720);
// glMatrixMode( GL_PROJECTION );
//    glLoadIdentity( );
// 
//	GLfloat ratio;
//	ratio = ( GLfloat )1280 / ( GLfloat )720;
//    /* Set our perspective */
//    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
glDeleteTextures(3, texts);
glDeleteFramebuffersEXT(1, &fbo);
}




ShadowSum::ShadowSum(RebGDC * rgdc)
{
	ls = (RebGLLightSystem*)rgdc->rd->GetLightSystem();

	ssum.AddShaderFile(rgdc->rfs->Search("ShadowSumV.rvs", "Shaders"));
	ssum.AddShaderFile(rgdc->rfs->Search("ShadowSum.rfs", "Shaders"));
	ssum.Link();

	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER, fbo);


	
	glGenRenderbuffersEXT(1, &depthrenderbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	glGenTextures(2, shadsum);
	for (char a = 0; a < 2; a++)
	{

		glBindTexture(GL_TEXTURE_2D, shadsum[a]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 1280, 720, 0, GL_RGB, GL_FLOAT, 0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + a, shadsum[a], 0);
	}

	// Check if all worked fine and unbind the FBO
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
		throw new std::exception("Can't initialize an FBO render texture. FBO initialization failed.");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void ShadowSum::Write(char to)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, 1280, 720);
	GLuint db = GL_COLOR_ATTACHMENT0 + to;
	glDrawBuffers(1, &db);
}


void ShadowSum::SumShadows(int postexid)
{
	
	ssum.Use();



	for (unsigned int i = 0; i < ls->GetLights()->size(); i++)
	{
		

		RebGLLight * cur = (RebGLLight*)ls->GetLights()->at(i);
		cur->GetShadowMap()->ShadowPass();
		

		ssum.Use();
		
		cur->GetShadowMap()->Read();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, postexid);

		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "postex"), 0);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "shad2d"), 1);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "shadcube"), 2);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "prev"), 3);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, shadsum[!(bool)(i % 2)]);

		glUniform3f(glGetUniformLocation(ssum.GetHandle(), "lightpos"), cur->GetPos().x, cur->GetPos().y, cur->GetPos().z);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "first"), i < 1);
		glUniform1i(glGetUniformLocation(ssum.GetHandle(), "sop"), cur->GetSop());

		Write(i % 2);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(1, 1, 0);
		glTexCoord2f(1, -1);
		glVertex3f(1, -1, 0);
		glTexCoord2f(-1, -1);
		glVertex3f(-1, -1, 0);
		glTexCoord2f(-1, 1);
		glVertex3f(-1, 1, 0);
		glEnd();
	}
}

void ShadowSum::Read()
{
	glActiveTextureARB(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, shadsum[(ls->GetLights()->size()-1) % 2]);
}


ShadowSum::~ShadowSum()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteTextures(2, shadsum);
	glDeleteRenderbuffers(1, &depthrenderbuffer);
	glDeleteFramebuffers(1, &fbo);
}
















RMDeferred::RMDeferred(RebGDC * data) : ss(data)
	{
		ird = data->rd;
		ls = (RebGLLightSystem *)ird->GetLightSystem();
		ls->AddLight(RebColor(0.56, 0.6, 1), RebVector(0, 20, 0), LT_POINT, RebVector());
		/*ls->AddLight(RebColor(1, 1, 1), RebVector(-3, 19, 0), LT_POINT, RebVector());*/
		rfs = data->rfs;
		nof = 0;
		last = 0;
		tris = 0;
		RVCs = ird->GetVertexCacheManager()->GetRVCs();
		mo = 0;
		geoProgram.AddShaderFile(rfs->Search("write.rvs", "Shaders"));
		geoProgram.AddShaderFile(rfs->Search("fwrite.rfs", "Shaders"));
		lightProgram.AddShaderFile(rfs->Search("read.rvs", "Shaders"));
		lightProgram.AddShaderFile(rfs->Search("fread.rfs", "Shaders"));
		terrProgram.AddShaderFile(rfs->Search("terrain.rfs", "Shaders"));
		terrProgram.AddShaderFile(rfs->Search("terrain.rvs", "Shaders"));
		/*shadowProgram.AddShaderFile(rfs->Search("vshadow.rvs", "Shaders"));
		shadowProgram.AddShaderFile(rfs->Search("fshadow.rfs", "Shaders"));
		shadowProgram.AddShaderFile(rfs->Search("gshadow.rgs", "Shaders"));*/
	
	

		geoProgram.Link();
			lightProgram.Link();
			terrProgram.Link();
			
	}


	unsigned long int RMDeferred::gettriang()
	{
		return 0;
	}


	void SkyBoxRender()
	{

	}

	void RMDeferred::TerrainRender()
	{
		terrProgram.Use();

		float mm[16];


		

		ird->GetViewportMat().glm(mm);
		
		glUniformMatrix4fv(glGetUniformLocation(geoProgram.GetHandle(), "viewmat"), 1, 0, mm);


		for (size_t i = 0; i < ird->GetEnv()->GetTerrains()->size(); i++)
		{
			ird->GetEnv()->GetTerrains()->at(i)->GetTrans().glm(mm);
			glUniformMatrix4fv(glGetUniformLocation(terrProgram.GetHandle(), "mmat"), 1, 0, mm);
			ird->GetEnv()->GetTerrains()->at(i)->Draw();
		}
		
	}

	void RMDeferred::PassGeom()
	{
		not = 0;
		tt.Write();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		TerrainRender();


		geoProgram.Use();
		
		
		
		for (UINT i3 = 0; i3 < RVCs->size(); i3++)
		{
			RebSkin rs = RVCs->at(i3)->GetSkin();
			
		for (UINT i = 0; i < RVCs->at(i3)->GetRVBs()->size(); i++)
		{
			if(RVCs->at(i3)->GetRVBs()->at(i)->isRenderable())
			{
				RebMaterial rm = rs.materials[RVCs->at(i3)->GetRVBs()->at(i)->GetMaterialID()];
				
				
				float mm[16];
				(*RVCs->at(i3)->GetTrans() * *RVCs->at(i3)->GetRVBs()->at(i)->GetTrans()).glm(mm);

				
				
				GLuint mmloc = glGetUniformLocation(geoProgram.GetHandle(), "mmat");
				glUniformMatrix4fv(mmloc, 1, 0, mm);

				ird->GetViewportMat().glm(mm);
				mmloc = glGetUniformLocation(geoProgram.GetHandle(), "viewmat");
				glUniformMatrix4fv(mmloc, 1, 0, mm);


				glUniform1i(glGetUniformLocation(geoProgram.GetHandle(), "difftext"), 0);

				
					glActiveTexture(GL_TEXTURE0);
					if(rm.diftextures.size() > 0)
					ird->BindTexture(rm.diftextures[0].id);

					RVCs->at(i3)->GetRVBs()->at(i)->Draw();
			}
		}
		}
		glDisable(GL_DEPTH_TEST);
	}


	//unsigned long int RMDeferred::getFloats()
	//{
	//	unsigned long int ret = 0;
	//	for (UINT i3 = 0; i3 < RVCs->size(); i3++)
	//	{
	//
	//	for (UINT i = 0; i < RVCs->at(i3)->RVBs.size(); i++)
	//	{
	//			ret += 3 * RVCs->at(i3)->RVBs[i].vertices.size();
	//			}
	//		}
	//	return ret;
	//}






	void RMDeferred::Shade()
	{

		ss.SumShadows(tt.GetPostex());

		tt.Read();
		//sm->Read();
		lightProgram.Use();


		RebMatrix shadowmat, sha, res, bias;
	shadowmat.Identity();
	shadowmat.Translate(0,-10,0);

	sha.Identity();
	sha.RotyByDeg(90,0,0);

	bias.Identity();
	bias.Perspective(90, 1, 1, 1000);


	res = shadowmat * sha;
		
		glUniform1i(glGetUniformLocationARB(lightProgram.GetHandle(), "shadowsum"), 3);

		ss.Read();


				float mm[16];
				res.glm(mm);
				glUniformMatrix4fv(glGetUniformLocation(lightProgram.GetHandle(), "sm"), 1, 0, mm);

				bias.glm(mm);

				glUniformMatrix4fv(glGetUniformLocation(lightProgram.GetHandle(), "cm"), 1, 0, mm);

		tt.bind(lightProgram.GetHandle());

		GLuint nl = glGetUniformLocation(lightProgram.GetHandle(), "num_lights");
		glUniform1ui(nl, ls->GetLights()->size());

		for (unsigned int i = 0; i < ls->GetLights()->size(); i++)
		{
			GLuint nl2 = glGetUniformLocation(lightProgram.GetHandle(), std::string("light[" + std::to_string(i) + "].position").c_str());
			RebVector lpos;
			glUniform3f(nl2, ls->GetLights()->at(i)->GetPos().x, ls->GetLights()->at(i)->GetPos().y, ls->GetLights()->at(i)->GetPos().z);
			GLuint nl3 = glGetUniformLocation(lightProgram.GetHandle(), std::string("light[" + std::to_string(i) + "].color").c_str());
			glUniform3f(nl3, ls->GetLights()->at(i)->GetColor().x, ls->GetLights()->at(i)->GetColor().y, ls->GetLights()->at(i)->GetColor().z);
		}
		



		RebVector mmv(0,0,0);
				RebMatrix test;
				test.InverseOf(ird->GetViewportMat());
				mmv = mmv * test;

				glUniform3f(glGetUniformLocation(lightProgram.GetHandle(), "mmv"), mmv.x, mmv.y, mmv.z);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glColor4f(1,0,0,1);
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);
		glVertex3f(1,1,0);
		glTexCoord2f(1,-1);
		glVertex3f(1,-1,0);
		glTexCoord2f(-1,-1);
		glVertex3f(-1,-1,0);
		glTexCoord2f(-1,1);
		glVertex3f(-1, 1, 0);
		glEnd();
	

	
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void RMDeferred::copy()
	{
		
		glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

void RMDeferred::Render()
{
	
	
	PassGeom();
	
	Shade();
}

RMDeferred::~RMDeferred()
{
	//delete sm;
}