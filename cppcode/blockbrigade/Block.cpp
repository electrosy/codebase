#include "StdAfx.h"
#include "Block.h"

Block::Block(Video* Video1)
{
	BlockPiece = Video1->NewLoadImage("./resources/BlockPiece.bmp");

	height = BlockPiece->h;
	width = BlockPiece->w;

	this->x = 0;
	this->y = 0;
}

Block::~Block(void)
{

}

void Block::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Block::Draw(Video* Video1, int orientation)
{

	if(orientation == 0)
	{
		Video1->ApplySurface(x, y, BlockPiece);
		Video1->ApplySurface(x, y+height, BlockPiece);
		Video1->ApplySurface(x, y+height+height, BlockPiece);
		Video1->ApplySurface(x+width, y+height+height, BlockPiece);
	}
	if(orientation == 1)
	{
		Video1->ApplySurface(x, y, BlockPiece);
		Video1->ApplySurface(x, y+height, BlockPiece);
		Video1->ApplySurface(x+width, y, BlockPiece);
		Video1->ApplySurface(x+width, y, BlockPiece);
		Video1->ApplySurface(x+width+width, y, BlockPiece);
	}
	if(orientation == 2)
	{
		Video1->ApplySurface(x, y, BlockPiece);
		Video1->ApplySurface(x+width, y, BlockPiece);
		Video1->ApplySurface(x+width, y+height, BlockPiece);
		Video1->ApplySurface(x+width, y+height+height, BlockPiece);
	}
	if(orientation == 3)
	{
		Video1->ApplySurface(x, y+height, BlockPiece);
		Video1->ApplySurface(x+width, y+height, BlockPiece);
		Video1->ApplySurface(x+width+width, y+height, BlockPiece);
		Video1->ApplySurface(x+width+width, y, BlockPiece);
	}
}

void Block::FallDown()
{

	this->y = this->y + this->height;
}

void Block::MoveDown()
{
	this->y = this->y + this->height;
}

void Block::MoveLeft()
{
	this->x = this->x - this->width;
}
void Block::MoveRight()
{
	this->x = this->x + this->width;
}