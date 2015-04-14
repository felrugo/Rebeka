#ifndef REBGL_LS
#define REBGL_LS

#include "..\RebRenderer\IRenderDevice.h"
#include "RebRenderTechnic.h"
#include <gl\GL.h>


class RebGLLight : public RebLight
{
	ShadowMap * sm;
public:
	RebGLLight(RebColor col, RebVector spos, LightType slt, RebVector spotlookat, RebGDC * gdc);
	void SetPos(RebVector spos);
	RebVector GetPos();
	ShadowMap * GetShadowMap();
	bool GetSop();

};

class RebGLLightSystem : public ILightSystem
{

	std::vector<RebLight*> lights;
	RebGDC * gdc;

public:
	RebGLLightSystem(RebGDC * sgdc);

	RebLight * AddLight(RebColor col, RebVector spos, LightType lt, RebVector spotlookat);
	void DeleteLight(RebLight * todel);
	std::vector<RebLight*> * GetLights();
	void Update();

	~RebGLLightSystem();
};







#endif