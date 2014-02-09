#pragma once
//This program was written by Steven Philley
//Purpose: This program is my first SDL program and will become a basic type 
//game. 
//
//!This program uses the lazy font TTF from http://lazyfoo.net

/// TODO: Add Timer. Use a lock with the Screen.
/// TODO: Use Threads: Make the screen refresh a thread? Make the input a thread?
/// TODO: Put the events into a Queue to be worked by a seperate thread.
#include <string>
#include <stdio.h>
#include <map>
#include <vector>

#include "SDL.h"

#include "video.h" //allows us to create a video object.
#include "screenfont.h" //a ttf font
#include "BlockBase.h"
#include "Timer.h"

//#include "button.h"
SDL_Event event; //SDL event

Video theVideo;
Video* Video1 = &theVideo;

Uint32 g_black = SDL_MapRGB(Video1->GetScreen()->format, 0x00, 0x00, 0x00);//Defines a color
Uint32 g_yellow = SDL_MapRGB(Video1->GetScreen()->format, 0x55, 0x55, 0x55);

ScreenFont ScreenFont1;

SDL_Surface* sfcBlockPiece = Video1->NewLoadImage("./resources/BlockPiece.bmp");



std::vector<BlockBase> vecBlocksInPlay;

BlockBase Block1(Video1, "LBlock", 1, 0, sfcBlockPiece);
BlockBase Block2(Video1, "LBlock", 1, 400, sfcBlockPiece);
BlockBase Block3(Video1, "SqBlock", 41, 200, sfcBlockPiece);
BlockBase Floor(Video1, "FloorBottom", 0, 500, sfcBlockPiece);




std::set<std::pair<int,int>> AddValueToSet(std::set<std::pair<int,int>> & setIn, int xChange, int yChange) 
{ //This shifts the whole set up, down, left or right. Can change both x and y at the same time.
	std::set<std::pair<int,int>> newSet;
	std::set<std::pair<int,int>>::iterator iT;

	for(iT = setIn.begin(); iT != setIn.end(); iT++)
	{
		newSet.insert( std::make_pair(iT->first + (xChange), iT->second + (yChange) ));
	}

	return newSet;
}

bool AnyFromSetAInSetB(std::set<std::pair<int,int>> & a, std::set<std::pair<int,int>> & b)
{
	bool bReturn = 0;

	std::set<std::pair<int,int>>::iterator itA;
	std::set<std::pair<int,int>>::iterator itB;

	for(itA = a.begin(); itA != a.end(); itA++) //loop through a, to see if we can find any from a in b. `
	{
		if(bReturn == 1)
		{
			break;
		}
		
		std::pair<int,int> tempPairA = std::make_pair(itA->first, itA->second);

		if(b.find(tempPairA) != b.end())
		{
			bReturn = 1;
			break;
		}
	}

	return bReturn;
}	

void DrawColisionBoundry(Video * Video1, std::set<std::pair<int,int>> & shiftset)
{
	Uint32 ColorPurple = SDL_MapRGB(Video1->GetScreen()->format, 0x55, 0x00, 0x55);

	std::set<std::pair<int,int>>::iterator it;

	for(it=shiftset.begin(); it != shiftset.end();it++)
	{
		Video1->PrintPixel(it->first,it->second,ColorPurple);
	}
}


bool WillCollideOnNextMove(std::set<std::pair<int,int>> & a, std::set<std::pair<int,int>> & b, std::string sDirection, BlockBase & Block1)
{
	bool bWillCollide = 0;
	std::set<std::pair<int,int>> testSet;

	if(sDirection == "down")
	{
		//all y's + height
		testSet = AddValueToSet(a, 0, Block1.GetPieceHeight());
		bWillCollide = AnyFromSetAInSetB(testSet, b);

	}
	else if (sDirection == "up")
	{
		//all y's - height
		testSet = AddValueToSet(a, 0, Block1.GetPieceHeight()*-1);
		bWillCollide = AnyFromSetAInSetB(testSet, b);
	}
	else if (sDirection == "right")
	{
		//all x's + width
		testSet = AddValueToSet(a, Block1.GetPieceWidth(),0);
		bWillCollide = AnyFromSetAInSetB(testSet, b);
	}
	else if (sDirection == "left")
	{
		//all x's - width
		testSet = AddValueToSet(a, Block1.GetPieceWidth()*-1,0);
		bWillCollide = AnyFromSetAInSetB(testSet, b);
	}

	DrawColisionBoundry(Video1, testSet);

	return bWillCollide;
}

bool WillCollideWithBlocksInPlay(std::string BlockMove)
{

	bool bReturn = 0;

	if(
	WillCollideOnNextMove(Block1.getBorder(), Floor.getBorder(), BlockMove, Block1)
						|| WillCollideOnNextMove(Block1.getBorder(), Block2.getBorder(), BlockMove, Block1)
	)
	{ bReturn = 1; }

	return bReturn;
}



bool WillActiveBlockCollideWithListOfBlocks();

void keyBoardTest(Video *keysVideoptr) //TODO rename keyBoardTest to something more meaningfull, like MainGameLoop or something.
{//starts the game.  

	Timer FallDownTimer(500);
	Timer BlockMover(125); //control speed of left right motion.
    Timer BlockMoverDown(50); // control speed of downward motion
	Timer GameLoopRate(20);

	SDL_Rect TextLocation;
	SDL_Rect loc_MouseTest;
	std::string sMouseText = "";
	
	std::string KeyPress = "";

	char* c_string = new char[100];
	unsigned int fontCounter = 0;
	bool quit=false;
	
	TextLocation.y = 0;
	TextLocation.x = 0;
	loc_MouseTest.y = 375;
	loc_MouseTest.x = 50;

	int image_x = 0;
	int image_y = 0;
	bool image_direction = true;
	int image_speed = 10;

	int block_speed = 5;
	
	int orientation = 0;

	std::string BlockMove = "";

	while(quit==false)
	{	
		if(!GameLoopRate.TimeToMove())
		{
			continue;
		}

		if (FallDownTimer.TimeToMove())
		{
		    printf("TimeToMoveDown: \n");
	//		Block1.FallDown();
			
		}
		if (BlockMover.TimeToMove() && BlockMove != "")
		{
			printf("TimeToMoveLeftRight: %s \n", BlockMove.c_str());
			if (BlockMove == "left")
			{
				if(!WillCollideWithBlocksInPlay(BlockMove))
				{
					Block1.MoveLeft();
				}
				//if key is not currently suppressed.
				
			}
			if (BlockMove == "right")
			{
				if(!WillCollideWithBlocksInPlay(BlockMove))
				{
					Block1.MoveRight();
				}
				
			}
		}
		if (BlockMoverDown.TimeToMove() && BlockMove == "down")
		{
			if(!WillCollideWithBlocksInPlay(BlockMove))
			{
				Block1.MoveDown();
			}
		}

		while(SDL_PollEvent(&event))
		{
			switch(event.type)//set the proper text
			{
				case SDL_KEYDOWN:  // Key was pressed
				
					KeyPress = SDL_GetKeyName(event.key.keysym.sym);
					
					printf("The %s key was pressed!\n",KeyPress.c_str());
					
					TextLocation.x+=10;

					if(KeyPress == "up")
					{
						if(orientation == 3)
						{
							orientation = 0;
						}
						else
						{
							orientation++;
						}

						printf("orientation: %d", orientation);
					}
					
					if(KeyPress == "down" && !BlockMoverDown.TimeToMove())
					{
						if(!Block1.getBorder().empty() && !WillCollideWithBlocksInPlay(KeyPress))
						{
							Block1.MoveDown();
						}
						BlockMove = "down";
						BlockMoverDown.Reset();
					}
					
					if(KeyPress == "left")
					{
						//Block1.MoveLeft();
						BlockMove = "left";
					}
					
					if(KeyPress == "right")
					{
						//Block1.MoveRight();
						BlockMove = "right";
					}
					
					if(KeyPress == "q" || KeyPress == "escape")
					{
						quit=true;
					}
					if (KeyPress == "z")
					{
						Block1.SetPos(1,0);
					}

					break;

				
				case SDL_KEYUP:  // Key was DEpressed
						
					break;
				
				case SDL_MOUSEMOTION:
					printf("Mouse Position %d , %d, %d, %d", event.motion.xrel, event.motion.yrel, event.motion.x, event.motion.y);
					sprintf(c_string, "mouse position %d , %d, %d, %d", event.motion.xrel, event.motion.yrel, event.motion.x, event.motion.y);
					KeyPress = c_string;
					Video1->ApplySurface(300, 577, ScreenFont1.DrawFontString(KeyPress));
					fontCounter += 28;
					break;

				case SDL_MOUSEBUTTONDOWN:
					printf("Mouse button %d pressed at (%d,%d)\n", event.button.button, event.button.x, event.button.y);
					
					break;

				case SDL_QUIT: quit=true;
					break;
			}
		}

		//DrawAll the pieces.
		Floor.Draw(Video1, 0);

		Block1.Draw(Video1, orientation);
		Block2.Draw(Video1, 0);
		Block3.Draw(Video1, 0);

		Video1->Flip();
		SDL_FillRect(SDL_GetVideoSurface(), NULL, g_black);
	}

	c_string = NULL;
	delete c_string;
}

int main(int argc, char *args[]){

	
	vecBlocksInPlay.push_back(Block2);
	vecBlocksInPlay.push_back(Block3);
	vecBlocksInPlay.push_back(Floor);

	char VideoDriver[50];

	bool quit = false; //bool to see if user wants to exit the game.
	SDL_VideoDriverName(VideoDriver, 50);
	printf("Video Driver: %s\n", VideoDriver);

	Video1->ApplySurface(10,50,ScreenFont1.DrawFontString("Welcome to the game it will start soon!!!"));
	Video1->Flip();

	keyBoardTest(Video1);
	
 	exit(0);

    return 0;
}