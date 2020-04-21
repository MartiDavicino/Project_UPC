#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleRopes.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleBalls.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	//Idle anim
	idleRightAnim.PushBack({ 0,66,25,35 });
    idleRightAnim.loop = true;
	idleRightAnim.speed = 0.1f;

	idleLeftAnim.PushBack({ 84,66,35,35 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.1f;

	dead.PushBack({ 0,0,0,0 });
	// Walk Right
	rightAnim.PushBack({ 0,0,30,29});
	rightAnim.PushBack({ 31,0,30,30 });
	rightAnim.PushBack({ 64,0,29,30});
	rightAnim.PushBack({ 96,0,27,30 });
	rightAnim.loop=true;
	rightAnim.speed = 0.1f;
	//Walk left
	leftAnim.PushBack({ 0,133,30,29 });
	leftAnim.PushBack({ 31,133,30,30 });
	leftAnim.PushBack({ 64,133,29,30 });
	leftAnim.PushBack({ 96,133,27,30 });
	leftAnim.PushBack({ 129,133,28,30 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;
	//CLimb 
	climbAnim.PushBack({ 0,32,23,30 });
	climbAnim.PushBack({ 23,32,23,30 });
	climbAnim.PushBack({ 47,32,23,30 });
	climbAnim.PushBack({ 60,32,23,30 });
	climbAnim.loop = true;
	climbAnim.speed = 0.1f;
	//Shoot
	shootRightAnim.PushBack({ 0,67,15,31 });
	shootRightAnim.PushBack({ 26,67,35,35 });
	shootRightAnim.loop = true;
	shootRightAnim.speed = 0.00001f;

	shootLeftAnim.PushBack({ 84,67,27,34 });
	shootLeftAnim.PushBack({ 56,67,27,34 });
	shootLeftAnim.loop = shootRightAnim.loop;
	shootLeftAnim.speed = shootRightAnim.speed;

	// move upwards
	/*upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;*/

	// Move down
	/*downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;*/
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/SpriteSheet.png");
	currentAnimation = &idleRightAnim;

	FiringFx = App->audio->LoadFx("Assets/[FX]- firing sound.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 150;
	position.y = 170;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 30, 30 }, Collider::Type::PLAYER, this);

	return ret;
}

void setFalse(int* status);

void setFalseAll(int list[], int* collider);


update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	//App->player->position.x += 1;

	//god mode
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		LOG("God mode activated\n");
		switch (GodMode)
		{
		case(true):

			App->collisions->matrix[Collider::Type::PLAYER][Collider::Type::WALL_A] = true;

			App->collisions->matrix[Collider::Type::PLAYER][Collider::Type::WALL_D] = true;

			App->collisions->matrix[Collider::Type::PLAYER][Collider::Type::BALL] = true;

			App->collisions->matrix[Collider::Type::PLAYER][Collider::Type::FLOOR] = true;


			GodMode = false;
			break;

		case(false):

			App->collisions->matrix[Collider::Type::PLAYER][Collider::Type::WALL_A] = true;

			App->collisions->matrix[Collider::Type::PLAYER][Collider::Type::WALL_D] = true;

			App->collisions->matrix[Collider::Type::PLAYER][Collider::Type::BALL] = false;

			App->collisions->matrix[Collider::Type::PLAYER][Collider::Type::FLOOR] = true;

			GodMode = true;
			break;

		}

	}

	//Divide balls manually
	if (App->input->keys[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
	{
		LOG("Ball divided manually\n");
		App->balls->AddBall(BALL_TYPE::SMALL, 120,100, true);
		App->balls->AddBall(BALL_TYPE::SMALL, 100,100, false);


	}
	

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (Collision_A != true)
		{
			position.x -= speed;
		}
		
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
		if (goingRight != false)
			goingRight = false;

	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (Collision_D != true)
		{
			position.x += speed;
		}
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
		if (goingRight != true)
			goingRight = true;

	}

	//if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	//{
	//	if (Collision_F != true)
	//	{
	//		position.y += speed;
	//	}
	//}

	//if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	//{
	//	//only if detected stairs

	//	position.y -= speed;
	//	if (currentAnimation != &climbAnim)
	//	{
	//	     climbAnim.Reset();
	//		currentAnimation = &climbAnim;
	//	}
	//}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		/*if (currentAnimation != &shootRightAnim)
		{
			shootRightAnim.Reset();
			currentAnimation = &shootRightAnim;
		}*/
	/*	App->particles->AddParticle(App->particles->rope, position.x, position.y-0, Collider::Type::ROPE);*/


		switch (goingRight)
		{
		case(false):
			currentAnimation = &idleLeftAnim;
			break;
		case(true):
			currentAnimation = &idleRightAnim;
			break;
		}

		LOG("SHOOTING ROPE!")
		App->ropes->AddRope(App->ropes->rope, position.x +9, position.y - 370, Collider::Type::ROPE);
		App->audio->PlayFx(FiringFx);
		

		
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_W] != KEY_STATE::KEY_DOWN)
	{
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
			if (isAlive == true)
			{
				if (currentAnimation != &shootLeftAnim || currentAnimation != &shootRightAnim)
				{
					switch (goingRight)
					{
					case(false):
						currentAnimation = &idleLeftAnim;
						break;
					case(true):
						currentAnimation = &idleRightAnim;
						break;
					}
				}
				
			}
			else
			{
				currentAnimation = &dead;
			}
	}

	if (App->input->keys[SDL_SCANCODE_G] != KEY_STATE::KEY_DOWN)
	{
		App->collisions->DebugDraw();
	}
	

		collider->SetPos(position.x, position.y);

		currentAnimation->Update();

		if (destroyed)
		{
			/*destroyedCountdown--;
			if (destroyedCountdown <= 0)
				return update_status::UPDATE_STOP;*/
			/*this->lives = this->lives - 1;
			if (lives < 0) {
				App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneIntro, 60);
			}

			if (lives = 0) {*/
			App->fade->FadeToBlack((Module*)App->scene, (Module*)App->lose, 60);
		/*	}*/
			destroyed = false;
		}

		Collision_A = false;
		Collision_D = false;
		Collision_F = false;

		return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
	
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		

		/*App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);*/

		if (c1->type == Collider::Type::BALL && c2->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BALL)
		{
			lives -= 1;
			App->particles->AddParticle(App->particles->blink, 0, 0, Collider::Type::NONE, 0);
			if (isAlive == true) 
			{
				SDL_Delay(200);
				switch (goingRight)
				{
				case(false):
					LOG("Die Right\n")
						App->particles->AddParticle(App->particles->dieRightAnim, position.x, position.y, Collider::Type::NONE, 0);
					break;
				case(true):
					LOG("Die Left\n")
						App->particles->AddParticle(App->particles->dieLeftAnim, position.x, position.y, Collider::Type::NONE, 0);
					break;
				}
				isAlive = false;
			}

			App->audio->PlayFx(explosionFx);

			destroyed = true;
		}

		if (c1->type == Collider::Type::WALL_A && c2->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL_A)
		{
			Collision_A = true;
		}
		if (c1->type == Collider::Type::WALL_D && c2->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL_D)
		{
			Collision_D = true;
		}
		if (c1->type == Collider::Type::FLOOR && c2->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::FLOOR)
		{
			Collision_F = true;
		}
	}


}

void setFalse(int* status)
{
	*status = false;
}


void setFalseAll(int list[], int* collider)
{
	for (int i = 0; i < 3; ++i)
	{
		setFalse(collider + i);
	}
}
