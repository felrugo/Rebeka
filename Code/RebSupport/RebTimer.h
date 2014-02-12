#ifndef REBTIMER_H
#define REBTIMER_H

#include <ctime>
#include <climits>

class RebTimer
{
time_t t;
clock_t start;
public:
	RebTimer();

	float GetCurrent();

	void Start();
};




#endif