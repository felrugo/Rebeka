#include "RebTimer.h"

RebTimer::RebTimer()
{
	t = 0;
	start = 0;
}

void RebTimer::Start()
{
	start = clock();
}

float RebTimer::GetCurrent()
{
	clock_t dif = clock() - start;
	if(dif < 0)
	{
		dif = LONG_MAX - start + clock();
	}
	return dif / CLOCKS_PER_SEC;
}