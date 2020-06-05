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
#include "ModuleFonts.h"
#include <stdio.h>
#include "SDL/include/SDL.h"
#include "ModuleScene.h"
#include "ModuleInterface.h"


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
	climbAnim.PushBack({ 25,32,23,30 });
	climbAnim.PushBack({ 51,32,23,30 });
	climbAnim.PushBack({ 78,32,23,30 });
	climbAnim.loop = true;
	climbAnim.speed = 0.1f;
	//Shoot
	//shootRightAnim.PushBack({ 0,67,25,31 });
	shootRightAnim.PushBack({ 26,67,30,35 });
	shootRightAnim.PushBack({ 0,67,25,31 });
	shootRightAnim.loop = false;
	shootRightAnim.speed = 0.00001f;

	//shootLeftAnim.PushBack({ 84,67,27,34 });
	shootLeftAnim.PushBack({ 56,67,27,34 });
	shootLeftAnim.PushBack({ 84,67,27,34 });
	shootLeftAnim.loop = shootRightAnim.loop;
	shootLeftAnim.speed = shootRightAnim.speed = 0.05f;
	
	dieRightAnim.PushBack({ 5,104,39,27 });
	dieLeftAnim.PushBack({ 44,104,39,27 });
	dieRightAnim.loop = true;
	dieLeftAnim.loop = true;
	dieRightAnim.speed = 0.1f;
	dieLeftAnim.speed = 0.1f;

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


bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/SpriteSheet.png");
	currentAnimation = &idleRightAnim;

	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 250;
	position.y = 170;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 22, 30 }, Collider::Type::PLAYER, this);
	char lookupTable[] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	scoreFont = App->fonts->Load("Assets/Font.png", lookupTable, 1);

	if (App->score >= 7500) {
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->win, 60);

	}

	return ret;
}



update_status ModulePlayer::Update()
{
	UpdateState();
	UpdateLogic();

	Collision_A = false;
	Collision_D = false;
	Collision_F = false;
	canClimb=false;

	if (isInmune == true) inmuneCountDown--;

	//god mode
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		//isInmune = true;

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

	if (destroyed == false) {

		position.y += gravity;
		
		if (isInmune == true && inmuneActivated == false) {

			//it creates a lot of particles
			App->particles->AddParticle(App->particles->inmune, position.x, position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::INMUNE);
			inmuneActivated = true;
			inmuneCountDown = resetInmuneCountDown;

		}
		if (inmuneCountDown <= 0)
		{
			isInmune = false; inmuneActivated = false;
		}
		//EQUIP MANUALLY
		if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
		{
			itemEquipped = ITEM_EQUIPPED::NONE;
		}
		if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
		{
			itemEquipped = ITEM_EQUIPPED::HOOK;
		}
		if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)
		{
			itemEquipped = ITEM_EQUIPPED::GUN;
		}
		if (App->input->keys[SDL_SCANCODE_5] == KEY_STATE::KEY_DOWN)
		{
			isInmune = true; inmuneActivated = true;
		}




		//if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		//{

		//	/*if (Collision_A != true)
		//	{
		//		position.x -= speed;
		//	}

		//	if (currentAnimation != &leftAnim)
		//	{
		//		leftAnim.Reset();
		//		currentAnimation = &leftAnim;
		//	}*/
		//	if (goingRight != false)
		//		goingRight = false;

		//}

		//if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		//{

		//	isMovingAt.x = 3;
		//	if (Collision_D != true)
		//	{
		//		position.x += speed;
		//	}
		//	if (currentAnimation != &rightAnim)
		//	{
		//		rightAnim.Reset();
		//		currentAnimation = &rightAnim;
		//	}
		//	if (goingRight != true)
		//		goingRight = true;

		//}






		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			/*if (currentAnimation != &shootRightAnim)
			{
				shootRightAnim.Reset();
				currentAnimation = &shootRightAnim;
			}*/
			/*	App->particles->AddParticle(App->particles->rope, position.x, position.y-0, Collider::Type::ROPE);*/


			/*switch (goingRight)
			{
			case(false):
				currentAnimation = &idleLeftAnim;
				break;
			case(true):
				currentAnimation = &idleRightAnim;
				break;
			}*/

			LOG("SHOOTING ROPE!");
			switch (itemEquipped)
			{
			case(ITEM_EQUIPPED::NONE):
				//App->particles->AddRope(App->particles->rope, position.x + 9, position.y, Collider::Type::ROPE, 0, PARTICLE_TYPE::ROPE);

				App->ropes->AddRope(App->ropes->rope, position.x+9, position.y, Collider::Type::ROPE, ROPE_TYPE::ROPE);
				break;
			case(ITEM_EQUIPPED::HOOK):
				/*App->particles->AddRope(App->particles->hook, position.x + 9, position.y, Collider::Type::ROPE, 0, PARTICLE_TYPE::HOOK);*/
				App->ropes->AddRope(App->ropes->hook, position.x + 9, position.y, Collider::Type::ROPE, ROPE_TYPE::HOOK);
				break;
			case(ITEM_EQUIPPED::GUN):
				/*App->particles->AddRope(App->particles->shot, position.x + 9, position.y, Collider::Type::ROPE, 0, PARTICLE_TYPE::SHOT);*/
				App->ropes->AddRope(App->ropes->shot, position.x + 9, position.y, Collider::Type::ROPE, ROPE_TYPE::SHOT);
				break;
			}



		}

		// If no up/down movement detected, set the current animation back to idle
		/*if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE)
		{


			if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)

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

		if (App->input->keys[SDL_SCANCODE_G] != KEY_STATE::KEY_DOWN)
		{
			App->collisions->DebugDraw();
		}*/
	}
	
	if (destroyed == true) {
		if (bounce == false) {
			//SDL_Delay(200);
			switch (goingRight) {
			case(false):
				currentAnimation = &dieRightAnim;
				dead_vx = 125;
				dead_vy = dead_vy + (gravityDead * deltaTime);
				position.y = position.y + (dead_vy * deltaTime) + (gravityDead * (deltaTime * deltaTime));
				position.x = position.x + (dead_vx * deltaTime);

				break;
			case(true):
				currentAnimation = &dieLeftAnim;
				dead_vx = -125;
				dead_vy = dead_vy + (gravityDead * deltaTime);
				position.y = position.y + (dead_vy * deltaTime) + (gravityDead * (deltaTime * deltaTime));
				position.x = position.x + (dead_vx * deltaTime);

				break;
			}


		}
		if (bounce == true) {
			dead_vy = dead_vy + (gravityDead * deltaTime);
			position.y = position.y + (dead_vy * deltaTime) + (gravityDead * (deltaTime * deltaTime));
			position.x = position.x + (dead_vx * deltaTime);

		}

		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->lose, 300);
		
	}
		collider->SetPos(position.x, position.y);

		currentAnimation->Update();

		/*Collision_A = false;
		Collision_D = false;
		Collision_F = false;*/

		return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::UpdateState()
{
	switch (state)
	{
	case IDLE:
	{
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN ||
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
			ChangeState(state, RUNNING);

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{ 
			ChangeState(state, SHOOTING);
			shootCountDown = resetCountDown;
		}
			

		// TODO 5: Fill in the transition condition to start climbing
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && canClimb)
			ChangeState(state, CLIMBING);

		// TODO 0: Notice how we are changing into HAMMER_IDLE state when pressing H
		/*if (App->input->keys[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN)
			ChangeState(state, HAMMER_IDLE);*/
		if (destroyed == true) ChangeState(state, DYING);

		break;
	}

	case RUNNING:
	{
		if (App->input->keys[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT)
		{
			ChangeState(state, IDLE);
			shootCountDown = resetCountDown;	
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			ChangeState(state, SHOOTING);
		}
		//if (App->input->keys[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN)
		//	ChangeState(state, HAMMER_RUNNING);

		// TODO 5: Fill in the transition condition to start climbing
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && canClimb)
			ChangeState(state, CLIMBING);

		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && canClimb)
			ChangeState(state, CLIMBING);

		break;
	}

	case CLIMBING:
	{
		/*if (jumpCountdown <= 0)
		{
			jumpCountdown = 30;*/
		/*if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT ||
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
			ChangeState(state, CLIMBING);*/
		//else
		if(canClimb==false)
			ChangeState(state, IDLE);

		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && canClimb)
			ChangeState(state, CLIMBING);

		break;
	}

	case SHOOTING:
	{

		// TODO 2: Check the condition to go back to IDLE state. If fulfilled, change the state.
		
		/*--shootCountDown;*/
		// TODO 3: Add all the logic behind HAMMER_RUN state
		// TODO 3.1: Check the condition. If fulfilled, change the state to HAMMER_RUN
		
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN ||
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			
			if (shootCountDown <= 0)
			{
				ChangeState(state, RUNNING);
			}
			
		}
		if (shootCountDown <= 0)
		{
			ChangeState(state, IDLE);
		}
			
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && canClimb)
			ChangeState(state, CLIMBING);

		break;
	case DYING:
	{
		

		break;
	}
	}
	}
}

void ModulePlayer::UpdateLogic()
{
	switch (state)
	{
	case(IDLE):
	{
		// Nothing to do here :)
		break;
	}
	case(RUNNING):
	{
		if (Collision_D == false && goingRight) 
			 position.x += speed;

	 else if(Collision_A==false && !goingRight)
			position.x += (speed * (-1));

	currentAnimation->Update();
		
		break;
	}
	case(CLIMBING):
	{
		// TODO 5: Update climbing logic - Only move when the player is pressing "W"

		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT)
		{
			--position.y;
			currentAnimation->Update();
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT)
		{
			++position.y;
			currentAnimation->Update();
		}

		break;
	}

	case(SHOOTING):
	{
		--shootCountDown;
		currentAnimation->Update();
		break;
	}
	case(DYING):
	{
		if (bounce == false) {
			//SDL_Delay(200);
			switch (goingRight) {
			case(false):
				currentAnimation = &dieRightAnim;
				dead_vx = 125;
				dead_vy = dead_vy + (gravityDead * deltaTime);
				position.y = position.y + (dead_vy * deltaTime) + (gravityDead * (deltaTime * deltaTime));
				position.x = position.x + (dead_vx * deltaTime);

				break;
			case(true):
				currentAnimation = &dieLeftAnim;
				dead_vx = -125;
				dead_vy = dead_vy + (gravityDead * deltaTime);
				position.y = position.y + (dead_vy * deltaTime) + (gravityDead * (deltaTime * deltaTime));
				position.x = position.x + (dead_vx * deltaTime);

				break;
			}


		}
		if (bounce == true) {
			dead_vy = dead_vy + (gravityDead * deltaTime);
			position.y = position.y + (dead_vy * deltaTime) + (gravityDead * (deltaTime * deltaTime));
			position.x = position.x + (dead_vx * deltaTime);

		}
		break;
	}
	}

	// Warning: dirty workaround for this class for fast checking
	// This should be avoided!!
	//canClimb = App->sceneLevel_1->CanPlayerClimb();

	// Simply updating the collider position to match our current position
	collider->SetPos(position.x + 2, position.y + 14);
}

void ModulePlayer::ChangeState(PLAYER_STATE previousState, PLAYER_STATE newState)
{
	switch (newState)
	{
	case(IDLE):
	{
		currentAnimation = &(goingRight== false ? idleLeftAnim : idleRightAnim);
		break;
	}
	case(RUNNING):
	{
		
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN ||
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
			goingRight=false;
		else
			goingRight=true;
		currentAnimation = &(goingRight == false ? leftAnim : rightAnim);
		break;
	}
	case(CLIMBING):
	{
		currentAnimation = &climbAnim;
		break;
	}
	case(SHOOTING):
	{
		// TODO 1: Change the current animation to match the new state (very similar to IDLE case)
		currentAnimation = &(goingRight == false ? shootLeftAnim : shootRightAnim);
		break;
	}
	case(DYING):
	{
		currentAnimation = &(goingRight == false ? dieLeftAnim : dieRightAnim);
		break;
	}

	}

	state = newState;
}



update_status ModulePlayer::PostUpdate()
{
	deadCountDown++;
	
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
	
		App->render->Blit(texture, position.x, position.y, &rect);
	
	
	/*sprintf_s(scoreText, 10, "%7d", App->score);*/
	
	/*App->fonts->BlitText(150, 215, scoreFont, scoreText);*/
	const char* insert = { "INSERT" };
	const char* coin = { "COIN" };

	App->fonts->BlitText(260, 225, scoreFont, insert); App->fonts->BlitText(325, 225, scoreFont, coin);

	const char* t01= { "FUJI" };
	const char* t02 = { "KEIRIN" };
	const char* t03 = { "KEIRIN" };
	const char* t04 = { "KEIRIN" };
	const char* t05 = { "KEIRIN" };
	const char* t06 = { "KEIRIN" };
	switch (App->scene->levelSelection)
	{

	case(1):
		App->fonts->BlitText(130, 30, scoreFont, t01);
		break;

	case(2):
		App->fonts->BlitText(130, 130, scoreFont, t02);
		break;

	case(3):
		App->fonts->BlitText(130, 30, scoreFont, t03);
		break;

	case(4):
		App->fonts->BlitText(130, 30, scoreFont, t04);
		break;

	case(5):
		App->fonts->BlitText(130, 30, scoreFont, t05);
		break;

	case(6):
		App->fonts->BlitText(170, 210, scoreFont, t05);
		break;
	}

	return update_status::UPDATE_CONTINUE;
}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	Collision_A = false;
	Collision_D = false;
	Collision_F = false;

	if (c1 == collider && destroyed == true) {
		if (bounce == false) {
			if (c2->type == Collider::Type::WALL_D) {
				dead_vx = -(dead_vx);
				bounce = true;
			}
			if (c2->type == Collider::Type::WALL_A) {
				dead_vx = -(dead_vx);
				bounce = true;
			}
			if (c2->type == Collider::Type::FLOOR) {
				dead_vy = -200;
				bounce = true;
			}
		}
	}
	if (c1 == collider && destroyed == false)
	{
		/*App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);*/

		
		if (deadCountDown >= 60)
		{
			
			if (c2->type == Collider::Type::BALL)
			{
				destroyed = false;
				//The problem is the collision is tetected more than once, so number of lives decreases drastically
				if (isInmune == false)
				{
					lives--;
					deadCountDown = 0;
				}
				if (isInmune == true) {
					isInmune = false; inmuneActivated = false;
					deadCountDown = 0;
				}
				if (lives == 0)
				{
					destroyed = true;
					App->particles->AddParticle(App->particles->blink, 0, 0, Collider::Type::NONE, 0, PARTICLE_TYPE::NONE);
					App->interfaceElements->AddElement(App->interfaceElements->gameOver, 130, 100, INTERFACE_ELEMENT_TYPE::UI, 70);
				}


				App->audio->PlayFx(explosionFx);


			}
		}


		if (c2->type == Collider::Type::WALL_A)
		{
			Collision_A = true;
		}
		if (c2->type == Collider::Type::WALL_D)
		{
			Collision_D = true;
		}
		if (c2->type == Collider::Type::FLOOR)
		{
			Collision_F = true;
			gravity = 0; 
			position.y--;
		}
		if (c2->type == Collider::Type::STAIRS)
		{
			canClimb = true;
			//climb stairs
			//if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
			//{
			//	position.y -= speed;
			//	if (currentAnimation != &climbAnim)
			//	{
			//		climbAnim.Reset();
			//		currentAnimation = &climbAnim;
			//	}
			//	//position.y++;
			//}
			//if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
			//{
			//	position.y += speed;
			//	if (currentAnimation != &climbAnim)
			//	{
			//		climbAnim.Reset();
			//		currentAnimation = &climbAnim;
			//	}
			//	position.y--;
			//}
		}
		if (c2->type == Collider::Type::CORNICE)
		{
			gravity = newGravity;
		}
	
		
	}

	if (c1->type == Collider::Type::ROPE && c2->type == Collider::Type::BALL)
	{
		/*App->score += 500;*/
	}

}


