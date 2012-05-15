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

#include "SDL.h"

#include "video.h" //allows us to create a video object.
#include "screenfont.h" //a ttf font
#include "BlockBase.h"
#include "Timer.h"

//#include "button.h"
SDL_Event event; //SDL event

Video Video1;

Uint32 g_black = SDL_MapRGB(Video1.GetScreen()->format, 0x00, 0x00, 0x00);//Defines a color

ScreenFont ScreenFont1;


//std::map<std::string, BlockBase> BlocksOnScreen;


//BlockOnScreen.insert("LBlock", (&Video1, "LBlock", 0, 0));
//BlockOnScreen.insert("FloorBottom", (&Video1, "FloorBottom", 10, 500));

BlockBase Block1(&Video1, "LBlock", 0, 0);
BlockBase Floor(&Video1, "FloorBottom", 10, 500);

void keyBoardTest(Video *keysVideoptr) //starts the game.
{   

	Timer Timer1(500);
	Timer BlockMover(125);
    Timer BlockMoverDown(50);

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
		if (Timer1.TimeToMove())
		{
		    printf("TimeToMoveDown: \n");
			Block1.FallDown();
			
		}
		if (BlockMover.TimeToMove() && BlockMove != "")
		{
			printf("TimeToMoveLeftRight: %s \n", BlockMove.c_str());
			if (BlockMove == "left")
			{
				Block1.MoveLeft();
				//if key is not currently suppressed.
				
			}
			if (BlockMove == "right")
			{
				Block1.MoveRight();
				
			}
		}
		if (BlockMoverDown.TimeToMove() && BlockMove == "down")
		{
			Block1.MoveDown();
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
					
					if(KeyPress == "down")
					{
						Block1.MoveDown();
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
						Block1.SetPos(10,10);
					}

					break;

				
				case SDL_KEYUP:  // Key was DEpressed
						
					break;
				
				case SDL_MOUSEMOTION:
					printf("Mouse Position %d , %d, %d, %d", event.motion.xrel, event.motion.yrel, event.motion.x, event.motion.y);
					sprintf(c_string, "mouse position %d , %d, %d, %d", event.motion.xrel, event.motion.yrel, event.motion.x, event.motion.y);
					KeyPress = c_string;
					Video1.ApplySurface(300, 577, ScreenFont1.DrawFontString(KeyPress));
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
		Floor.Draw(&Video1, 0);
		Block1.Draw(&Video1, orientation);

		Video1.Flip();
		SDL_FillRect(SDL_GetVideoSurface(), NULL, g_black);
	}

	c_string = NULL;
	delete c_string;
}

int main(int argc, char *args[]){

	char VideoDriver[50];


 
	//*This stuff is for the mouse butten that was not successfully implemented 
	//*but all the code should be here somewhere.
	//make the button
	//Button myButton(170,120,320,240, &Video1);
    
	bool quit = false; //bool to see if user wants to exit the game.
	SDL_VideoDriverName(VideoDriver, 50);
	printf("Video Driver: %s\n", VideoDriver);

	Video1.ApplySurface(10,50,ScreenFont1.DrawFontString("Welcome to the game it will start soon!!!"));
	Video1.Flip();
	SDL_Delay(700); // TODO Instead of a delay there needs to be a timer.	    
    
	keyBoardTest(&Video1);
	
	Video1.~Video(); //Distory Video object before exiting SDL
	exit(0);

    return 0;
}

