#pragma once

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
	enum class Tiles {
		NONE,
		WALL,
		FLOOR,
		TOP,
		STAIRS,
		STAIRS_TOP,

	};
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

	void lvlLoading(int tiles[MAXT_Y][MAXT_X]);

	// Disables the player and the enemies
	bool CleanUp();

	void LvlChange(int lvlA[MAXT_Y][MAXT_X], int lvlB[MAXT_Y][MAXT_X]);

public:

	int levelSelection = 1;

private:


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
public:
	//maybe we should use level one tiles set as template and only modificate the changing tiles
	// h: 30 tiles w: 56
	// 0= none , 1=wall, 2=floor, 3=top, 4 = Normal Platform, 5 = Destructible Platform
	bool lvlchanged = false; //checks if the level has already changed

	int tiles_template[MAXT_Y][MAXT_X];
};

