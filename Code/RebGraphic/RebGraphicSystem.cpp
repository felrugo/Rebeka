// File: ZFXRenderer.cpp   
   
#include "RebGraphicSystem.h"


RebGraphicSystem::RebGraphicSystem()
{
	runing = false;
	rd = 0;
}

void RebGraphicSystem::CreateDevice()
{
	if(runing == false)
	{
	mDLL = LoadLibrary("RebGL.dll");
	CREATERENDERDEVICE _CreateRenderDevice = 0;
	_CreateRenderDevice = (CREATERENDERDEVICE)GetProcAddress(mDLL, "CreateRenderDevice");
	_CreateRenderDevice(&rd);
	runing = true;
	}
}

void RebGraphicSystem::ReleaseDevice()
{
	RELEASERENDERDEVICE _ReleaseRenderDevice = 0;
	_ReleaseRenderDevice = (RELEASERENDERDEVICE)GetProcAddress(mDLL, "ReleaseRenderDevice");
	if (runing == true)
	{
	_ReleaseRenderDevice(&rd);
	runing = false;
	}
}

IRenderDevice * RebGraphicSystem::GetDevice()
{
	return rd;
}

HINSTANCE RebGraphicSystem::GetModule()
{
	return mDLL;
}

RebGraphicSystem::~RebGraphicSystem()
{
	ReleaseDevice();
}