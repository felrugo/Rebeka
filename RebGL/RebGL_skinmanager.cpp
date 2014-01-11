// I N C L U D E S /////////////////////////////////////////////////

#include "RebGL_skinmanager.h"   // class definition
             // return values and stuff


bool RebGLSkinManager::sforvecid(UINT id, UINT * fid)
{
	for (unsigned int i = 0; i < vTextures.size(); i++)
	{
		if (vTextures[i].id == id)
		{
			if (fid != 0)
			{
			*fid = i;
			}
			return 1;
		}
	}
	return 0;
}

 bool RebGLSkinManager::textureisex(std::string filename)
 {
	 for (unsigned int i = 0; i < vTextures.size(); i++)
	 {
		 if (vTextures[i].chName == filename)
		 {
			 return true;
		 }
	 }
	 return false;
 }

 bool RebGLSkinManager::matidex(UINT * matid)
 {
	 for (unsigned int i = 0; i < vMaterials.size(); i++)
	 {
		 if(vMaterials[i].id == *matid)
		 {
			 return true;
		 }
	 }
	 return false;
 }

 bool RebGLSkinManager::skiidex(UINT * skiid)
 {
	 for (unsigned int i = 0; i < vSkins.size(); i++)
	 {
		 if(vSkins[i].id == *skiid)
		 {
			 return true;
		 }
	 }
	 return false;
 }

bool RebGLSkinManager::AddTexture(std::string filename, UINT * textid)
{
	if(sforvecid(*textid, 0))
	{
		return false;
	}
	if (textureisex(filename))
	{
		return false;
	}
	// elvalasz
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(filename.c_str(),0);//Automatocally detects the format(from over 20 formats!)
	FIBITMAP* imagen = FreeImage_Load(formato, filename.c_str());
 
	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);
 
	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);
	
 
	GLubyte* textura = new GLubyte[4*w*h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);
	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
 
	for(int j= 0; j<w*h; j++){
		textura[j*4+0]= pixeles[j*4+2];
		textura[j*4+1]= pixeles[j*4+1];
		textura[j*4+2]= pixeles[j*4+0];
		textura[j*4+3]= pixeles[j*4+3];
		//cout<<j<<": "<<textura[j*4+0]<<"**"<<textura[j*4+1]<<"**"<<textura[j*4+2]<<"**"<<textura[j*4+3]<<endl;
	}
 
	//Now generate the OpenGL texture object 
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, textid);
	glBindTexture(GL_TEXTURE_2D, *textid);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, w, h, 0, GL_RGBA,GL_UNSIGNED_BYTE,(GLvoid*)textura );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 
	GLenum huboError = glGetError();
	if(huboError){
 
		return false;
	}
	RebTexture rt;
	rt.chName = filename;
	rt.id = *textid;
	vTextures.push_back(rt);
 
	//elv

	return true;
	
}


bool RebGLSkinManager::AddMaterial(RebColor *ambient, RebColor *diffuse, RebColor *specular, RebColor *emissive, float * power, UINT * matid)
{
	if(matidex(matid) == false)
	{
	RebMaterial rm;
	rm.cAmbient = *ambient;
	rm.cDiffuse = *diffuse;
	rm.cEmissive = *emissive;
	rm.cSpecular = *specular;
	rm.fPower = *power;
	rm.id = * matid;
	vMaterials.push_back(rm);
	return true;
	}
	return false;
}


bool RebGLSkinManager::CreateSkin(UINT * matid, UINT * texid[8], UINT * skiid, bool alpha)
{
	if(skiidex(skiid) == false)
	{
	RebSkin rs;
	rs.bAlpha = alpha;
	rs.id = *skiid;
	rs.nMaterial = *matid;
	for (int i = 0; i < 8; i++)
	{
	rs.nTexture[i] = *texid[i];
	}
	vSkins.push_back(rs);
	return true;
	}
	return false;
}



RebGLSkinManager::RebGLSkinManager()
{

}

RebGLSkinManager::~RebGLSkinManager()
{

}