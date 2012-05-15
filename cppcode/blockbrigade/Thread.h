#include "SDL_thread.h"

#pragma once

class Thread
{

private:

	SDL_Thread *thread;

	static int StaticThreadProc(void* pParam)
	{
	   return ((Thread*)pParam)->Run();
	}
protected:
	virtual int Run() = 0;

public:

	Thread(void);
	~Thread(void);
};
 