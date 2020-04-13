#include "ModuleWindow.h"

#include "Application.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")

ModuleWindow::ModuleWindow() : Module()
{

}

ModuleWindow::~ModuleWindow()
{

}

bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	// TODO 2:	Init the library and check for possible errors using SDL_GetError()
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error:\n");
		LOG(SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (WIN_FULLSCREEN == true)
			flags |= SDL_WINDOW_FULLSCREEN;

		if (WIN_BORDERLESS == true)
			flags |= SDL_WINDOW_BORDERLESS;

		if (WIN_RESIZABLE == true)
			flags |= SDL_WINDOW_RESIZABLE;

		if (WIN_FULLSCREEN_DESKTOP == true)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		//	TODO 3:	Pick the width and height and experiment with different window flags.
		//			Create the window and check for errors
		//			Expose the SDL_window as a public variable to access it through the different application modules
		window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);

		if (window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: \n");
			LOG(SDL_GetError());
			ret = false;
		}
		else
		{
			//TODO 4: Create a screen surface and keep it as a public variable
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp()
{
	// TODO 5:	Fill with code the CleanUp() method
	//			Remove all the data and uninitialize SDL

	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window != NULL)
		SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return true;
}