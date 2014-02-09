#pragma once

#include "stdafx.h"
#include "video.h"

Video::Video(){

	SDL_Rect zeroRect;
	zeroRect.h = 0;
	zeroRect.w = 0;
	zeroRect.x = 0;
	zeroRect.y = 0;

                    
    printf("Initializing SDL.\n");
    
    // Init SDL_ using the everything option.
    if((SDL_Init(SDL_INIT_EVERYTHING)==-1)) { 
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
        printf("SDL initialized.\n");
    }
    
    //Sets the screen video mode to 800x600 and ? bits per pixel to the current display setting.
    screen = SDL_SetVideoMode(800, 600, 0, SDL_ANYFORMAT);
    if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set 800x600 video mode: %s\n", SDL_GetError());
        exit(1);
    }
    //set the window caption
    SDL_WM_SetCaption("SDL Game \"double O\" - Version 0.1", NULL);


	//Load Background
	m_pBackGround = NewLoadImage("./resources/background.bmp");
	m_pSprites = new SDL_Surface;


}//End Constructor.

Video::~Video()
{
	screen = NULL;
	delete screen;

	loadedImage = NULL; //Temp storage for the image that's loaded 
	delete loadedImage;

	optimizedImage = NULL;//The optimized image that will be used
	delete optimizedImage;

	m_pSprites = NULL;
	delete m_pSprites;
	
	//Shutdown all SDL subsystems.
	atexit(SDL_Quit);
    printf("Quiting....\n");
	
}//End Destructor.

void Video::Flip()
{
	SDL_Rect zeroClip;
	zeroClip.x = 0;
	zeroClip.y = 0;
	
	//SDL_BlitSurface(m_pBackGround, &m_pBackGround->clip_rect, screen, &zeroClip);
	SDL_BlitSurface(m_pSprites, &m_pSprites->clip_rect, screen, &zeroClip);

	if(SDL_Flip(screen))
	{
		printf("Unrecovered ERROR: %s\n", SDL_GetError());
		exit(0);
	}
}

void Video::PrintPixel(int x, int y, Uint32 pixel)
{
	/* Lock the screen for direct access to the pixels */
    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            }
    }

    int bpp = screen->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    switch(bpp) 
	{
		case 1:
			*p = pixel;
			break;
		case 2:
			*(Uint16 *)p = pixel;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *)p = pixel;
			break;
    }
    
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
    
    /* Update just the part of the display that we've changed */
    SDL_UpdateRect(screen, x, y, 1, 1);
}
SDL_Surface* Video::GetScreen()
{
	return screen;
}
int Video::ApplySurface(int InX, int InY, SDL_Surface* pSource)
{    
	int nReturn = 0;

	SDL_Rect zeroClip;
	SDL_Rect inClip;

	zeroClip.x = 0;
	zeroClip.y = 0;

	inClip.x = InX;
	inClip.y = InY;

	SDL_BlitSurface(pSource, &pSource->clip_rect, screen, &inClip);

	return nReturn;
}
SDL_Surface* Video::NewLoadImage(std::string fileName){

	loadedImage = IMG_Load(fileName.c_str()); //Load the image using SDL_image

	//If the image loaded Ok.
	if(loadedImage != NULL){
		// create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);
	    
		if(optimizedImage != NULL){
			//Map the colorkey
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format,0xFF,0,0xFF);
			//set all pixels of color R 0xFF, G 0, B 0xFF, to transparent
		   SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
		}
	}
	//Return the optimized image
	return optimizedImage;
}