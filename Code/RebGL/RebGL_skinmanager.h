
#ifndef ZFXD3D_SKINMAN_H
#define ZFXD3D_SKINMAN_H


#include "../RebRenderer/IRenderDevice.h"
#include "..\RebRenderer\Reb.h"
#include <gl\GL.h>
#include <vector>
#include <string>
#include "FreeImage.h"

#define MAX_ID 65535

class RebGLSkinManager : public ISkinManager {
	 protected:
		 std::vector<RebTexture> vTextures;
		 std::vector<RebMaterial> vMaterials;
		 std::vector<RebSkin> vSkins;

		 bool sforvecid(UINT id, UINT * fid = 0);
		 bool textureisex(std::string filename);
		 bool matidex(UINT * matid);
		 bool skiidex(UINT * skiid);

   public:
	   RebGLSkinManager();
      ~RebGLSkinManager(void);

	  bool AddTexture(std::string filename, UINT * textid);
	  bool AddMaterial(RebColor *ambient, RebColor *diffuse, RebColor *specular, RebColor *emissive, float * power, UINT * matid);
	  bool CreateSkin(UINT * matid, UINT * texid[8], UINT * skiid, bool alpha);

     

};

#endif