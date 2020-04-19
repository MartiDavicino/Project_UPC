#include "TinyBall.h"

#include "Ball.h"
#include "Path.h"

#include "Application.h"
#include "ModuleCollisions.h"

TinyBall::TinyBall(int x, int y) : Ball(x, y)
{
	idle.PushBack({ 106,23,8,7 });

	idle.loop = true;
	idle.speed = 0.1f;
	currentAnim = &idle;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::BALL, (Module*)App->balls);
}

void TinyBall::Update()
{

	//moviment de la pilota per que reboti


	Ball_vy = Ball_vy + (gravity * deltaTime);

	position.y = position.y + (Ball_vy * deltaTime) + ( gravity * (deltaTime * deltaTime));
	position.x = position.x + (Ball_vx * deltaTime);



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Ball::Update();
}
