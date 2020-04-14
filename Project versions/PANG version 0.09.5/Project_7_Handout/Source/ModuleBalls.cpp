#include "ModuleBalls.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Ball.h"
#include "BigBall.h"
//#include "MediumBall.h"
//#include "SmallBall.h"
//#include "tinyBall.h"

#define SPAWN_MARGIN 50


ModuleBalls::ModuleBalls()
{
	for (uint i = 0; i < MAX_BALLS; ++i)
		Balls[i] = nullptr;
}

ModuleBalls::~ModuleBalls()
{

}

bool ModuleBalls::Start()
{
	texture = App->textures->Load("Assets/enemies.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/explosion.wav");

	return true;
}

update_status ModuleBalls::Update()
{
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

bool ModuleBalls::AddBall(BALL_TYPE type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (spawnQueue[i].type == BALL_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
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

				delete Balls[i];
				Balls[i] = nullptr;
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
				Balls[i] = new BigBall(info.x, info.y);
				break;
			case BALL_TYPE::MEDIUM:
				Balls[i] = new BigBall(info.x, info.y);
				break;
			}
			Balls[i]->texture = texture;
			Balls[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleBalls::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_BALLS; ++i)
	{
		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1)
		{
			Balls[i]->OnCollision(c2); //Notify the enemy of a collision

			delete Balls[i];
			Balls[i] = nullptr;
			break;
		}
	}
}