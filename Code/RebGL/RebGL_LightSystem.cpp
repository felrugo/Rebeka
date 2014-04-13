#include "RebGL_LightSystem.h"

RebGLLightSystem::RebGLLightSystem()
{
	lights.clear();
	
}


RebLight * RebGLLightSystem::AddLight(RebColor col, RebVector spos)
{
	RebLight * rl = new RebLight();
	rl->color = col;
	rl->pos = spos;
	lights.push_back(rl);
	return rl;
}



RebGLLightSystem::~RebGLLightSystem()
{
	for (unsigned int i = 0; i < lights.size(); i++)
	{
		delete lights[i];
	}
	lights.clear();
	glDisable(GL_LIGHTING);
}