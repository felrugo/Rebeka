
#ifndef REBGL_H
#define REBGL_H
#include "GL\glew.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <gl\GLU.h>
#include "../RebRenderer/IRenderDevice.h"
#include "RebGL_skinmanager.h"
#include "RebGL_VCM.h"
#include "RebGL_SS.h"
#include "RebGL_LightSystem.h"
#include "RebEnv.h"
#include "..\RebSupport\RebGDC.h"







class RebGL : public IRenderDevice
{

	bool skinmanruning;

	bool VCMRunning;

	int w, h;

	

	ISkinManager * skinman;

	IVertexCacheManager * VCM;

	IShaderSystem * ISS;

	RebFileSystem * rfs;

	IRenderModel * IRM;

	ILightSystem * ILS;

	IWindowManager * iwm;

	IGameEnv * GE;

	RebMatrix MatViewport;

	void * ViewportID;
	

public:

	void * tm();
	
	void Init(RebGDC * gd);

	void SetVP(int width, int height); 

	void Release();

	void ClearColor(float r, float g, float b, float a);

	void StartDraw(Methold met);

	void Vertex3(float x, float y, float z);

	void Vertex3(RebVector RV);

	void Normal(RebVector RV);

	void MaterialSetup(RebMaterial rm);

	void TextCoord2(float s, float t);

	void BindTexture(UINT id);

	void Color(float r, float g, float b);

	void EndDraw();

	RebMatrix GetViewportMat();

	void SetViewportMat(RebMatrix svm);

	void ** GetViewportID();

	void GetViewportSize(unsigned int * w, unsigned int * h);

	ISkinManager * GetSkinManager();

	IVertexCacheManager * GetVertexCacheManager();

	IShaderSystem * GetShaderSystem();

	IGameEnv * GetEnv();

	void Swap(void * window);

	void Flush();

	void ChangeMatrixMode(MatrixMode mm);

	void Clear(bool color, bool depth);

	void ResetMatrix();

	void PushMatrix();

	void PopMatrix();

	void Translate(float x, float y, float z);

	void Rotate(float a, float x, float y, float z);

	void Scale(float x, float y, float z);

	void TransformMatrix(RebMatrix trans);

	void Render();

	~RebGL();
};




#endif