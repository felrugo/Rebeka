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
//glViewport(0,0,1280,720);
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









	RMDeferred::RMDeferred(RebGDC * data)
	{
		ird = data->rd;
		rfs = data->rfs;

		RVCs = ird->GetVertexCacheManager()->GetRVCs();

		geoProgram.AddShaderFile(rfs->Search("write.rvs", "Shaders"));
		geoProgram.AddShaderFile(rfs->Search("fwrite.rfs", "Shaders"));
		lightProgram.AddShaderFile(rfs->Search("read.rvs", "Shaders"));
		lightProgram.AddShaderFile(rfs->Search("fread.rfs", "Shaders"));

		geoProgram.Link();
			lightProgram.Link();
	}

	void RMDeferred::PassGeom()
	{
		tt.Write();
		geoProgram.Use();
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

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

				ird->TransformMatrix(ird->GetViewportMat());
				
				GLuint mmloc = glGetUniformLocation(geoProgram.GetHandle(), "mmat");
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
					}
				ird->EndDraw();
				i2 += 3;
				}
			}
		}
		}

		glDisable(GL_DEPTH_TEST);
	}

	void RMDeferred::Shade()
	{
		tt.Read();
		lightProgram.Use();
		tt.bind(lightProgram.GetHandle());
		GLuint nl = glGetUniformLocation(lightProgram.GetHandle(), "num_lights");
		glUniform1i(nl, 1);
		GLuint nl2 = glGetUniformLocation(lightProgram.GetHandle(), "light[0].position");
		glUniform3f(nl2, 0,3,0);
		GLuint nl3 = glGetUniformLocation(lightProgram.GetHandle(), "light[0].color");
		glUniform3f(nl3, 1,1,1);


		RebVector mmv(0,0,-1);
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