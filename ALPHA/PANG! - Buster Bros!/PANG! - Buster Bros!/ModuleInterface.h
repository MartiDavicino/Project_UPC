#ifndef __MODULE_INTERFACE_H__
#define __MODULE_INTERFACE_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"
#include "InterfaceElement.h"
#include "Animation.h"
#include "Drop.h"

#define MAX_ACTIVE_PARTICLES 100
#define MAX_ACTIVE_INTERFACE_ELEMENTS 30
#define MAX_ACTIVE_DROPS 30

struct SDL_Texture;
//struct Collider;

class ModuleInterface : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	

	ModuleInterface(bool startEnabled);

	//Destructor
	~ModuleInterface();

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

	//void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddElement(const InterfaceElement& element, int x, int y);
	void AddDrop(const Drop& drop, int x ,int y,DROP_TYPE type);

	void RandomDrop(int x,int y);

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

	InterfaceElement* interfaceElements[MAX_ACTIVE_INTERFACE_ELEMENTS] = { nullptr };

	Drop* drops[MAX_ACTIVE_INTERFACE_ELEMENTS] = { nullptr };

public:
	int itemsCount = 0;
	iPoint equippedPosition; 

	InterfaceElement* currentAnim = nullptr;

	InterfaceElement Blink;
	InterfaceElement zeroLife;
	InterfaceElement oneLife;
	InterfaceElement secondLife;
	InterfaceElement thirdLife;
	InterfaceElement fourthLife;

	InterfaceElement UI;

	//Include in player bool hasItem;
	InterfaceElement hook;
	InterfaceElement inmune;

	//scores
	InterfaceElement score400;
	InterfaceElement score800;
	InterfaceElement score1600;
	

	Drop hookDrop;
	Drop inmuneDrop;
	Drop gunDrop;

	Drop cherry;
	Drop banana;
	

};

#endif // !__MODULEPARTICLES_H__

