#pragma once

#include "Video.h"

class CFloor
{


private: 
	
	int x;
	int y;
	int height;
	int width;

	SDL_Surface* BlockPiece;

	
public:
		CFloor(Video* Video1);
		~CFloor(void);
		void CFloor::Draw(Video* Video1);
};
