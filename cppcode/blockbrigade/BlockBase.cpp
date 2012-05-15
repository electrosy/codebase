#include "StdAfx.h"
#include "BlockBase.h"

BlockBase::BlockBase(Video* Video1, std::string s_BlockType, int x, int y)
{
	
	m_sBlockType = s_BlockType;


	if (m_sBlockType == "LBlock")
	{
		BlockPiece = Video1->NewLoadImage("./resources/BlockPiece.bmp");
	}
	else if (m_sBlockType == "FloorBottom")
	{
		BlockPiece = Video1->NewLoadImage("./resources/FloorPieceBottom.bmp");
	}

	//Grab the height and width from the images that were loaded.
	height = BlockPiece->h;
	width = BlockPiece->w;

	if(x<50000&x>-50000)
	{
		this->x = x;
	}
	else 
	{
		this->x = 0;
	}

	if(x<50000&x>-50000)
	{
		this->y = y;
	}
	else 
	{
		this->y = 0;
	}
	
}

BlockBase::~BlockBase(void)
{

}

void BlockBase::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;
}
void BlockBase::Draw(Video* Video1, int orientation)
{
	if(m_sBlockType == "LBlock")
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
	else if (m_sBlockType == "FloorBottom")
	{
		int length = 20;

		if(orientation==0) //floor
		{
			for(int i = 0; i < length; i++)
			{
				Video1->ApplySurface(x+(i*this->BlockPiece->w), this->y, BlockPiece);
			}
		}
		else if(orientation==1) //left wall
		{
			for(int i = 0; i < length; i++)
			{
				Video1->ApplySurface(x, y+(i*this->BlockPiece->h), BlockPiece);
			}
		}

	}
}

void BlockBase::FallDown()
{
	this->y = this->y + this->height;
}

void BlockBase::MoveDown()
{
	this->y = this->y + this->height;
}

void BlockBase::MoveLeft()
{
	this->x = this->x - this->width;
}
void BlockBase::MoveRight()
{
	this->x = this->x + this->width;
}

void BlockBase::CheckIfMoveWillCollide() //pass this a datastructure of all blocks on the screen?
{
	//Will moving colide with another block.
}