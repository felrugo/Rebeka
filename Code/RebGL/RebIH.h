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
	virtual unsigned int GetWidth() = 0;
	virtual unsigned int GetHight() = 0;
	virtual RebVector GetPixelColor(unsigned int x, unsigned int y) = 0;
	virtual void LoadIntoRenderer() = 0;
};






#endif