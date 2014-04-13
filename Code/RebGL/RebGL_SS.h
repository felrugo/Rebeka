#ifndef REBSHADERSYSTEM_H
#define REBSHADERSYSTEM_H

#include "..\RebRenderer\IRenderDevice.h"
#include "..\RebSupport\RebFileSystem.h"
#include <fstream>
#include <streambuf>
#include "GL\glew.h"
#include <gl\GL.h>

struct RebShader
{
	unsigned int sid;
	std::string source;
};

struct RebShaderProgram
{
	std::string name;
	unsigned int pid;
	bool linked;
	std::vector<RebShader> shaders;
	
};

class RebGLShader
{
	unsigned int phandle;
	std::vector<unsigned int> shands;
	IRenderDevice * IRD;
public:
	RebGLShader(IRenderDevice * sird);

	void AddShaderFile(RebFile file);


	~RebGLShader();
};


struct LMStruct
{
	GLuint D, A, S;
};

class RSRExtended : public IRenderModel
{
	IRenderDevice * ird;
std::vector<RebVertexCache*> * RVCs;
	GLuint programHandle;
	GLuint texloc;
	GLuint texCloc;
	LMStruct Light, Material;
	GLuint lp;
	GLuint shine;

	GLuint positionBufferHandle;
GLuint colorBufferHandle;
public:
	RSRExtended(IRenderDevice * sird);
	void TerrainRender();
	void Render();
	~RSRExtended();
};


class RebShaderSystem : public IShaderSystem
{
	std::vector<RebShaderProgram> programs;

	IRenderModel * irm;

	IRenderDevice * ird;

public:
	RebShaderSystem(IRenderDevice * sird);

	unsigned int GetProgramid(std::string name);

	unsigned int GetShaderid(std::string source);

	void ActivateProgram(unsigned int programid);

	std::string GetShaderData(std::string file);

	void CreateProgram(std::string name,unsigned int * programid);

	void Link(unsigned int handle);

	void AddShader(std::string shaderfile, unsigned int programid, unsigned int * shaderid);

	void DeleteShader(unsigned int shaderid);

	void DeleteProgram(unsigned int programid);

	~RebShaderSystem();
};



#endif