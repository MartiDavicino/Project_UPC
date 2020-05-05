
#ifndef __DROP_H__
#define __DROP_H__

#include "Animation.h"
#include "p2Point.h"

struct Collider;

struct Drop
{
public:
	// Constructor
	Drop();

	// Copy constructor
	Drop(const Drop& d);

	// Destructor
	~Drop();

	// Called in ModuleParticles' Update
	// Handles the logic of the particle
	// Returns false when the particle reaches its lifetime
	bool Update();

public:
	// Defines the position in the screen
	iPoint position;

	// Defines the speed at which the particle will move (pixels per second)
	iPoint speed;

	// A set of rectangle sprites

	Animation *currentAnim;
	Animation idle;
	Animation blink;

	bool isBlinking = false;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool isAlive = false;

	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	//When a time is reached, the drop will start to blink and then dissapear...
	//Maybe
	uint lifetime = 0;

	// The particle's collider
	Collider* collider = nullptr;
};

#endif //__PARTICLE_H__