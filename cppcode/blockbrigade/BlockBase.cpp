#include "StdAfx.h"
#include "BlockBase.h"

BlockBase::BlockBase(Video* Video1, std::string s_BlockType, int x, int y, SDL_Surface* BlockPiecein)
{
	BlockPiece = BlockPiecein;
	
	m_sBlockType = s_BlockType;

	bDidCollide = 0;

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

	if(x<50000 & x>-50000)
	{
		this->y = y;
	}
	else 
	{
		this->y = 0;
	}
	
	m_WidthOfCurrentOrientation = 0;
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

	//Clear the boundry before re drawing.
	m_border.clear();

	if(m_sBlockType == "LBlock")
	{
		if(orientation == 0) //"L shape" 
		{
		//build an LShape with the 4 quote blocks
			Video1->ApplySurface(x, y, BlockPiece);
			Video1->ApplySurface(x, y+height, BlockPiece);
			Video1->ApplySurface(x, y+height+height, BlockPiece);
			Video1->ApplySurface(x+width, y+height+height, BlockPiece);

		    //six lines to add to the boundry 
			// all the -1's below are to prevent an off by one because the grid starts at (0,0) and the block is exactly 60 pixels long and 40 pixels wide.
			//First line from top left to bottom left
			AddBorderLine(std::make_pair(x,y), std::make_pair(x,y+(3*height)-1)); //three blocks high in this orintation.

			//Next Line from bottom left to bottom right
			AddBorderLine(std::make_pair(x,y+(3*height)-1), std::make_pair(x+(2*width)-1,y+(3*height)-1)); //2 blocks wide in this orintation.

			//next line from bottom right to top right
			AddBorderLine(std::make_pair(x+(2*width)-1,y+(3*height)-1), std::make_pair(x+(2*width)-1,y+(2*height)));

			//add border line from top right of the bottom part of the L. (going left)
			AddBorderLine(std::make_pair(x+(2*width)-1,y+(2*height)) , std::make_pair(x+width-1, y+(2*height)-1 ) );

			//add border line from inside elbow to top right.
			AddBorderLine(std::make_pair(x+(width)-1,y+(2*height)-1),std::make_pair(x+(width)-1,y));

		   //add border line from top right to the start position
			AddBorderLine(std::make_pair(x+(width)-1,y),std::make_pair(x,y));

			
		}
		if(orientation == 1)
		{
			Video1->ApplySurface(x, y, BlockPiece);
			Video1->ApplySurface(x, y+height, BlockPiece);
			Video1->ApplySurface(x+width, y, BlockPiece);
			Video1->ApplySurface(x+width, y, BlockPiece);
			Video1->ApplySurface(x+width+width, y, BlockPiece);

			AddBorderLine(std::make_pair(x,y), std::make_pair(x,y+(2*height)-1));

			
			AddBorderLine(std::make_pair(x,y+(2*height)-1), std::make_pair(x+width-1,y+(2*height)-1)); 

			
			AddBorderLine(std::make_pair(x+width-1,y+(2*height)-1), std::make_pair(x+width-1,y+height-1));

			
			AddBorderLine(std::make_pair(x+width-1,y+height-1) , std::make_pair(x+(3*width)-1, y+height-1));

			
			AddBorderLine(std::make_pair(x+(3*width)-1, y+height-1),std::make_pair(x+(3*width)-1,y));

		   
			AddBorderLine(std::make_pair(x+(3*width)-1,y),std::make_pair(x,y));

		}
		if(orientation == 2)
		{
			Video1->ApplySurface(x, y, BlockPiece);
			Video1->ApplySurface(x+width, y, BlockPiece);
			Video1->ApplySurface(x+width, y+height, BlockPiece);
			Video1->ApplySurface(x+width, y+height+height, BlockPiece);

			AddBorderLine(std::make_pair(x,y), std::make_pair(x,y+height-1));

			
			AddBorderLine(std::make_pair(x,y+height-1), std::make_pair(x+width-1,y+height-1));

			
			AddBorderLine(std::make_pair(x+width,y+height-1), std::make_pair(x+width,y+(3*height)-1));

			
			AddBorderLine(std::make_pair(x+width,y+(3*height)-1), std::make_pair(x+(2*width)-1,y+(3*height)-1));

			
			AddBorderLine(std::make_pair(x+(2*width)-1,y+(3*height)-1),std::make_pair(x+(2*width)-1,y));


			AddBorderLine(std::make_pair(x+(2*width)-1,y),std::make_pair(x,y));

		}
		if(orientation == 3)
		{
			Video1->ApplySurface(x, y+height, BlockPiece);
			Video1->ApplySurface(x+width-1, y+height, BlockPiece);
			Video1->ApplySurface(x+width+width-1, y+height, BlockPiece);
			Video1->ApplySurface(x+width+width-1, y, BlockPiece);
		}
	}
	else if (m_sBlockType == "SqBlock")
	{
		if(orientation == 0)
		{
			Video1->ApplySurface(x, y, BlockPiece);
			Video1->ApplySurface(x+width, y, BlockPiece);
			Video1->ApplySurface(x, y+height, BlockPiece);
			Video1->ApplySurface(x+width, y+height, BlockPiece);

			AddBorderLine(std::make_pair(x,y), std::make_pair(x,y+(height*2)-1));
			AddBorderLine(std::make_pair(x,y+(height*2)-1), std::make_pair(x+(2*height)-1,y+(height*2)-1));
			AddBorderLine(std::make_pair(x+(2*width)-1,y+(height*2)-1), std::make_pair(x+(2*width)-1,y));
			AddBorderLine(std::make_pair(x+(2*width)-1,y), std::make_pair(x,y));
		}
	}
	else if (m_sBlockType == "FloorBottom")
	{
		int length = 20;
		int nBlockPieceHeight = this->BlockPiece->h;
		int nBlockPieceWidth = this->BlockPiece->w;

		if(orientation==0) //floor
		{
			for(int i = 0; i < length; i++)
			{
				Video1->ApplySurface(x+(i * nBlockPieceWidth), this->y, BlockPiece);
				
			}

			AddBorderLine(std::make_pair(x,y),std::make_pair(x,y+nBlockPieceHeight));
			AddBorderLine(std::make_pair(x,y+nBlockPieceHeight),std::make_pair(x+(length*nBlockPieceWidth),y+nBlockPieceHeight));
			AddBorderLine(std::make_pair(x+(nBlockPieceWidth*length),y+nBlockPieceHeight),std::make_pair(x+(nBlockPieceWidth*length),y));
			AddBorderLine(std::make_pair(x+(nBlockPieceWidth*length),y),std::make_pair(x,y));

			//Left and right borders
			AddBorderLine(std::make_pair(0,0), std::make_pair(0,500));
			AddBorderLine(std::make_pair(401,0), std::make_pair(401,500));
		}
		else if(orientation==1) //left wall
		{
			for(int i = 0; i < length; i++)
			{
				Video1->ApplySurface(x, y+(i*this->BlockPiece->h), BlockPiece);
			}
		}

	}

	if(!m_border.empty())
	{
		DrawColisionBoundry(Video1);
	}
}

void BlockBase::DrawColisionBoundry(Video * Video1)
{

	Uint32 ColorGrey = SDL_MapRGB(Video1->GetScreen()->format, 0x55, 0x55, 0x55);

	std::set<std::pair<int,int>>::iterator it;

	for(it=m_border.begin(); it != m_border.end();it++)
	{
		Video1->PrintPixel(it->first,it->second,ColorGrey);
	}
}

void BlockBase::AddSingleBorder(std::pair<int, int> start, std::pair<int,int> finish, eDirection direction)
{
	switch(direction)
	{
		case  0 : //down
			AddBorderDown(start.second, finish.second, start.first);
		break;
		
		case 1 : //up
			AddBorderUp(start.second, finish.second, start.first);
		break;
		          
		case  2 : //left
			AddBorderLeft(start.first, finish.first, start.second);
		break;

		case 3 : //right
			
			AddBorderRight(start.first, finish.first, start.second);
		break;
	}
}

void BlockBase::AddBorderDown(int y1, int y2,int x)
{
	//Add all the points from top to bottom on the same x axis
	for(int i = y1; i <= y2; i++)
	{
		m_border.insert(std::make_pair(x,i));
	}
}
void BlockBase::AddBorderUp(int y1, int y2, int x)
{
	for(int i = y1; i >= y2; i--)
	{
		m_border.insert(std::make_pair(x,i));
	}
}
void BlockBase::AddBorderLeft(int x1, int x2, int y)
{
	for(int i = x1; i >= x2; i--)
	{
		m_border.insert(std::make_pair(i,y));
	}
}
void BlockBase::AddBorderRight(int x1, int x2, int y)
{
	for(int i = x1; i <= x2; i++)
	{
		m_border.insert(std::make_pair(i,y));
	}
}
std::set<std::pair<int,int>> BlockBase::getBorder()
{
		return m_border;
}
void BlockBase::AddBorderLine(std::pair<int,int> start, std::pair<int,int> finish)
{
	eDirection direction;

	direction = FindDirectionToCount(start.first, start.second, finish.first, finish.second);

	AddSingleBorder(start, finish, direction);
}

BlockBase::eDirection BlockBase::FindDirectionToCount(int x1,int y1,int x2,int y2)
{
	eDirection direction;

	//which way do we count, up, down, left or right.

	if(x1 == x2) //then its up or down
	{
		if(y1 < y2) //then its down
		{
			direction = DOWN;
		}
		else
		{
			direction = UP;
		}

	}
	else //then its left or right
	{
		if(x1 < x2) //then right
		{
			direction = RIGHT;
		}
		else
		{
			direction = LEFT;
		}
	}

	return direction;
}

void BlockBase::FallDown() // TODO replaces occurences of this with MoveDown as they are the same function.
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

bool BlockBase::DidCollide()
{
	return bDidCollide;
}

void BlockBase::SetCollided()
{
	bDidCollide = 1;
}