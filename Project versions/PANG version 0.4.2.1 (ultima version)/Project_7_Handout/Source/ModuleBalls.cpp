#include "ModuleBalls.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"

#include "Ball.h"
#include "BigBall.h"
#include "MediumBall.h"
#include "SmallBall.h"
#include "TinyBall.h"

#define SPAWN_MARGIN 50


ModuleBalls::ModuleBalls(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_BALLS; ++i)
		Balls[i] = nullptr;
}

ModuleBalls::~ModuleBalls()
{

}

bool ModuleBalls::Start()
{
	texture = App->textures->Load("Assets/balls.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/explosion.wav");

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

bool ModuleBalls::AddBall(BALL_TYPE type, int x, int y,bool rightDirection)
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
				Balls[i] = new BigBall(info.x, info.y);
				if (info.right == false)
					Balls[i]->Ball_vx = -Balls[i]->Ball_vx;
				break;
			case BALL_TYPE::MEDIUM:
				Balls[i] = new MediumBall(info.x, info.y);
				if (info.right == false)
					Balls[i]->Ball_vx = -Balls[i]->Ball_vx;
				break;

			case BALL_TYPE::SMALL:
				Balls[i] = new SmallBall(info.x, info.y);
				if (info.right == false)
					Balls[i]->Ball_vx = -Balls[i]->Ball_vx;
				break;

			case BALL_TYPE::TINY:
				Balls[i] = new TinyBall(info.x, info.y);
				if (info.right == false)
					Balls[i]->Ball_vx = -Balls[i]->Ball_vx;
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

		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1 && c2->type == Collider::Type::ROPE)
		{
			Balls[i]->OnCollision(c2);
			delete Balls[i];
			Balls[i] = nullptr;

			break;
		}

		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL_A) {

			App->balls->Balls[i]->Ball_vx = -(App->balls->Balls[i]->Ball_vx)*2;

		}
		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL_D) {

			App->balls->Balls[i]->Ball_vx = -(App->balls->Balls[i]->Ball_vx)/2;

		}
		if (Balls[i] != nullptr && Balls[i]->GetCollider() == c1 && c2->type == Collider::Type::FLOOR) {

			App->balls->Balls[i]->OnCollision(c2);

		}

	}

}

void ModuleBalls::DivideBalls(Ball ball)
{
	//This function divide and plays the explosion animation

	//Big=1, Medium=2,Small=3,Tiny=4
	switch (ball.type)
	{
	case(BALL_TYPE::BIG):

		App->particles->bigExplosion, ball.position.x, ball.position.y, Collider::Type::NONE, 0;

		App->balls->AddBall(BALL_TYPE::MEDIUM, ball.position.x + Xoffset, ball.position.y + Yoffset,true);
		App->balls->AddBall(BALL_TYPE::MEDIUM, ball.position.x - Xoffset, ball.position.y + Yoffset,false);
		App->score += 500;
		break;
	case(BALL_TYPE::MEDIUM):

		App->particles->mediumExplosion, ball.position.x, ball.position.y, Collider::Type::NONE, 0;

		App->balls->AddBall(BALL_TYPE::SMALL, ball.position.x + Xoffset, ball.position.y + Yoffset,true);
		App->balls->AddBall(BALL_TYPE::SMALL, ball.position.x - Xoffset, ball.position.y + Yoffset,false);
		App->score += 500;
		break;
	case(BALL_TYPE::SMALL):

		App->particles->smallExplosion, ball.position.x, ball.position.y, Collider::Type::NONE, 0;

		App->balls->AddBall(BALL_TYPE::TINY, ball.position.x + Xoffset, ball.position.y + Yoffset,true);
		App->balls->AddBall(BALL_TYPE::TINY, ball.position.x - Xoffset, ball.position.y + Yoffset,false);

		App->score += 500;

		break; 
	case(BALL_TYPE::TINY):
		App->score += 500;
		break;
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
		else if(Balls[i] == nullptr)
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