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
#define MAX_ACTIVE_ITEMS_EQUIPPED 1

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


	DROP_TYPE dropType;
	
	void Equip(InterfaceElement& element);
	void ChangeLife(InterfaceElement& element);
	// Called when a particle collider hits another collider

	//void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddElement(const InterfaceElement& element, int x, int y,INTERFACE_ELEMENT_TYPE type,uint lifetime);
	void AddDrop(const Drop& drop, int x ,int y,DROP_TYPE type);

	void RandomDrop(int x,int y);


	//collisions
	void OnCollision(Collider* c1, Collider* c2);


private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

	InterfaceElement* interfaceElements[MAX_ACTIVE_INTERFACE_ELEMENTS] = { nullptr };

	Drop* drops[MAX_ACTIVE_INTERFACE_ELEMENTS] = { nullptr };

	InterfaceElement* itemEquipped[MAX_ACTIVE_ITEMS_EQUIPPED] = { nullptr };

	InterfaceElement* lives[MAX_ACTIVE_ITEMS_EQUIPPED] = { nullptr };

public:
	int itemsCount = 0;
	iPoint equippedPosition; 

	DROP_TYPE equippedItem;

	InterfaceElement* currentAnim = nullptr;

	InterfaceElement Blink;
	InterfaceElement zeroLife;
	InterfaceElement oneLife;
	InterfaceElement secondLife;
	InterfaceElement thirdLife;
	InterfaceElement fourthLife;

	InterfaceElement UI;
	InterfaceElement blackSection;
	InterfaceElement ready;
	InterfaceElement gameOver;

	//Include in player bool hasItem;
	InterfaceElement hook;
	//InterfaceElement inmune;
	InterfaceElement gun;
	InterfaceElement doubbleShot;
	InterfaceElement none;
	InterfaceElement blackSquare;

	//scores
	Drop score400;
	Drop score800;
	Drop score1600;
	

	Drop hookDrop;
	Drop inmuneDrop;
	Drop gunDrop;

	Drop stopTime;
	Drop dynamite;

	Drop cherry;
	Drop banana;
	

	//dissapear times
	uint scoreTime = 45;
	uint equippedTime = 0; 
	uint dropTime = 100;

	// 1 econd equals 60 frames
	uint countDown = 80;
	uint frameCount = 0;

	bool countDownReached = false;

	//
	int  coinDown = 0;
	
	int objectPickedFX = 0;
};

#endif // !__MODULEPARTICLES_H__

