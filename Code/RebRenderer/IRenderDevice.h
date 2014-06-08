// File: RebRenderDevice.h 
#ifndef RENDERINTERFACE_H 
#define RENDERINTERFACE_H 
 
 
// I N C L U D E S ///////////////////////////////////////////////// 
 
#include <windows.h> 
#include <stdio.h>
#include "Reb.h"
#include "..\RebWindowSystem\IWindowManager.h"
#include "..\RebSupport\RebGDC.h"
 
// D E F I N E S /////////////////////////////////////////////////// 
 
#define MAX_3DHWND 8 
 
 
 
// S T R U C T S /////////////////////////////////////////////////// 


class ILightSystem
{
public:
	virtual ~ILightSystem() {}
};


class IRenderDevice;

class IRenderModel;

class IShaderHandler
{
public:
};

//class IShaderSystem
//{
//	public:
//
//	virtual unsigned int GetProgramid(std::string name) = 0;
//
//	virtual unsigned int GetShaderid(std::string source) = 0;
//
//	virtual void ActivateProgram(unsigned int programid) = 0;
//
//	virtual void CreateProgram(std::string name,unsigned int * programid) = 0;
//
//	virtual void AddShader(std::string shaderfile, unsigned int programid, unsigned int * shaderid) = 0;
//
//	virtual void DeleteShader(unsigned int shaderid) = 0;
//
//	virtual void Link(unsigned int handle) = 0;
//
//	virtual void DeleteProgram(unsigned int programid) = 0;
//
//	virtual ~IShaderSystem() {};
//};


class IImageHandler
{
public:

};

class IModelHandler
{
public:
virtual bool LoadModel(std::string file) = 0;
virtual RebVertexCache GetRVC() = 0;
};

class ISkinManager {
public:

	virtual ~ISkinManager() {};
   
	virtual bool AddTexture(std::string filename, UINT * textid) = 0;

	virtual void * LoadTexture(std::string filename) = 0;

	virtual RebColor GetPixelColor(void * data, unsigned int x, unsigned int y) = 0;

	virtual unsigned int GetHigh(void * data) = 0;
      
   };

class IVertexCacheManager
{
public:
	virtual void CreateCache(std::string name, std::vector<RebVertexBuffer> RVB) = 0;

	virtual void DeleteCache(RebVertexCache * rvc) = 0;

	virtual RebVertexCache * GetVertexCache(std::string cname) = 0;

	virtual RebVertexCache * GetVCByFile(std::string filename) = 0; /*if VC doesn't exists return 0 */

	virtual void CreateCacheFromFile(std::string cname, std::string filename) = 0;

	virtual void Release() = 0;

	virtual std::vector<RebVertexCache*> * GetRVCs() = 0;

	virtual ~IVertexCacheManager() {}
};

class IGameEnv
{
public:
	virtual RebTerrain * CreateTerrain() = 0;
	virtual std::vector<RebTerrain*> * GetTerrains() = 0;
	virtual void DeleteTerrain(RebTerrain * del) = 0;
};

class IRenderDevice
{	
	public:

	virtual void Init(RebGDC * gd) = 0;

	virtual void SetVP(int width, int height) = 0; 

	virtual void Release() = 0;

	virtual void ClearColor(float r, float g, float b, float a) = 0;

	virtual void StartDraw(Methold met) = 0;

	virtual void EndDraw() = 0;

	virtual ISkinManager * GetSkinManager() = 0;

	virtual IVertexCacheManager * GetVertexCacheManager()= 0;

	virtual IGameEnv * GetEnv() = 0;

	virtual RebMatrix GetViewportMat() = 0;

	virtual void SetViewportMat(RebMatrix svm) = 0;

	virtual void ** GetViewportID() = 0;

	virtual void GetViewportSize(unsigned int * w, unsigned int * h) = 0;

	virtual void Vertex3(float x, float y, float z) = 0;

	virtual void Vertex3(RebVector RV)= 0;

	virtual void TextCoord2(float s, float t) = 0;

	virtual void BindTexture(UINT id) = 0;

	virtual void Color(float r, float g, float b) = 0;

	virtual void Normal(RebVector RV) = 0;

	virtual void MaterialSetup(RebMaterial rm) = 0;

	virtual void ChangeMatrixMode(MatrixMode mm) = 0;

	virtual void Clear(bool color, bool depth) = 0;

	virtual void ResetMatrix() = 0;

	virtual void PushMatrix() = 0;

	virtual void PopMatrix() = 0;

	virtual void Translate(float x, float y, float z) = 0;

	virtual void Rotate(float a, float x, float y, float z) = 0;

	virtual void Scale(float x, float y, float z) = 0;

	virtual void TransformMatrix(RebMatrix trans) = 0;

	virtual void Swap(void * window) = 0;

	virtual void Flush() = 0;

	virtual void Render() = 0;

	virtual ~IRenderDevice() {}
};



class IRenderModel
{
public:
	virtual void Render() = 0;
	virtual ~IRenderModel() {}
};

 
typedef class IRenderDevice *LPRebRENDERDEVICE; 
/*----------------------------------------------------------------*/ 
 extern "C" {
   void CreateRenderDevice(IRenderDevice **LPRenderDevice);
   typedef void (*CREATERENDERDEVICE)(IRenderDevice **LPRenderDevice);
   
   void ReleaseRenderDevice(IRenderDevice **LPRenderDevice);
   typedef void (*RELEASERENDERDEVICE)(IRenderDevice **LPRenderDevice);
 }

#endif