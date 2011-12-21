#pragma once

#include "Video.h"
#include "Thread.h"
#include "Timer.h"


class BlockBase
{

private: 
	
	int x;
	int y;
	int height;
	int width;

	Uint32 LeftRightTick(std::string Behavior)
	{
		printf("LeftRightTick|");
		const Uint32 TICK_INTERVAL = 125;
		static Uint32 next_time = 0;
		Uint32 now;
	    
		now = SDL_GetTicks();

		if (Behavior == "Clear")
		{
			next_time = 0;
			return(0);
		}

		if (Behavior == "Reset")
		{
			next_time = 1;
			return(1);
		}

		if (next_time <= now) {
			next_time = now+TICK_INTERVAL;
			return(0);
		}
	    
		return(next_time-now);
	}

	Uint32 DownTick(std::string Behavior)
	{
		const Uint32 TICK_INTERVAL = 125;
		static Uint32 next_time = 0;
		Uint32 now;
	    
		now = SDL_GetTicks();
		
		if (Behavior == "Reset")
		{
			next_time = 1;
			return(1);
		}

		if (next_time <= now) {
			next_time = now+TICK_INTERVAL;
			return(0);
		}
	    
		return(next_time-now);
	}

	Uint32 FallTick(std::string Behavior)
	{
		const Uint32 TICK_INTERVAL = 1000;
		static Uint32 next_time = 0;
		Uint32 now;
	    
		now = SDL_GetTicks();
		
		if (Behavior == "Clear")
		{
			return(1);
		}

		if (Behavior == "Reset")
		{
			next_time = 0;
			return(1);
		}

		if (next_time <= now) {
			next_time = now+TICK_INTERVAL;
			return(0);
		}
	    
		return(next_time-now);
	}

	std::string LastInput;
	std::string Orientation;
	std::string m_sBlockType;

	SDL_Surface* BlockPiece;

protected:

	int Run()
	{
		SDL_Delay(500);
		return 0;	
	}

public:

	void HandleKeyDepress();
	void SetPos(int x, int y);

	void Draw(Video* Video1, int orientation);
	void CheckIfMoveWillCollide(); //Check if this block will colide with any other block when making a move
	void FallDown();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void CheckAction();

	BlockBase(Video*, std::string, int, int);
	~BlockBase(void);

};
