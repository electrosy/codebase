#pragma once

#include "Video.h"
#include "Thread.h"
#include "Timer.h"



#include <set>
#include <string>


class BlockBase
{



protected:

	int Run()
	{
		SDL_Delay(500);
		return 0;	
	}

public:

	BlockBase(Video*, std::string, int, int, SDL_Surface * BlockPiece);
	~BlockBase(void);

	void HandleKeyDepress();
	void SetPos(int x, int y);

	void Draw(Video* Video1, int orientation);
	void FallDown();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void CheckAction();

	bool DidCollide(); //flag if collided or not 
	void SetCollided(); // set collide = 1

	int GetPieceHeight() {return height;};
	int GetPieceWidth() {return width;};

	std::set<std::pair<int,int>> getBorder();

	private: 
	
	int x;
	int y;
	int height;
	int width;
	std::set<std::pair<int,int>> m_border; //All the x and y cordinates that make up the boundry 	
	bool bDidCollide;
	int m_WidthOfCurrentOrientation;

	std::string LastInput;
	std::string Orientation;
	std::string m_sBlockType;

	SDL_Surface* BlockPiece;

	enum eDirection { DOWN, UP, LEFT, RIGHT };

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

	

	void AddBorderLine(std::pair<int,int> start, std::pair<int,int> finish);

	eDirection FindDirectionToCount(int x1,int y1,int x2,int y2);

	void AddSingleBorder(std::pair<int, int> start, std::pair<int,int> finish, eDirection);

	void AddBorderDown(int y1, int y2, int x);

	void AddBorderUp(int y1, int y2, int x);

	void AddBorderLeft(int x1, int x2, int y);

	void AddBorderRight(int x1, int x2, int y);

	void DrawColisionBoundry(Video * Video1);

};
