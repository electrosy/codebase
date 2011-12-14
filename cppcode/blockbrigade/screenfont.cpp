#include "stdafx.h"

#include "screenfont.h"


// class constructor
ScreenFont::ScreenFont()
{
	SDL_Color textColor = {55,0,55};

    if(TTF_Init()==-1){
        printf("Could not initialize TTF");
    }
	else //create TTF Font
	{                     
		mp_FontOne = TTF_OpenFont("./resources/lazy.ttf",25);
	}
    
	if(mp_FontOne == NULL){
        printf("Could not open the TTF Font!");
		printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
}
ScreenFont::~ScreenFont()
{
	mp_FontOne = NULL;
	delete mp_FontOne;

	//mp_FontSurface = NULL;
	//delete mp_FontSurface;

	SDL_FreeSurface(mp_FontSurface);
	//SDL_FreeSurface(mp_FontOne);
}

SDL_Surface* ScreenFont::DrawFontString(std::string str)
{
	SDL_Color textColor = {55,55,25};

	if(mp_FontOne != NULL)
	{
		mp_FontSurface = TTF_RenderText_Solid(mp_FontOne,str.c_str(),textColor);
	}

	return mp_FontSurface;
}