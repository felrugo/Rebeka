#include "RebGL_LightSystem.h"


RebGLLight::RebGLLight(RebColor col, RebVector spos, LightType slt, RebVector spotlookat, RebGDC * gdc)
{
	view.Identity();
	color = col;
	pos = spos;
	lt = slt;
	if (lt == LT_POINT)
	{
		sm = new ShadowMapCube(gdc);
	}
	else
	{
		sm = new ShadowMap2D(gdc);
	}
	sm->SetPos(pos);
}




void RebGLLight::SetPos(RebVector spos)
{
	pos = spos;
	sm->SetPos(pos);
}

RebVector RebGLLight::GetPos()
{
	return pos;
}

bool RebGLLight::GetSop()
{
	return (bool)lt;
}

ShadowMap * RebGLLight::GetShadowMap()
{
	return sm;
}

RebGLLightSystem::RebGLLightSystem(RebGDC * sgdc)
{
	lights.clear();
	gdc = sgdc;
	
}


RebLight * RebGLLightSystem::AddLight(RebColor col, RebVector spos, LightType lt, RebVector spotlookat)
{
	RebLight * rl = new RebGLLight(col, spos, lt, spotlookat, gdc);
	lights.push_back(rl);
	return rl;
}

void RebGLLightSystem::DeleteLight(RebLight * todel)
{
	for (unsigned int i = 0; i < lights.size(); i++)
	{
		if (lights[i] == todel)
		delete lights[i];
	}
}

std::vector<RebLight*> * RebGLLightSystem::GetLights()
{
	return &lights;
}

RebGLLightSystem::~RebGLLightSystem()
{
	for (unsigned int i = 0; i < lights.size(); i++)
	{
		delete lights[i];
	}
	lights.clear();
}