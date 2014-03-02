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
	std::string name;
	unsigned int pid;
	std::vector<RebShader> shaders;
};

class RebShaderSystem : public IShaderSystem
{
	std::vector<RebShaderProgram> programs;

public:
	void Init();

	unsigned int GetProgramid(std::string name);

	unsigned int GetShaderid(std::string source);

	void ActivateProgram(unsigned int programid);

	std::string GetShaderData(std::string file);

	void CreateProgram(std::string name,unsigned int * programid);

	void AddShader(std::string shaderfile, unsigned int programid, unsigned int * shaderid);

	void DeleteShader(unsigned int shaderid);

	void DeleteProgram(unsigned int programid);

	~RebShaderSystem();
};



#endif