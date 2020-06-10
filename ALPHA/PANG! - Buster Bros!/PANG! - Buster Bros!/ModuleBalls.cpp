#include "ModuleBalls.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInterface.h"
#include "ModuleParticles.h"
#include "Ball.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "ModuleScene.h"


#define SPAWN_MARGIN 50


ModuleBalls::ModuleBalls(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_BALLS; ++i)
		Balls[i] = nullptr;
}

bool ModuleBalls::Start()
{
	switch(App->scene->levelSelection) //depending on the level set cursos to its pertinent position
	{
	case(1):
		texture = App->textures->Load("Assets/balls.png");
		break;
	case(2):
		texture = App->textures->Load("Assets/balls_blue.png");
		break;
	case(3):
		texture = App->textures->Load("Assets/balls_green.png");
		break;
	case(4):
		texture = App->textures->Load("Assets/balls.png");
		break;
	case(5):
		texture = App->textures->Load("Assets/balls_blue.png");
		break;
	case(6):
		texture = App->textures->Load("Assets/balls_green.png");
		break;
	}
	//texture = App->textures->Load("Assets/balls.png");
	ballDestroyedFx = App->audio->LoadFx("Assets/[FX]-Ballon pop.wav");

	return true;
}

update_status ModuleBalls::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (Balls[i] != nullptr && Balls[i]->pendingToDelete)
		{
			delete Balls[i];
			Balls[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBalls::Update()
{
	//spawn ball with click
	
	if (App->input->keys[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN || App->input->keys[SDL_BUTTON_LEFT] == KEY_STATE::KEY_UP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		LOG("Spawn ball manually at position : %d , %d ",x,y);
		AddBall(BALL_TYPE::BIG, x, y, true);

	}

	//explode all manually
	/*if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN )
	{
		ExplodeAll();
	}
	*/

	HandleBallsSpawn();

	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (Balls[i] != nullptr)
			Balls[i]->Update();

	}

	HandleBallsDespawn();

	return update_status::UPDATE_CONTINUE;

}

update_status ModuleBalls::PostUpdate()
{
	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (Balls[i] != nullptr)
			Balls[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleBalls::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (Balls[i] != nullptr)
		{
			delete Balls[i];
			Balls[i] = nullptr;
		}

	}

	return true;
}

bool ModuleBalls::AddBall(BALL_TYPE type, int x, int y, bool rightDirection)
{
	bool ret = false;

	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (spawnQueue[i].type == BALL_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;

			if (rightDirection == false)
				spawnQueue[i].right = false;

			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleBalls::HandleBallsSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (spawnQueue[i].type != BALL_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnBall(spawnQueue[i]);
				spawnQueue[i].type = BALL_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleBalls::HandleBallsDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (Balls[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (Balls[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", Balls[i]->position.x * SCREEN_SIZE);

				Balls[i]->SetToDelete();
			}
		}
	}
}

void ModuleBalls::SpawnBall(const BallSpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (Balls[i] == nullptr)
		{
			//Needs the correspondant spawn for each type of ball
			switch (info.type)
			{
			case BALL_TYPE::BIG:
				Balls[i] = new Ball(info.x, info.y, BALL_TYPE::BIG);
				if (info.right == false)
					Balls[i]->Ball_vx = -Balls[i]->Ball_vx / 2;
				break;
			case BALL_TYPE::MEDIUM:
				Balls[i] = new Ball(info.x, info.y, BALL_TYPE::MEDIUM);
				if (info.right == false)
					Balls[i]->Ball_vx = -Balls[i]->Ball_vx / 2;
				break;

			case BALL_TYPE::SMALL:
				Balls[i] = new Ball(info.x, info.y, BALL_TYPE::SMALL);
				if (info.right == false)
					Balls[i]->Ball_vx = -Balls[i]->Ball_vx / 2;
				break;

			case BALL_TYPE::TINY:
				Balls[i] = new Ball(info.x, info.y, BALL_TYPE::TINY);
				if (info.right == false)
					Balls[i]->Ball_vx = -Balls[i]->Ball_vx / 2;
				break;
			}

			Balls[i]->texture = texture;
			Balls[i]->destroyedFx = ballDestroyedFx;
			break;
		}
	}
}


void ModuleBalls::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_BALLS; ++i)
	{

		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1 && c2->type == Collider::Type::ROPE)
		{
			Balls[i]->OnCollision(c2);
			delete Balls[i];
			Balls[i] = nullptr;

			break;
		}

		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL_A) {

			App->balls->Balls[i]->Ball_vx = -(App->balls->Balls[i]->Ball_vx) * 2;

		}
		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL_D) {

			App->balls->Balls[i]->Ball_vx = -(App->balls->Balls[i]->Ball_vx) / 2;

		}
		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1 && c2->type == Collider::Type::FLOOR) {

			App->balls->Balls[i]->OnCollision(c2);

		}

	}

}

void ModuleBalls::DivideBalls()
{
	//This function divide and plays the explosion animation
	//And also, the function Random, ads a drop when the ball explodes
	for (uint i = 0; i < MAX_BALLS; ++i) {
		//Big=1, Medium=2,Small=3,Tiny=4

		if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::BIG) {

			App->particles->bigExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0;

			App->balls->AddBall(BALL_TYPE::MEDIUM, Balls[i]->position.x + Xoffset, Balls[i]->position.y + Yoffset, true);
			App->balls->AddBall(BALL_TYPE::MEDIUM, Balls[i]->position.x - Xoffset, Balls[i]->position.y + Yoffset, false);

			App->particles->AddParticle(App->particles->bigExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);
			App->interfaceElements->AddDrop(App->interfaceElements->score400, Balls[i]->position.x, Balls[i]->position.y, DROP_TYPE::SCORE);
		
			App->audio->PlayFx(ballDestroyedFx);

			ballsLeft--;
			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::MEDIUM) {

			App->particles->mediumExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0;

			App->balls->AddBall(BALL_TYPE::SMALL, Balls[i]->position.x + Xoffset, Balls[i]->position.y + Yoffset, true);
			App->balls->AddBall(BALL_TYPE::SMALL, Balls[i]->position.x - Xoffset, Balls[i]->position.y + Yoffset, false);

			App->particles->AddParticle(App->particles->mediumExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);
			App->interfaceElements->AddDrop(App->interfaceElements->score800, Balls[i]->position.x, Balls[i]->position.y, DROP_TYPE::SCORE);
			
			App->audio->PlayFx(ballDestroyedFx);

			ballsLeft--;
			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::SMALL) {

			App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0;

			App->balls->AddBall(BALL_TYPE::TINY, Balls[i]->position.x + Xoffset, Balls[i]->position.y + Yoffset, true);
			App->balls->AddBall(BALL_TYPE::TINY, Balls[i]->position.x - Xoffset, Balls[i]->position.y + Yoffset, false);

			App->particles->AddParticle(App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);
			App->interfaceElements->AddDrop(App->interfaceElements->score1600, Balls[i]->position.x, Balls[i]->position.y, DROP_TYPE::SCORE);

			App->audio->PlayFx(ballDestroyedFx);

			ballsLeft--;
			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::TINY) {
			App->particles->AddParticle(App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y,Collider::Type::NONE,0,PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);

			App->particles->AddParticle(App->particles->tinyExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->audio->PlayFx(ballDestroyedFx);

			ballsLeft--;
			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::NO_TYPE) {
			LOG("No type ball");
		}

	}
}


update_status ModuleBalls::checkRemainingBalls()
{
	int counter = 0;
	for (int i = 0; i < MAX_BALLS; ++i)
	{
		if (Balls[i] != nullptr)
		{
			return update_status::UPDATE_CONTINUE;
			break;
			counter = 0;
		}
		else if (Balls[i] == nullptr)
		{
			counter++;
			if (counter == MAX_BALLS) {
				App->fade->FadeToBlack((Module*)App->scene, (Module*)App->win, 60);
			}

		}
		else {
			LOG("ERROR");
		}
	}
}

void ModuleBalls::ExplodeAll()
{
	LOG("Balls exploded");
	//This function divide and plays the explosion animation
	//And also, the function Random, ads a drop when the ball explodes
	for (uint i = 0; i < MAX_BALLS; ++i) {
		//Big=1, Medium=2,Small=3,Tiny=4
		if (Balls[i] != nullptr)
		{
			/*if (Balls[i] != nullptr && Balls[i]->div == false && Balls[i]->type != BALL_TYPE::TINY) {

				App->balls->DivideBalls();

			}*/

			//for (int i = 0; i < 3; i++)
			
				if (Balls[i] != nullptr && Balls[i]->type == BALL_TYPE::BIG)
				{
					Balls[i]->div = true;
					App->balls->DivideBalls();

				}

				if (Balls[i] != nullptr && Balls[i]->type == BALL_TYPE::MEDIUM)
				{
					Balls[i]->div = true;
					App->balls->DivideBalls();

				}
				
				/*if (Balls[i] != nullptr && Balls[i]->type == BALL_TYPE::SMALL)
				{
					Balls[i]->div = true;
					App->balls->DivideBalls();

				}*/
			


		}
		

	}
}