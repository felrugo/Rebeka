#include "RebGL_SS.h"


RebShaderSystem::RebShaderSystem(IRenderDevice * sird)
{
		glewInit();
	programs.clear();
	ird = sird;
	irm = 0;
}




std::string RebShaderSystem::GetShaderData(std::string file)
{
	std::ifstream t(file.c_str());
std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
 
return str;
}


void RebShaderSystem::CreateProgram(std::string name, unsigned int * programid)
{
GLenum my_program;
my_program = glCreateProgramObjectARB();
RebShaderProgram rsp;
rsp.pid = my_program;
rsp.name = name;
rsp.linked = false;
programs.push_back(rsp);
*programid = my_program;
}

void RebShaderSystem::AddShader(std::string shaderfile, unsigned int programid, unsigned int * shaderid)
{
GLenum my_shader;

if(GetShaderid(shaderfile) == 0)
{

if (shaderfile.find(".rvs", 0, 4) != std::string::npos)
{
my_shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
}
else if (shaderfile.find(".rfs", 0, 4) != std::string::npos)
{
	my_shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
}
else
{
	return;
}

if(shaderid != 0)
{
	*shaderid = my_shader;
}
std::string asd = GetShaderData(shaderfile);

const char * g = asd.c_str();

glShaderSourceARB(my_shader, 1, &g, NULL);

glCompileShaderARB(my_shader);
}

else
{
	my_shader = GetShaderid(shaderfile);
}

glAttachObjectARB(programid, my_shader);

// Link The Program Object

 
// Use The Program Object Instead Of Fixed Function OpenGL

GLint isCompiled = 0;
glGetShaderiv(my_shader, GL_COMPILE_STATUS, &isCompiled);
if(isCompiled == GL_FALSE)
{
        GLint maxLength = 0;
        glGetShaderiv(my_shader, GL_INFO_LOG_LENGTH, &maxLength);
 
        //The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(my_shader, maxLength, &maxLength, &errorLog[0]);
 
        //Provide the infolog in whatever manor you deem best.
        //Exit with failure.
		glDeleteObjectARB(my_shader);
        return;
}


}


void RebShaderSystem::Link(unsigned int handle)
{
	for (unsigned int i = 0; i < programs.size(); i++)
	{
		if (programs[i].pid == handle)
		{
			programs[i].linked = true;
			glLinkProgramARB(handle);
		}
	}
}

void RebShaderSystem::DeleteShader(unsigned int shaderid)
{
	glDeleteObjectARB(shaderid);
}

void RebShaderSystem::DeleteProgram(unsigned int programid)
{
	glDeleteObjectARB(programid);
}


void RebShaderSystem::ActivateProgram(unsigned int sid)
{
	for (unsigned int i = 0; i < programs.size(); i++)
	{
		if (programs[i].pid == sid)
		{
			if(!programs[i].linked)
			glLinkProgramARB(sid);
			glUseProgramObjectARB(sid);
		}
	}
	
}


unsigned int RebShaderSystem::GetProgramid(std::string name)
{
	for (unsigned int i = 0; i < programs.size(); i++)
	{
		if (programs[i].name == name)
		{
			return programs[i].pid;
		}
	}
	return 0;
}

unsigned int RebShaderSystem::GetShaderid(std::string source)
{
	for (unsigned int i = 0; i < programs.size(); i++)
	{
		for (unsigned int i2 = 0; i2 < programs[i].shaders.size(); i2++)
		{
			if (programs[i].shaders[i2].source == source)
			{
				return programs[i].shaders[i2].sid;
			}
		}
	}
	return 0;
}




RebShaderSystem::~RebShaderSystem()
{
	glUseProgramObjectARB(0);
	for (unsigned int i = 0; i < programs.size(); i++)
	{
		for(unsigned int i2 = 0; i < programs[i].shaders.size(); i2++)
		{
			glDeleteObjectARB(programs[i].shaders[i2].sid);
		}
		programs[i].shaders.clear();
		glDeleteObjectARB(programs[i].pid);
	}
	programs.clear();
	if(irm != 0)
	delete irm;
}
