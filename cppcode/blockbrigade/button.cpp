#pragma once

#include "button.h" // class's header file
#include "SDL_image.h"
#include "video.h"

//class constructor
Button::Button(int x, int y, int w, int h, Video* screen)
{
	//this->image = screen->NewLoadImage("buttons.png");
	printf("error: %s\n", SDL_GetError());

	if(screen != NULL)
	{
		this->_screen = screen;
	}

	//Set the button's attributes
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
                   
    //Clip the sprite sheets
    clips[CLIP_MOUSEOVER].x = 0;
    clips[CLIP_MOUSEOVER].y = 0;
    clips[CLIP_MOUSEOVER].w = 320;
    clips[CLIP_MOUSEOVER].h = 240;
    clips[CLIP_MOUSEOUT].x = 320;
    clips[CLIP_MOUSEOUT].y = 0;
    clips[CLIP_MOUSEOUT].w = 320;
    clips[CLIP_MOUSEOUT].h = 240;
    clips[CLIP_MOUSEDOWN].x = 0;
    clips[CLIP_MOUSEDOWN].y = 240;
    clips[CLIP_MOUSEDOWN].w = 320;
    clips[CLIP_MOUSEDOWN].h = 240;
    clips[CLIP_MOUSEUP].x = 320;
    clips[CLIP_MOUSEUP].y = 240;
    clips[CLIP_MOUSEUP].w = 320;
    clips[CLIP_MOUSEUP].h = 240;
                   
	clip = &clips[CLIP_MOUSEOUT]; //set the default sprite
	
}

Button::~Button() // class destructor
{
	
}
void Button::handle_events()
{
    //The mouse offsets
    int x = 0, y = 0;
    
    //if the mouse moved
    if( event.type == SDL_MOUSEMOTION)
	{   
		//get the mouse offsets
		x = event.button.x;
		y = event.button.y;
	       
		//if the mouse is over the button
		if((x > box.x)&&(x < box.x + box.w) &&(y>box.y)&&(y<box.y+box.h))
		{
				clip = &clips[CLIP_MOUSEOVER];
		}
		else
		{
			clip = &clips[CLIP_MOUSEOUT];
		}
     }
     
     
     //if a mouse button was pressed
     if(event.type == SDL_MOUSEBUTTONDOWN)
     {     //if the left mouse button was pressed
           if(event.button.button == SDL_BUTTON_LEFT)
           {
               //get the mouse offsets
               x = event.button.x;
               y = event.button.y;
               
               //if the mouse is over the button
               
               if((x >box.x)&&(x<box.x + box.w)&&(y>box.y)&&(y<box.y+box.h))
               {
                     //set the button sprite
                     clip = &clips[CLIP_MOUSEDOWN];
               }
           }
     }
     
     //if a mouse button was released
     if(event.type == SDL_MOUSEBUTTONUP)
     {
         //if the left mouse button was released
         if(event.button.button == SDL_BUTTON_LEFT)
         {
             //Get the mouse offsets
             x = event.button.x;
             y = event.button.y;
             
             //if the mouse is over the button
             if((x >box.x)&&(x<box.x+box.w)&&(y>box.y)&&(y<box.y+box.h))
             {
                   //set the button sprite
                   clip = &clips[CLIP_MOUSEUP];
             }
         }
     }
}//end button::handle_events()

void Button::show()
{
	this->_screen->ApplySurface(box.x,box.y,image,clip);
}
