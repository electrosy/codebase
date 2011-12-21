#include "StdAfx.h"
#include "Floor.h"


CFloor::CFloor(Video* Video1)
{
	
	LeftPiece = Video1->NewLoadImage("./resources/FloorPieceLeft.bmp");

	//for positioning.
	floorx =0;
	floory =575;
	rwallx =0;
	rwally =0;
	lwallx =0;
	lwally =0;
}

CFloor::~CFloor(void)
{
}

void CFloor::Draw(Video* Video1, int orientation)
{
		int length = 25;

		
}


