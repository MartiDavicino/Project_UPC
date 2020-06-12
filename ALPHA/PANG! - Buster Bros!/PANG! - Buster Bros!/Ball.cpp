#include "Ball.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleBalls.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_scancode.h"

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
	if (App->balls->ballsStop == true)
	{
		counter++;
		if (counter >= 180)
		{
			App->balls->ballsStop = false;
				counter = 0;
		}
	}

	if (App->player->destroyed == false && App->balls->ballsStop==false) {
		if (Ball_vy > 4.8f) {
			Ball_vy = 4.5f;
		}
		position.x += Ball_vx;
		position.y -= (Ball_vy + gravity);
		Ball_vy -= gravity;
	}
	else {
		position.y = position.y;
		position.x = position.x;
	}

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	//explode
	if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN)
	{
		if (collider != nullptr)
		{
			App->balls->ExplodeAll();
			
		}
		
	}

}

void Ball::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Ball::OnCollision(Collider* collider)
{
	//LOG("Ball Destroyed\n");

	if (collider->type == Collider::Type::ROPE) {
			div = true;
			App->balls->DivideBalls();

			SetToDelete();
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