#ifndef RMDEFERRED
#define RMDEFERRED

#include "RebRenderTechnic.h"
#include "RebGL_LightSystem.h"
#include <assert.h>
#include <memory>

class GBuffer
{
public:
	enum GBUFFER_TEXTURE_TYPE
	{
		GBUFFER_TEXTURE_BEGIN,
		GBUFFER_TEXTURE_COLOR = GBUFFER_TEXTURE_BEGIN,
		GBUFFER_TEXTURE_POSITION,
		GBUFFER_TEXTURE_NORMAL,
		GBUFFER_TEXTURE_TEXCOORD,
		GBUFFER_NUM_TEXTURES
	};

	GBuffer(unsigned int screenWidth, unsigned int screenHeight) : width(screenWidth), height(screenHeight)
	{
		glGenFramebuffers(1, &fbo);
		glEnable(GL_DEPTH_TEST);
			// bind framebuffer for drawing
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
			glViewport(0,0,width,height);
			initializeTextures();

	   		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			assert(Status == GL_FRAMEBUFFER_COMPLETE);

	    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	~GBuffer()
	{
		destroyTextures();
		glDeleteRenderbuffers(1, &rbo);
		glDeleteFramebuffers(1, &fbo);
	}

	//  wriite into frame buffer (write G-Buffer)
	void BindForWriting()
	{
	    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
		glViewport(0,0,width,height);
   		GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
   		glDrawBuffers(GBUFFER_NUM_TEXTURES, DrawBuffers);
	}

	// read from frame buffer (read G-Buffer)
	void BindForReading()
	{
	    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	}

	// 
	void BindForStencil()
	{
		glDrawBuffer(GL_NONE);
	}

	bool check()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	   		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			if(Status == GL_FRAMEBUFFER_COMPLETE)
			{
				return true;
			}
return false;
	}

	void BindForAmbient()
	{
		glDrawBuffer(GL_COLOR_ATTACHMENT4);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//
	void BindForLighting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glDrawBuffer(GL_COLOR_ATTACHMENT4);


    	for (unsigned int i = 0 ; i < GBUFFER_NUM_TEXTURES; i++) 
    	{
        	glActiveTexture(GL_TEXTURE0 + i);	
        	glBindTexture(GL_TEXTURE_2D, textures[GBUFFER_TEXTURE_BEGIN + i]);
    	}
	}

	//
	void BindForBlt()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    	glReadBuffer(GL_COLOR_ATTACHMENT4);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//
	void BindUniform(GLint program)
	{
		glUniform1i(glGetUniformLocation(program, "color"), 0);
		glUniform1i(glGetUniformLocation(program, "pos"), 1);
		glUniform1i(glGetUniformLocation(program, "normal"), 2);
		/*glUniform1i(glGetUniformLocation(program, "texcoord"), 3);*/
		glUniform2f(glGetUniformLocation(program, "screenSize"), (float)width, (float)height);
	}

	void SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType)
	{
	    glReadBuffer(GL_COLOR_ATTACHMENT0 + TextureType);
	}

private:
	void initializeTextures()
	{
		glEnable ( GL_TEXTURE_2D );
		// generate texture object
		glGenTextures(GBUFFER_NUM_TEXTURES, textures);
		for (unsigned int i = 0; i < GBUFFER_NUM_TEXTURES; i++)
		{
			// bind texture to a target (sampling method)
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			// initialize target format (current binding)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0, GL_RGB, GL_FLOAT, 0);
			// bind texture to framebuffer to ** render into **
       		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], 0);

       		// this is also necessary for sampling textures
	        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   		}

   		// generate depth texture object
   		/*glGenTextures(1, &depthStencilTexture);
   		glBindTexture(GL_TEXTURE_2D, depthStencilTexture);
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencilTexture, 0);*/


		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);



    	// generate output texture object
    	glGenTextures(1, &outputTexture);
     	glBindTexture(GL_TEXTURE_2D, outputTexture);
     	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0, GL_RGB, GL_FLOAT, NULL);
  		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, outputTexture, 0);
	}

	void destroyTextures()
	{
		glDeleteTextures(GBUFFER_NUM_TEXTURES, textures);
		glDeleteTextures(1, &outputTexture);
		/*glDeleteTextures(1, &depthStencilTexture);*/
	}

	unsigned int width;
	unsigned int height;
	GLuint fbo;
	GLuint rbo;
	GLuint textures[GBUFFER_NUM_TEXTURES];
	GLuint outputTexture;
	GLuint depthStencilTexture;
};





class RTT
{
	GLuint fbo;
	GLuint texts[3];
public:
	RTT();
	~RTT();
	void Write();
	void bind(GLuint handle);
	int GetPostex();
	void Read();
};

class ShadowSum
{
	GLuint fbo, shadsum[2];
	GLuint depthrenderbuffer;
	RebGLShaderProgram ssum;
	RebGLLightSystem * ls;
public:
	ShadowSum(RebGDC * rgdc);
	void Write(char to);
	void SumShadows(int postexid);
	void Read();
	~ShadowSum();

};



class RMDeferred : public IRenderModel
{
	IRenderDevice * ird;
	RebFileSystem * rfs;
	RebGLLightSystem * ls;
	
	float * tris;
	std::vector<RebVertexCache*> * RVCs;
	/*RayTraceBuffer rtb;*/
	unsigned int width;
unsigned int height;

RTT tt;
ShadowSum ss;
RebGLShaderProgram geoProgram ;
RebGLShaderProgram lightProgram;
RebGLShaderProgram shadowProgram;
GLuint mainObjectID;
GLuint lightVolumeID;

unsigned long int nof, last, not;

GLuint ssbo[2];
float mo;

unsigned long int gettriang();

public:
	RMDeferred(RebGDC * data);
	~RMDeferred();
	void PassGeom();
	
	void Shade();
	unsigned long int getFloats();
	void copy();
void Render();
};





#endif