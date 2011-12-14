#ifndef SCREENFONT_H
#define SCREENFONT_H

#include <string>
#include "SDL_ttf.h"

//This will take care of the font and passing the 
//font to the Video, Somehow.

class ScreenFont
{

private:

	SDL_Surface* mp_FontSurface;

public:
        
	TTF_Font* mp_FontOne; //This stores the font.    
	SDL_Surface* DrawFontString(std::string str);

	ScreenFont();
	~ScreenFont();
};

#endif // SCREENFONT_H
