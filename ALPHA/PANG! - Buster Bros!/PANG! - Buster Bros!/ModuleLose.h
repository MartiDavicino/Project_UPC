#ifndef __MODULE_LOSE__H__
#define __MODULE_LOSE__H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleLose : public Module
{
public:
	//Constructor
	ModuleLose(bool startEnabled);

	//Destructor
	~ModuleLose();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgtitle = nullptr;
private:
	int loseMusic = 0;
};

#endif
