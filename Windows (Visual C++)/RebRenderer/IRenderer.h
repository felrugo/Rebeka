// File: ZFXRenderer.h 
#ifndef ZFXRENDERDEVICE_H 
#define ZFXRENDERDEVICE_H 
 
 
// I N C L U D E S ///////////////////////////////////////////////// 
 
#include "IRenderDevice.h"

 
 
// D E F I N E S /////////////////////////////////////////////////// 
 
 
// S T R U C T S /////////////////////////////////////////////////// 
 
/** 
 * Just used to create, get a pointer to, and release a render device, 
 * wether this is d3d or opengl or whatelse depends on dll which is  
 * selected in the CreateDevice() call. 
 */ 
class Renderer { 
   public: 

	   Renderer();

     void CreateDevice();

	 void ReleaseDevice();

	 IRenderDevice * GetDevice();

	 HINSTANCE GetModule();

	 ~Renderer();

private:
      IRenderDevice  *rd;
	  HMODULE mDLL;
	  bool runing;
   }; // class 
 

 
#endif 