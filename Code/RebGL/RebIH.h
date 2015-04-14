#ifndef REBIH
#define REBIH

#include "../RebRenderer/IRenderDevice.h"
#include "FreeImage.h"

class RebIH : public IImageHandler
{
	FREE_IMAGE_FORMAT formato;
	FIBITMAP* imagen;
public:
	void LoadFile(std::string file);
	unsigned int GetWidth();
	unsigned int GetHeight();
	RebVector GetPixelColor(unsigned int x, unsigned int y);
	void LoadIntoRenderer() {};
};






#endif