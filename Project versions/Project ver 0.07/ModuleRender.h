#ifndef __MODULERENDERER_H__
#define __MODULERENDERER_H__

#include "Module.h"

struct SDL_Renderer;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	// Called on application start.
	// Creates the rendering context using the program's window.
	bool Init() override;

	// Called at the end of the application loop.
	// Displays a rectangle in the rendering context
	// Updates the screen with the rendered content
	update_status PostUpdate() override;

	// Called on application exit.
	// Destroys the rendering context
	bool CleanUp() override;

public:
	// Rendering context used for any rendering action
	SDL_Renderer* renderer = nullptr;

};

#endif //__ModuleRenderer_H__
