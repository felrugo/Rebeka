
#ifndef REBRENDERTECHNIC
#define REBRENDERTECHNIC


#include "RebGL_SS.h"
#include <assert.h>
#include <memory>


class ShadowMap
{
protected:
	RebVector lpos;
public:
	virtual void Write() = 0;
	virtual void SetPos(RebVector set);
	virtual void Read() = 0;
	virtual void ShadowPass() = 0;
};

class ShadowMap2D : public ShadowMap
{
	GLuint sfbo, st, post;
	unsigned int w, h;
	IRenderDevice* ird;
	RebGLShaderProgram shadowProgram;

public:
	ShadowMap2D(RebGDC * rgdc);
	void Write();
	void Read();
	void ShadowPass();
	~ShadowMap2D();
};

class ShadowMapCube : public ShadowMap
{
	GLuint sfbo, st, post;
	unsigned int w, h;
	IRenderDevice* ird;
	RebGLShaderProgram shadowProgram;
public:
	ShadowMapCube(RebGDC * rgdc);
	void SetCUBE(GLuint handle);
	void Write();
	void Read();
	void ShadowPass();
	~ShadowMapCube();
};


#endif