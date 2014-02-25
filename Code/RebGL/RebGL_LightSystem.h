#ifndef REBGL_LS
#define REBGL_LS

#include "..\RebRenderer\IRenderDevice.h"
#include <gl\GL.h>

class RebGLLightSystem : public ILightSystem
{

	std::vector<RebLight*> lights;

public:
	RebGLLightSystem();

	RebLight * AddLight(RebColor col, RebVector spos);

	void Update();

	~RebGLLightSystem();
};







#endif