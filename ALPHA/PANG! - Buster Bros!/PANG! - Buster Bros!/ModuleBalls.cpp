#include "ModuleBalls.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInterface.h"

#include "Ball.h"


#define SPAWN_MARGIN 50


ModuleBalls::ModuleBalls(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_BALLS; ++i)
		Balls[i] = nullptr;
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

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);

			App->interfaceElements->AddElement(App->interfaceElements->score400, Balls[i]->position.x, Balls[i]->position.y, INTERFACE_ELEMENT_TYPE::UI);

			App->score += 500;
			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::MEDIUM) {

			App->particles->mediumExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0;

			App->balls->AddBall(BALL_TYPE::SMALL, Balls[i]->position.x + Xoffset, Balls[i]->position.y + Yoffset, true);
			App->balls->AddBall(BALL_TYPE::SMALL, Balls[i]->position.x - Xoffset, Balls[i]->position.y + Yoffset, false);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);

			App->interfaceElements->AddElement(App->interfaceElements->score400, 22, 40, INTERFACE_ELEMENT_TYPE::UI);

			App->score += 500;
			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::SMALL) {

			App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0;

			App->balls->AddBall(BALL_TYPE::TINY, Balls[i]->position.x + Xoffset, Balls[i]->position.y + Yoffset, true);
			App->balls->AddBall(BALL_TYPE::TINY, Balls[i]->position.x - Xoffset, Balls[i]->position.y + Yoffset, false);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);

			App->interfaceElements->AddElement(App->interfaceElements->score400, 30, Balls[i]->position.y, INTERFACE_ELEMENT_TYPE::UI);


			Balls[i]->div = false;
			App->score += 500;
			Balls[i]->SetToDelete();

			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::TINY) {
			App->particles->AddParticle(App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y,Collider::Type::NONE,0,PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);

			App->score += 500;
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