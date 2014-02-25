// I N C L U D E S /////////////////////////////////////////////////

#include "RebGL_skinmanager.h"   // class definition
             // return values and stuff




bool RebGLSkinManager::AddTexture(std::string filename, UINT * textid)
{
	
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
	rt.filename = filename;
	rt.id = *textid;
 
	//elv

	return true;
	
}

void * RebGLSkinManager::LoadTexture(std::string filename)
{
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(filename.c_str(),0);//Automatocally detects the format(from over 20 formats!)
	FIBITMAP* imagen = FreeImage_Load(formato, filename.c_str());
 
	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);
	return imagen;
}

RebColor RebGLSkinManager::GetPixelColor(void * data, unsigned int x, unsigned int y)
{
	FIBITMAP * img = (FIBITMAP*)data;
	RGBQUAD col;
	FreeImage_GetPixelColor(img, x, y, &col);
	RebColor ret;
	ret.fA = col.rgbReserved / 256;
	ret.fB = col.rgbBlue / 256;
	ret.fG = col.rgbGreen / 256;
	ret.fR = col.rgbRed / 256;
	return ret;
}

unsigned int RebGLSkinManager::GetHigh(void * data)
{
	FIBITMAP * img = (FIBITMAP*)data;
	unsigned int ret;
	ret = FreeImage_GetWidth(img);
	return ret;
}




RebGLSkinManager::RebGLSkinManager()
{

}

RebGLSkinManager::~RebGLSkinManager()
{

}