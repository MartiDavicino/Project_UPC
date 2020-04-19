#include "SmallBall.h"

#include "Ball.h"
#include "Path.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "MOduleballs.h"

SmallBall::SmallBall(int x, int y) : Ball(x, y)
{
	idle.PushBack({ 86,19,16,14 });

	idle.loop = true;
	idle.speed = 0.1f;
	currentAnim = &idle;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::BALL, (Module*)App->balls);
}

void SmallBall::Update()
{

	//moviment de la pilota per que reboti


	Ball_vy = Ball_vy + (gravity * deltaTime);

	position.y = position.y + (Ball_vy * deltaTime) + ( gravity * (deltaTime * deltaTime));
	position.x = position.x + (Ball_vx * deltaTime);

	// aixo es perque xoqui contra les parets, canviarho per coliders
	if (position.y >= 150)
	{
		Ball_vy = -Ball_vy;
	}

	if (position.x >= 250)
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
void SmallBall::OnCollision(Collider* collider)
{
	LOG("Ball Destroyed\n");

	//Must play different animations depending of ball size
	App->particles->AddParticle(App->particles->smallExplosion, position.x, position.y);



	App->balls->AddBall(BALL_TYPE::TINY, position.x + xOffset, position.y + yOffset, true);
	App->balls->AddBall(BALL_TYPE::TINY, position.x - xOffset, position.y + yOffset, false);


	//App->audio->PlayFx(destroyedFx);


	SetToDelete();
}
