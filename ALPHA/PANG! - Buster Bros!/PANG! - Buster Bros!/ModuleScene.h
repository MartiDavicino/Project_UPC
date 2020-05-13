#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene(bool startEnabled);

	//Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	
	int levelSelection = 3;

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture_01 = nullptr;
	SDL_Texture* bgTexture_02 = nullptr;
	SDL_Texture* bgTexture_03 = nullptr;
	SDL_Texture* bgTexture_04 = nullptr;
	SDL_Texture* bgTexture_05 = nullptr;
	SDL_Texture* bgTexture_06 = nullptr;
	
	// The sprite rectangle for the ground
	SDL_Texture* blockTexture_01 = nullptr;
	SDL_Texture* blockTexture_02 = nullptr;
	SDL_Texture* blockTexture_03 = nullptr;
	SDL_Texture* blockTexture_04 = nullptr;
	SDL_Texture* blockTexture_05 = nullptr;
	SDL_Texture* blockTexture_06 = nullptr;
};

#endif