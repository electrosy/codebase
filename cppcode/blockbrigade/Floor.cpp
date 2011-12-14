#include "StdAfx.h"
#include "Floor.h"


CFloor::CFloor(Video* Video1)
{
	BlockPiece = Video1->NewLoadImage("./resources/BlockPiece.bmp");

	this->x=0;
	this->y=0;
	this->height=1;
	this->width=5;
}



CFloor::~CFloor(void)
{
}

void CFloor::Draw(Video* Video1)
{
		Video1->ApplySurface(x, y, BlockPiece);
		Video1->ApplySurface(x, y+height, BlockPiece);
		Video1->ApplySurface(x, y+height+height, BlockPiece);
		Video1->ApplySurface(x+width, y+height+height, BlockPiece);
}
