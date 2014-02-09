#include "StdAfx.h"
#include "Timer.h"


Timer::Timer(int TICK_TIME) : TICK_INTERVAL(TICK_TIME), now(0), next_time(0)
{
	//at 10 block starts to fall on its own
}
Timer::~Timer(void)
{

}

void Timer::Reset(void)
{
	this->next_time = 0;
}

Uint32 Timer::TimeToMove(void) 
{
    Uint32 now;
	bool time_up = 0;

	now = SDL_GetTicks();
	if (next_time <= now)
	{
		next_time = now+TICK_INTERVAL;
		time_up = 1;
	}

    return time_up;
}


