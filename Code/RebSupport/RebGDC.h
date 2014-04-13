#ifndef REBGDC_H
#define REBGDC_H

class IWindowManager;
class IRenderDevice;
class RebFileSystem;
class IMEH;


class RebGDC
{
public:
	IWindowManager * winm;
	IRenderDevice * rd;
	IMEH * meh;
	void * window;
	bool * grp;
	RebFileSystem * rfs;
	RebGDC()
	{
		winm = 0;
		rd = 0;
		meh = 0;
		window = 0;
		rfs = 0;
		grp = 0;
	}
};


#endif