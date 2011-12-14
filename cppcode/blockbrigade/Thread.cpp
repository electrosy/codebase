#include "Thread.h"
#include "StdAfx.h"

//The classes derived from thread can only use multiple inheritence in -very- limited ways.  
//Specifically, Thread must be the leftmost derived class, and even then in certain cases it may 
//not work properly if virtual inheritence is used.

Thread::Thread(void)
{


	thread = SDL_CreateThread(&Thread::StaticThreadProc, (void*)this);
    if ( thread == NULL ) {
        fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
        return;
    }
}

Thread::~Thread(void)
{

   
}
