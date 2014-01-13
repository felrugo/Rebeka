#include "RebGL_SS.h"


void RebShaderSystem::Init()
{
	glewInit();
	programs.clear();
}


std::string RebShaderSystem::GetShaderData(std::string file)
{
	std::ifstream t(file.c_str());
std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
 
return str;
}


void RebShaderSystem::CreateProgram(unsigned int * programid)
{
GLenum my_program;
my_program = glCreateProgramObjectARB();
programs.push_back(my_program);
*programid = my_program;
}

void RebShaderSystem::AddShader(std::string shaderfile, unsigned int programid, unsigned int * shaderid)
{
GLenum my_shader;
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

glAttachObjectARB(programid, my_shader);

// Link The Program Object
glLinkProgramARB(programid);
 
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
	glUseProgramObjectARB(sid);
}


RebShaderSystem::~RebShaderSystem()
{
	for (int i = 0; i < programs.size(); i++)
	{
		glDeleteObjectARB(programs[i]);
	}
	programs.clear();
}