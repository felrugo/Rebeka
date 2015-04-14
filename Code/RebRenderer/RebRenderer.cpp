// File: ZFXRenderer.cpp   
   
#include "IRenderer.h"


Renderer::Renderer()
{
	runing = false;
	rd = 0;
}

void Renderer::CreateDevice()
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

void Renderer::ReleaseDevice()
{
	RELEASERENDERDEVICE _ReleaseRenderDevice = 0;
	_ReleaseRenderDevice = (RELEASERENDERDEVICE)GetProcAddress(mDLL, "ReleaseRenderDevice");
	if (runing == true)
	{
	_ReleaseRenderDevice(&rd);
	runing = false;
	}
}

IRenderDevice * Renderer::GetDevice()
{
	return rd;
}

HINSTANCE Renderer::GetModule()
{
	return mDLL;
}

Renderer::~Renderer()
{
	ReleaseDevice();
}