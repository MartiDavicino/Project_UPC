#ifndef __MODULE_WINDOW_H__
#define __MODULE_WINDOW_H__

// TODO 1:	Create the declaration of ModuleWindow class
//			It should inherit from module and override all necessary functions

#include "Module.h"

//Try to figure out what this is used for
struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called on application start.
	// Initializes the SDL Library and creates a window.
	bool Init();

	// Called on application exit.
	// Destroys the window and uninitializes the SDL library
	bool CleanUp();

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The window's surface
	SDL_Surface* screenSurface = nullptr;
};

#endif // !__MODULE_WINDOW_H__

