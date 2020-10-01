#ifndef __MODULE_ROPES_H__
#define __MODULE_ROPES_H__

#include "Module.h"

#include "Globals.h"
#include "Rope.h"
#include "Collider.h"

#define MAX_ACTIVE_ROPES 100

struct SDL_Texture;
struct Collider;

class ModuleRopes : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleRopes();

	//Destructor
	~ModuleRopes();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	Rope* AddRope(const Rope& rope, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Rope* ropes[MAX_ACTIVE_ROPES] = { nullptr };

public:
	//Template particle for an explosion
	Rope shooting;

	//Template particle for a laser
	Rope rope;
};

#endif // !__MODULEPARTICLES_H__
