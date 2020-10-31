#ifndef __MODULEBALLSH__
#define __MODULEBALLS_H__

#include "Module.h"
#include "Ball.h"
#include "ModuleParticles.h"

#define MAX_BALLS 100

// TODO 4: Create a new enemy type: the Mech



struct BallSpawnpoint
{
	BALL_TYPE type = BALL_TYPE::NO_TYPE;
	int x, y; 
	bool right = true;
};

class Ball;
struct SDL_Texture;

class ModuleBalls : public Module
{
public:
	// Constructor
	ModuleBalls(bool startEnabled);

	// Destructor
	~ModuleBalls();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	update_status PreUpdate() override;
	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddBall(BALL_TYPE type, int x, int y,bool right);

	// Iterates the queue and checks for camera position
	void HandleBallsSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleBallsDespawn();

	void DivideBalls(Ball ball);


	int Xoffset = 10;
	int Yoffset = 0;

	//collisions
	bool Collision_A;
	bool Collision_D;
	bool Collision_F;

	Ball* Balls[MAX_BALLS] = { nullptr };

private:
	// Spawns a new enemy using the data from the queue
	void SpawnBall(const BallSpawnpoint& info);

	

private:
	// A queue with all spawn points information
	BallSpawnpoint spawnQueue[MAX_BALLS];

	// All spawned enemies in the scene
	

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an enemy
	int enemyDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__