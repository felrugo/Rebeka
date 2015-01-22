#include "RebIH.h"

void RebIH::LoadFile(std::string file)
{
	 formato = FreeImage_GetFileType(file.c_str(), 0);//Automatocally detects the format(from over 20 formats!)
	imagen = FreeImage_Load(formato, file.c_str());

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

}