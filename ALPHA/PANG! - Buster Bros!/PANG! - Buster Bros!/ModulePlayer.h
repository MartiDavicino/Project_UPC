#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

enum class ITEM_EQUIPPED {

	NONE, HOOK, GUN
};

enum PLAYER_STATE {
	IDLE,
	RUNNING,
	CLIMBING,
	SHOOTING,
	DYING
};

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	void UpdateState();
	void UpdateLogic();
	void ChangeState(PLAYER_STATE previous,PLAYER_STATE next);



	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	//Collisions
	bool Collision_A = false;
	bool Collision_D = false;
	bool Collision_F = false;

public:

	PLAYER_STATE state = IDLE;
	// Position of the player in the map
	iPoint position;
	bool goingRight = true;
	bool GodMode = false;
	bool isInmune = false;
	bool inmuneActivated = false;
	bool destroyed = true;
	bool canClimb = false;
	ITEM_EQUIPPED itemEquipped;
	iPoint isMovingAt;
	
	int inmuneCountDown = 120;
	int resetInmuneCountDown = inmuneCountDown;
	// 0 equals to any object equipped

	enum Object
	{
		Hook,Inmune,gun
	};

	unsigned int lives = 4;
	bool bounce = false;

	// The speed in which we move the player (pixels per frame)
	int speed = 2;
	float gravity = 2.0f;
	float newGravity = gravity;
	float gravityDead = 600.0f;
	float deltaTime = 1.0f / 60.0f;

	float dead_vy = -300.0f;
	float dead_vx = 0.0f;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleRightAnim;
	Animation idleLeftAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation climbAnim;
	Animation dieAnim;
	Animation shootRightAnim;
	Animation shootLeftAnim;
	Animation dead;
	Animation dieRightAnim;
	Animation dieLeftAnim;

	int shootCountDown = 8;
	int resetCountDown = shootCountDown;
	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	// Sound effects indices
	uint FiringFx = 0;
	uint explosionFx = 0;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	
private:
	//countdowns to avoid multiple deaths when collision
	int deadCountDown = 0;


};

#endif //!__MODULE_PLAYER_H__