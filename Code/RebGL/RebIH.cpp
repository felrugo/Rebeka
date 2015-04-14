#include "RebIH.h"

void RebIH::LoadFile(std::string file)
{
	 formato = FreeImage_GetFileType(file.c_str(), 0);//Automatocally detects the format(from over 20 formats!)
	imagen = FreeImage_Load(formato, file.c_str());

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

}


unsigned int RebIH::GetWidth()
{
	return FreeImage_GetWidth(imagen);
}


unsigned int RebIH::GetHeight()
{
	return FreeImage_GetHeight(imagen);
}

RebVector RebIH::GetPixelColor(unsigned int x, unsigned int y)
{
	RGBQUAD val;
	FreeImage_GetPixelColor(imagen, x, y, &val);
	RebVector ret(val.rgbRed, val.rgbGreen, val.rgbBlue);
	return ret;
}