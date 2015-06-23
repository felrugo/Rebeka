#ifndef REBSHADERSYSTEM_H
#define REBSHADERSYSTEM_H

#include "..\RebGraphic\IRenderDevice.h"
#include "..\RebSupport\RebFileSystem.h"
#include <fstream>
#include <streambuf>
#include "GL\glew.h"
#include <gl\GL.h>


class RebGLShaderProgram;

class RebGLShader
{
	friend class RebGLShaderProgram;
	enum ShaderType {RS_VERTEX, RS_FRAGMENT, RS_GEOMETRY};
	unsigned int pshader;
	ShaderType ty;
	bool * compiled;
	bool * error;
	unsigned int * copied;
	std::string GetShaderData(std::string file);
	void operator =(RebGLShader e);
	RebGLShader(const RebGLShader& cop);
	RebGLShader();
	bool IsCompiled();
	ShaderType GetType();
	void Source(RebFile file);
	void Compile();
	unsigned int GetHandle();
	~RebGLShader();
};

class RebGLShaderProgram
{
	unsigned int phandle;
	bool linked;
	RebGLShader * vs;
	RebGLShader * fs;
	RebGLShader * gs;
	std::string GetShaderData(std::string file);
public:
	RebGLShaderProgram();

	void AddShaderFile(RebFile shad);

	void Link();

	void Use();

	static void UseDefault();

	unsigned int GetHandle();

	~RebGLShaderProgram();
};


struct LMStruct
{
	GLuint D, A, S;
};




//class RebShaderSystem : public IShaderSystem
//{
//	std::vector<RebShaderProgram> programs;
//
//	IRenderModel * irm;
//
//	IRenderDevice * ird;
//
//public:
//	RebShaderSystem(IRenderDevice * sird);
//
//	unsigned int GetProgramid(std::string name);
//
//	unsigned int GetShaderid(std::string source);
//
//	void ActivateProgram(unsigned int programid);
//
//	std::string GetShaderData(std::string file);
//
//	void CreateProgram(std::string name,unsigned int * programid);
//
//	void Link(unsigned int handle);
//
//	void AddShader(std::string shaderfile, unsigned int programid, unsigned int * shaderid);
//
//	void DeleteShader(unsigned int shaderid);
//
//	void DeleteProgram(unsigned int programid);
//
//	~RebShaderSystem();
//};



#endif