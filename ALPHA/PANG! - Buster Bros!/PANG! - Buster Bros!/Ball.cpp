#include "Ball.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleBalls.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"

Ball::Ball(int x, int y, BALL_TYPE  Type) : position(x, y)
{
	spawnPos = position;
	type = Type;
	div = false;


	if (type == BALL_TYPE::BIG) {
		idle.PushBack({ 1,6,48,40 });

		idle.loop = true;
		idle.speed = 0.1f;
		currentAnim = &idle;

		collider = App->collisions->AddCollider({ 0, 0, 48, 40 }, Collider::Type::BALL, (Module*)App->balls);
	}
	else if (type == BALL_TYPE::MEDIUM) {
		idle.PushBack({ 52,13,32,26 });

		idle.loop = true;
		idle.speed = 0.1f;
		currentAnim = &idle;

		collider = App->collisions->AddCollider({ 0, 0, 32, 26 }, Collider::Type::BALL, (Module*)App->balls);
	}
	else if (type == BALL_TYPE::SMALL) {
		idle.PushBack({ 86,19,16,14 });

		idle.loop = true;
		idle.speed = 0.1f;
		currentAnim = &idle;

		collider = App->collisions->AddCollider({ 0, 0, 16, 14 }, Collider::Type::BALL, (Module*)App->balls);

	}
	else if (type == BALL_TYPE::TINY) {
		idle.PushBack({ 106,23,8,7 });

		idle.loop = true;
		idle.speed = 0.1f;
		currentAnim = &idle;

		collider = App->collisions->AddCollider({ 0, 0,8,7 }, Collider::Type::BALL, (Module*)App->balls);
	}
}

Ball::~Ball()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Ball::GetCollider() const
{
	return collider;
}

void Ball::Update()
{
	//translate ball position into tiles coordinates


	/*tilePosition.x = position.x / 8; tilePosition.y = position.y / 8;*/


	//check if adjacent tiles are floor or wall then changee x/y speed



	//for (int i = tilePosition.x-1; i <= tilePosition.x+1; i++)
	//{
	//	for (int j = tilePosition.y - 1; i <= tilePosition.y + 1; j++)
	//	{
	//		if(App->scene->tiles_01[i][j])
	//	}
	//}

	if (App->player->destroyed == false) {
		Ball_vy = Ball_vy + (gravity * deltaTime);

		position.y = position.y + (Ball_vy * deltaTime) + (gravity * (deltaTime * deltaTime));
		position.x = position.x + (Ball_vx * deltaTime);
	}
	else {
		position.y = position.y;
		position.x = position.x;
	}

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Ball::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Ball::OnCollision(Collider* collider)
{
	//LOG("Ball Destroyed\n");


	if (type == BALL_TYPE::BIG) {
		if (collider->type == Collider::Type::FLOOR) {
			Ball_vy = -280;
		}
		if (collider->type == Collider::Type::ROPE) {
			div = true;
			App->balls->DivideBalls();

			SetToDelete();
		}
	}
	if (type == BALL_TYPE::MEDIUM) {
		if (collider->type == Collider::Type::FLOOR) {
			Ball_vy = -240;
		}
		if (collider->type == Collider::Type::ROPE) {
			div = true;
			App->balls->DivideBalls();

			SetToDelete();
		}
	}
	if (type == BALL_TYPE::SMALL) {
		if (collider->type == Collider::Type::FLOOR) {
			Ball_vy = -210;
		}
		if (collider->type == Collider::Type::ROPE) {
			div = true;
			App->balls->DivideBalls();

			SetToDelete();
		}
	}
	if (type == BALL_TYPE::TINY) {
		if (collider->type == Collider::Type::FLOOR) {
			Ball_vy = -155;
		}
		if (collider->type == Collider::Type::ROPE) {
			div = true;
			App->balls->DivideBalls();

			SetToDelete();
		}
	}

}

void Ball::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

BALL_TYPE Ball::GetType() {
	return this->type;
}