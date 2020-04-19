#include "MediumBall.h"

#include "Ball.h"
#include "Path.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleBalls.h"

MediumBall::MediumBall(int x, int y) : Ball(x, y)
{
	idle.PushBack({ 52,13,32,26 });

	idle.loop = true;
	idle.speed = 0.1f;
	currentAnim = &idle;

	collider = App->collisions->AddCollider({ 0, 0, 32, 26 }, Collider::Type::BALL, (Module*)App->balls);
}

void MediumBall::Update()
{

	//moviment de la pilota per que reboti


	Ball_vy = Ball_vy + (gravity * deltaTime);

	position.y = position.y + (Ball_vy * deltaTime) + ( gravity * (deltaTime * deltaTime));
	position.x = position.x + (Ball_vx * deltaTime);

	// aixo es perque xoqui contra les parets, canviarho per coliders
	


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Ball::Update();
}
void MediumBall::OnCollision(Collider* collider)
{
	LOG("Ball Destroyed\n");
	if (collider->type == Collider::Type::FLOOR) {
		this->Ball_vy = -340;
	}
	if (collider->type == Collider::Type::ROPE) {
		App->particles->AddParticle(App->particles->mediumExplosion, position.x, position.y);



		App->balls->AddBall(BALL_TYPE::MEDIUM, position.x + xOffset, position.y + yOffset, true);
		App->balls->AddBall(BALL_TYPE::MEDIUM, position.x - xOffset, position.y + yOffset, false);


		//App->audio->PlayFx(destroyedFx);


		SetToDelete();
	}

	////Must play different animations depending of ball size
	//App->particles->AddParticle(App->particles->mediumExplosion, position.x, position.y);


	//App->balls->AddBall(BALL_TYPE::SMALL, position.x + xOffset, position.y + yOffset, true);
	//App->balls->AddBall(BALL_TYPE::SMALL, position.x - xOffset,position.y + yOffset, false);


	//App->audio->PlayFx(destroyedFx);


	SetToDelete();
}
