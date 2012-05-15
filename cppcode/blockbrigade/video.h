#ifndef VIDEO_H
#define VIDEO_H

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include "SDL.h" 
#include "SDL_image.h"

//#include "sprite.h"

class Video { //A Video can print to a screen.
      
private:

    SDL_Surface *screen;
	SDL_Surface *m_pSprites;

public:

	SDL_Surface *m_pBackGround;
    SDL_Surface* loadedImage; //Temp storage for the image that's loaded 
	SDL_Surface* optimizedImage; //The optimized image that will be used

    Video();
    ~Video();

	SDL_Surface* GetScreen();
    SDL_Surface* NewLoadImage(std::string fileName);      
    int ApplySurface(int x, int y, SDL_Surface* source);
    void PrintPixel(int x, int y, Uint32 pixel);
	void Flip();
};
#endif //VIDEO_H