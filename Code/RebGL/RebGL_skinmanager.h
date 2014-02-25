
#ifndef SKINMAN_H
#define SKINMAN_H


#include "../RebRenderer/IRenderDevice.h"
#include "..\RebRenderer\Reb.h"
#include <gl\GL.h>
#include <vector>
#include <string>
#include "FreeImage.h"

#define MAX_ID 65535

class RebGLSkinManager : public ISkinManager {
	 protected:

   public:
	   RebGLSkinManager();
      ~RebGLSkinManager(void);

	  bool AddTexture(std::string filename, UINT * textid);

	  void* LoadTexture(std::string filename);

	  unsigned int GetHigh(void * data);

	  RebColor GetPixelColor(void * data, unsigned int x, unsigned int y);

};

#endif