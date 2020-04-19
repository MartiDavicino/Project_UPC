#include "BigBall.h"

#include "Ball.h"
#include "Path.h"

#include "Application.h"
#include "ModuleCollisions.h"

BigBall::BigBall(int x, int y) : Ball(x, y)
{
	idle.PushBack({ 1,6,48,40 });

	idle.loop = true;
	idle.speed = 0.1f;
	currentAnim = &idle;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::BALL, (Module*)App->balls);
}

void BigBall::Update()
{
	//moviment de la pilota per que reboti
	Ball_vy = Ball_vy + (gravity * deltaTime);

	position.y = position.y + (Ball_vy * deltaTime) + (gravity * (deltaTime * deltaTime));
	position.x = position.x + (Ball_vx * deltaTime);

	// aixo es perque xoqui contra les parets, canviarho per coliders
	if (position.y >= 155)
	{
		Ball_vy = -Ball_vy;
	}


	if (position.x >= 330)
	{
		Ball_vx = -Ball_vx;
	}
	if (position.x <= 0)
	{
		Ball_vx = -Ball_vx;
	}


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Ball::Update();
}
void BigBall::OnCollision(Collider* c1, Collider* c2) {

	if (c1 == collider == true)
	{
		Ball_vx = -Ball_vx;

	}

}

