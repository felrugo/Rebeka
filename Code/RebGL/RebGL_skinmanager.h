
#ifndef SKINMAN_H
#define SKINMAN_H


#include "../RebGraphic/IRenderDevice.h"
#include <GL\glew.h>
#include <gl\GL.h>
#include <vector>
#include <string>
#include "FreeImage.h"
#include "RebIH.h"

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