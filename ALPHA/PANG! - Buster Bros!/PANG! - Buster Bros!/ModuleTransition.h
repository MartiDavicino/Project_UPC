#ifndef __MODULE_TRANSITION_H__
#define __MODULE_TRANSITION_H__

#include "Module.h"
#include "Animation.h"
#include "InterfaceElement.h"

#define MAX_ACTIVE_SELECTIONS 2

struct SDL_Texture;

class ModuleTransition : public Module
{
public:
	//Constructor
	ModuleTransition(bool startEnabled);

	//Destructor
	~ModuleTransition();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	void Selection(const InterfaceElement& selection, int x, int y);

	InterfaceElement* selectionCursor[MAX_ACTIVE_SELECTIONS] = { nullptr };

public:


	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* cursor = nullptr;
	SDL_Texture* blinkCursor = nullptr;

	InterfaceElement selection;

	//SDL_Texture* selection = nullptr;
	SDL_Texture* bgimg = nullptr;
private:
	uint countDown = 2;
	uint frameCount = 0;
	int scoreFont = -1;

	int planeFX = 0;
	int levelCompletedFx = 0;
};

#endif
