#include "BigBall.h"

#include "Ball.h"
#include "Path.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleBalls.h"

BigBall::BigBall(int x, int y) : Ball(x, y)
{
	idle.PushBack({ 1,6,48,40 });

	idle.loop = true;
	idle.speed = 0.1f;
	currentAnim = &idle;

	collider = App->collisions->AddCollider({ 0, 0, 48, 40 }, Collider::Type::BALL, (Module*)App->balls);
}

void BigBall::Update()
{
	//moviment de la pilota per que reboti
	Ball_vy = Ball_vy + (gravity * deltaTime);

	position.y = position.y + (Ball_vy * deltaTime) + (gravity * (deltaTime * deltaTime));
	position.x = position.x + (Ball_vx * deltaTime);

	// aixo es perque xoqui contra les parets, canviarho per coliders
	






	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Ball::Update();
}
void BigBall::OnCollision(Collider* collider) {
	
	LOG("Ball Destroyed\n");

	//Must play different animations depending of ball size
	if (collider->type == Collider::Type::FLOOR) {
		this->Ball_vy = -400;
	}
	if (collider->type == Collider::Type::ROPE) {
		App->particles->AddParticle(App->particles->mediumExplosion, position.x, position.y);



		App->balls->AddBall(BALL_TYPE::MEDIUM, position.x + xOffset, position.y + yOffset, true);
		App->balls->AddBall(BALL_TYPE::MEDIUM, position.x - xOffset, position.y + yOffset, false);


		//App->audio->PlayFx(destroyedFx);


		SetToDelete();
	}
	//App->particles->AddParticle(App->particles->mediumExplosion, position.x, position.y);

	//

	//App->balls->AddBall(BALL_TYPE::MEDIUM, position.x + xOffset, position.y + yOffset, true);
	//App->balls->AddBall(BALL_TYPE::MEDIUM, position.x - xOffset, position.y + yOffset, false);


	////App->audio->PlayFx(destroyedFx);


	//SetToDelete();
	//App->particles->AddParticle(App->particles->bigExplosion, position.x, position.y);

	

}

