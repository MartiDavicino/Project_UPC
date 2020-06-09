
#ifndef __DROP_H__
#define __DROP_H__

#include "Animation.h"
#include "p2Point.h"

struct Collider;
enum class DROP_TYPE
{
	HOOK,
	INMUNE,
	GUN,
	FOOD,
	SCORE,
	NONE
};

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

	//collisions
	void OnCollision(Collider* d1, Collider* d2);

	//get collider
	const Collider* GetCollider() const;



public:
	// Defines the position in the screen
	iPoint position;

	// Defines the speed at which the particle will move (pixels per second)
	iPoint speed;
	
	// A set of rectangle sprites

	Animation *currentAnim;
	Animation anim;
	Animation blink;

	DROP_TYPE name;

	bool isBlinking = false;

	bool isPlaced = false;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool isAlive = true;

	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	//When a time is reached, the drop will start to blink and then dissapear...
	//Maybe
	uint lifetime = 200;

	// The particle's collider
	Collider* collider = nullptr;
private:
	
};

#endif //__PARTICLE_H__