#include "RebVL.h"







RebVL::RebVL()
{
	first = 0;
	curbuff = &first;
}

void RebVL::push_back(RebVector pb)
{
	RebVL_e * n = new RebVL_e;
        n->value = pb;
        n->next = first;
		first = n;
}

RebVector RebVL::at(unsigned int id)
{
	RebVL_e * pr = first;
	for(unsigned int i = 0; i < id; i++)
	{
		pr = pr->next;
	}
	return pr->value;
}


RebVector RebVL::operator[](unsigned int id)
{
	RebVL_e * pr = first;
	for(unsigned int i = 0; i < id; i++)
	{
		pr = pr->next;
	}
	return pr->value;
}



RebVector * RebVL::buffer()
{
	RebVector * ret = &(*curbuff)->value;
	curbuff = &(*curbuff)->next;
	if(curbuff == 0)
		curbuff = &first;
	return ret;
}

unsigned int RebVL::size()
{
	unsigned int ret = 0;
	RebVL_e * pr = first;
	while(pr != 0)
	{
		pr = pr->next;
		ret++;
	}
	return ret;
}

void RebVL::clear()
{
	while(first != NULL) {
		RebVL_e * n = first->next;
            delete first;
            first = n;
}
}

RebVL::~RebVL()
{
	clear();
}