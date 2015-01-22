#include "RMDeferred.h"


RTT::RTT()
{


	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER ,fbo);

	glGenTextures(3, texts);
	for(int i = 0; i < 3; i++)
	{
	glBindTexture(GL_TEXTURE_2D, texts[i]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, 1280, 720, 0, GL_RGBA, GL_FLOAT, 0);
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



ShadowMap::ShadowMap(GLuint sw, GLuint sh)
{
	w = 4096;
	h = 4096;

	for(int i = 0; i < 6; i++)
	{
	cube[i].Identity();
	}
	 glGenFramebuffersEXT(1, &sfbo);
    glGenRenderbuffersEXT(1, &srbo);

    // Bind the FBO so that the next operations will be bound to it
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sfbo);

    // Bind the depth buffer
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, srbo);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, w, h);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, srbo);

    // Generate and bind the OGL texture for diffuse
    glGenTextures(1, &st);
    glBindTexture(GL_TEXTURE_2D, st);
// fixes seam-artifacts due to numerical precision limitations

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

GLint internal_format = GL_DEPTH_COMPONENT24; 
GLenum data_type = GL_UNSIGNED_INT;
// float z-buffer (if more precision is needed)
// GLint internal_format = GL_DEPTH_COMPONENT32F;
// GLenum data_type = GL_FLOAT;
GLenum format = GL_DEPTH_COMPONENT;
//for (GLint face = 0; face < 6; face++) {
//glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 
//0, 
//internal_format, 
//2048, 2048, 0, 
//format, 
//data_type, 
//NULL //content need not be specified
//);
//}

glTexImage2D(GL_TEXTURE_2D, 
0, 
internal_format, 
w, h, 0, 
format, 
data_type, 
NULL); //content need not be specified
   glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
st, 0);
   

	// Check if all worked fine and unbind the FBO
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if( status != GL_FRAMEBUFFER_COMPLETE_EXT)
		throw new std::exception("Can't initialize an FBO render texture. FBO initialization failed.");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    
}

void ShadowMap::Write()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sfbo);
	glDrawBuffer(GL_NONE);
	glViewport(0,0,w, h);
}

void ShadowMap::Read()
{

glActiveTextureARB(GL_TEXTURE3);
glBindTexture(GL_TEXTURE_2D, st);
}

ShadowMap::~ShadowMap()
{
	glDeleteTextures(1, &st);
	glDeleteFramebuffers(1, &sfbo);
}

void ShadowMap::SetCUBE(GLuint handle)
{
	float mm[] = {1,0,0,0,
				0,0,-1,0,
				0,1,0,0,
				0,0,0,1};
	
				for(short i = 0; i < 6; i++)
				{
				std::string name = "cm_mat[" + i + ']';
				glUniformMatrix4fv(glGetUniformLocation(handle, name.c_str()), 1, 0, mm);
				}
}

	RMDeferred::RMDeferred(RebGDC * data)
	{
		ird = data->rd;
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
		shadowProgram.AddShaderFile(rfs->Search("vshadow.rvs", "Shaders"));
		/*shadowProgram.AddShaderFile(rfs->Search("gshadow.rgs", "Shaders"));*/
	
	

		geoProgram.Link();
			lightProgram.Link();
			shadowProgram.Link();
			sm = new ShadowMap(1280, 720);
	}


	unsigned long int RMDeferred::gettriang()
	{
		return 0;
	}

	void RMDeferred::PassGeom()
	{
		not = 0;
		tt.Write();
		geoProgram.Use();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sm->Read();

		RebMatrix shadowmat, sha, res, bias;
	shadowmat.Identity();
	shadowmat.Translate(0,-10,0);

	sha.Identity();
	sha.RotyByDeg(90,0,0);

	res = shadowmat * sha;
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
				
				float mm[16];
				(RVCs->at(i3)->RVBs[i].trans * RVCs->at(i3)->transf).glm(mm);

				
				
				GLuint mmloc = glGetUniformLocation(geoProgram.GetHandle(), "mmat");
				glUniformMatrix4fv(mmloc, 1, 0, mm);

				ird->GetViewportMat().glm(mm);
				mmloc = glGetUniformLocation(geoProgram.GetHandle(), "viewmat");
				glUniformMatrix4fv(mmloc, 1, 0, mm);

				res.glm(mm);
				mmloc = glGetUniformLocation(geoProgram.GetHandle(), "shadmat");
				glUniformMatrix4fv(mmloc, 1, 0, mm);

				glUniform1i(glGetUniformLocation(geoProgram.GetHandle(), "difftext"), 0);

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
					/*tris[count] = RVCs->at(i3)->RVBs[i].vertices[i2+t].x;
					tris[count+1] = RVCs->at(i3)->RVBs[i].vertices[i2+t].y;
					tris[count+2] = RVCs->at(i3)->RVBs[i].vertices[i2+t].z;*/
					}
				ird->EndDraw();
				i2 += 3;
				
				}
			}
		}
		}
		glDisable(GL_DEPTH_TEST);
	}


	unsigned long int RMDeferred::getFloats()
	{
		unsigned long int ret = 0;
		for (UINT i3 = 0; i3 < RVCs->size(); i3++)
		{
	
		for (UINT i = 0; i < RVCs->at(i3)->RVBs.size(); i++)
		{
				ret += 3 * RVCs->at(i3)->RVBs[i].vertices.size();
				}
			}
		return ret;
	}






	void RMDeferred::ShadowPass()
	{
		sm->Write();
		shadowProgram.Use();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//test

		RebMatrix rot, sca;
		rot.Identity();
		rot.RotyByDeg(0, 90, 0);

		sca.Identity();
		sca.Translate(0, 0, -1);

		RebVector rv(0, 0, 0);

		//end of test

		glUniform3f(glGetUniformLocation(shadowProgram.GetHandle(), "ep"), 0,20,0);
		
	RebMatrix shadowmat, sha, res, bias;
	shadowmat.Identity();
	shadowmat.Translate(0,-20,0);


		bias.Identity();
	bias.Frustum(-1,1,-1,1,1,1000);

	res.Identity();
	res.RotyByDeg(90,0,0);
	/*	shadowmat.InverseOf(shadowmat);*/
			float mm[16];	
	/*sm->SetCUBE(shadowProgram.GetHandle());*/

		unsigned int i2;
		for (UINT i3 = 0; i3 < RVCs->size(); i3++)
		{
			
			
		for (UINT i = 0; i < RVCs->at(i3)->RVBs.size(); i++)
		{
			if(RVCs->at(i3)->RVBs[i].Renderable)
			{
				
				
				
				(RVCs->at(i3)->RVBs[i].trans * RVCs->at(i3)->transf).glm(mm);
				GLuint mmloc = glGetUniformLocation(shadowProgram.GetHandle(), "mmat");
				glUniformMatrix4fv(mmloc, 1, 0, mm);
				(shadowmat * res).glm(mm);
				mmloc = glGetUniformLocation(shadowProgram.GetHandle(), "sm");
				glUniformMatrix4fv(mmloc, 1, 0, mm);
				bias.glm(mm);
				mmloc = glGetUniformLocation(shadowProgram.GetHandle(), "cm");
				glUniformMatrix4fv(mmloc, 1, 0, mm);
				i2 = 0;
				while (i2 < RVCs->at(i3)->RVBs[i].vertices.size())
				{
					
					ird->StartDraw( RVCs->at(i3)->RVBs[i].met);
					for (short t = 0; t < 3; t++)
					{
					if(RVCs->at(i3)->RVBs[i].vertices.size() > i2+t)
					glVertex3fv(RVCs->at(i3)->RVBs[i].vertices[i2+t].glv());
					/*tris[count] = RVCs->at(i3)->RVBs[i].vertices[i2+t].x;
					tris[count+1] = RVCs->at(i3)->RVBs[i].vertices[i2+t].y;
					tris[count+2] = RVCs->at(i3)->RVBs[i].vertices[i2+t].z;*/
					}
				ird->EndDraw();
				i2 += 3;
				
				}
			}
		}
		}
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}







	void RMDeferred::Shade()
	{
		tt.Read();
		sm->Read();
		lightProgram.Use();


		RebMatrix shadowmat, sha, res, bias;
	shadowmat.Identity();
	shadowmat.Translate(0,-20,0);

	sha.Identity();
	sha.RotyByDeg(90,0,0);

	bias.Identity();
	bias.Frustum(-1,1,-1,1,1,1000);


	res = shadowmat * sha;
		
		glUniform1i(glGetUniformLocationARB(lightProgram.GetHandle(), "shadowmap"), 3);

				float mm[16];
				res.glm(mm);
				glUniformMatrix4fv(glGetUniformLocation(lightProgram.GetHandle(), "sm"), 1, 0, mm);

				bias.glm(mm);

				glUniformMatrix4fv(glGetUniformLocation(lightProgram.GetHandle(), "cm"), 1, 0, mm);

		tt.bind(lightProgram.GetHandle());
		GLuint nl = glGetUniformLocation(lightProgram.GetHandle(), "num_lights");
		glUniform1ui(nl, 1);
		GLuint nl2 = glGetUniformLocation(lightProgram.GetHandle(), "light[0].position");
		glUniform3f(nl2, 0,20,0);
		GLuint nl3 = glGetUniformLocation(lightProgram.GetHandle(), "light[0].color");
		glUniform3f(nl3, 1,1,1);

		



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
	
	ShadowPass();
	PassGeom();
	Shade();
}

RMDeferred::~RMDeferred()
{
	delete sm;
}