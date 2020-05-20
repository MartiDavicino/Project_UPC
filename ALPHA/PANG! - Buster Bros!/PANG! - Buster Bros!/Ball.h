#ifndef __BALL_H__
#define __BALL_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum class BALL_TYPE
{
	NO_TYPE,
	BIG,
	MEDIUM,
	SMALL,
	TINY
};

class Ball
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Ball(int x, int y, BALL_TYPE type);

	// Destructor
	virtual ~Ball();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);


	virtual void SetToDelete();

	Animation idle;



	virtual BALL_TYPE GetType();


public:

	BALL_TYPE type = BALL_TYPE::NO_TYPE;
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	bool pendingToDelete = false;

	const int gravity = 300.0f;         // pixels / second^2

	const float deltaTime = 1.0f / 60.0f; // More or less 60 frames per second

	int Ball_vy = -50.0f;

	int Ball_vx = 100.0f;

	int xOffset = 10;
	int yOffset = 10;

	bool div = false;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __BALL_H__