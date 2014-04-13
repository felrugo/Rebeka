#ifndef REBVL
#define REBVL

#include "..\Reb3D\Reb3d.h"

struct RebVL_e
{
	RebVector value;
	RebVL_e * next;
};

class RebVL
{

	RebVL_e * first;

	RebVL_e ** curbuff;

public:
	RebVL();
	void push_back(RebVector push);
	RebVector at(unsigned int id);


	RebVector operator[](unsigned int id);

	void clear();
	RebVector * buffer();
	unsigned int size();
	~RebVL();

};


#endif