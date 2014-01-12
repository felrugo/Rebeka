#ifndef REBSHADERSYSTEM_H
#define REBSHADERSYSTEM_H

#include "..\RebRenderer\IRenderDevice.h"
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
	unsigned int pid;
	std::vector<RebShader> shaders;
};

class RebShaderSystem : public IShaderSystem
{
	std::vector<unsigned int> programs;
public:
	void Init();

	void ActivateProgram(unsigned int programid);

	std::string GetShaderData(std::string file);

	void CreateProgram(unsigned int * programid);

	void AddShader(std::string shaderfile, unsigned int programid, unsigned int * shaderid);

	void DeleteShader(unsigned int shaderid);

	void DeleteProgram(unsigned int programid);

	~RebShaderSystem();
};



#endif