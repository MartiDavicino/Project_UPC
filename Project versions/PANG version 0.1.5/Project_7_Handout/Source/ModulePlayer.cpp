#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleRopes.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	//Idle anim
	idleAnim.PushBack({ 0,66,25,32 });
	/*idleAnim.PushBack({ 0,66,29,32 });
	idleAnim.PushBack({ 0,66,29,32 });
	idleAnim.PushBack({ 0,66,29,32 });*/
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;
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
	shootAnim.PushBack({ 26,67,35,35 });
	shootAnim.PushBack({ 26,67,35,35 });
	shootAnim.PushBack({ 26,67,35,35 });
	shootAnim.PushBack({ 26,67,35,35 });
	shootAnim.loop = true;
	shootAnim.speed = 0.1f;

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
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 150;
	position.y = 170;

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

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (Collision_F != true)
		{
			position.y += speed;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		//only if detected stairs

		position.y -= speed;
		if (currentAnimation != &climbAnim)
		{
		     climbAnim.Reset();
			currentAnimation = &climbAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		if (currentAnimation != &shootAnim)
		{
			shootAnim.Reset();
			currentAnimation = &shootAnim;
		}
		//App->particles->AddParticle(App->particles->rope, position.x, position.y-0, Collider::Type::PLAYER_SHOT);

		LOG("SHOOTING ROPE!")
		Rope* rope = App->ropes->AddRope(App->ropes->rope, position.x, position.y - 370, Collider::Type::ROPE);
		rope->collider->AddListener(this);
		App->audio->PlayFx(laserFx);
		
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_W] != KEY_STATE::KEY_DOWN)
	{
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
			currentAnimation = &idleAnim;
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

			App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneIntro, 60);
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
		

		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		if (c1->type == Collider::Type::BALL && c2->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BALL)
		{
			switch (goingRight)
			{
			case(true):
				App->particles->AddParticle(App->particles->dieRightAnim, position.x, position.y, Collider::Type::NONE, 0);
				break;
			case(false):
				App->particles->AddParticle(App->particles->dieLeftAnim, position.x, position.y, Collider::Type::NONE, 0);
				break;
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
