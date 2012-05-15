#include "SDL.h"

#pragma once

class Timer
{
public:
	Timer(int TICK_TIME);
	~Timer(void);

	Uint32 TimeToMove(void);
	void Reset(void);
	
private:
	const Uint32 TICK_INTERVAL;
	Uint32 now;
	Uint32 next_time;
};
