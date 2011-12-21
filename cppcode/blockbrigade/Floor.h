#pragma once

#include "Video.h"

class CFloor
{

private: 
	
	int floorx;
	int floory;
	int rwallx;
	int rwally;
	int lwallx;
	int lwally;
	int iHeight;
	int iWidth;

	SDL_Surface* BottomPiece;
	SDL_Surface* LeftPiece;

	
public:
		CFloor(Video* Video1);
		~CFloor(void);
		void CFloor::Draw(Video* Video1, int orientation);
};

