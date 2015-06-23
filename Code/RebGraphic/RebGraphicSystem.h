
#ifndef REBGRAPHICSYSTEM_H 
#define REBGRAPHICSYSTEM_H 
 

 
#include "IRenderDevice.h"

 
 

 
 

class RebGraphicSystem { 
   public: 

	   RebGraphicSystem();

     void CreateDevice();

	 void ReleaseDevice();

	 IRenderDevice * GetDevice();

	 HINSTANCE GetModule();

	 ~RebGraphicSystem();

private:
      IRenderDevice  *rd;
	  HMODULE mDLL;
	  bool runing;
   }; // class 
 

 
#endif 