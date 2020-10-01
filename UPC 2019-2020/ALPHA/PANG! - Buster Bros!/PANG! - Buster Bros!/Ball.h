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
	iPoint tilePosition;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	bool pendingToDelete = false;

	float gravity = 0.1f;         // pixels / second^2

	float Ball_vy = 0.05f;

	float Ball_vx = 1.0f;

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
private:
	int counter = 0;
};

#endif // __BALL_H__