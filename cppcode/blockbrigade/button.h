#ifndef BUTTON_H
#define BUTTON_H

#define CLIP_MOUSEOVER 0
#define CLIP_MOUSEOUT 1
#define CLIP_MOUSEDOWN 2
#define CLIP_MOUSEUP 3

#include "SDL.h"
#include "video.h"
//*
//* This is a class that is a mouse button and it can detect a mouse over, mouse out,
//* down and up.
//*
class Button
{
private:
    //The Attributes of the Button
    SDL_Rect box;
    
    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;
    SDL_Rect* clips;

	SDL_Surface* image;

	Video* _screen;
    
public:
	Button();
	~Button();
    //Initialize the variables
    Button(int x, int y, int w, int h, Video* screen);
    //Handles events and set the button's sprite region
    void handle_events();
    //Shows the button on the screen
    void show();
    SDL_Event event;
};

#endif // BUTTON_H
