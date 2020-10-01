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
#include <iostream>
#include <string>
using namespace std;


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
	
	//blinks
	blinkRight.PushBack({ 0,66,25,35 });
	blinkRight.PushBack({ 0,0,0,0 });

	blinkLeft.PushBack({ 84,66,35,35 });
	blinkLeft.PushBack({ 84,66,35,35 });

	blinkRight.PushBack({ 0,0,30,29 });
	blinkRight.PushBack({ 31,0,30,30 });
	blinkRight.PushBack({ 0,0,0,0 });
	blinkRight.PushBack({ 64,0,29,30 });
	blinkRight.PushBack({ 96,0,27,30 });
	blinkRight.PushBack({ 0,0,0,0 });

	blinkLeft.PushBack({ 0,133,30,29 });
	blinkLeft.PushBack({ 31,133,30,30 });
	blinkLeft.PushBack({ 0,0,0,0 });
	blinkLeft.PushBack({ 64,133,29,30 });
	blinkLeft.PushBack({ 96,133,27,30 });
	blinkLeft.PushBack({ 129,133,28,30 });
	blinkLeft.PushBack({ 0,0,0,0 });

	blinkRight.loop = true;
	blinkIdleRight.speed=blinkIdleLeft.speed=blinkLeft.speed=blinkRight.speed = 0.06f;

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
	char scoreLookupTable[] = { "0123456789" };
	scoreFont = App->fonts->Load("Assets/Font.png", lookupTable, 1);
	reducedFont = App->fonts->Load("Assets/score font.png", scoreLookupTable, 1);


	switch (App->scene->levelSelection) //depending on the level set cursos to its pertinent position
	{
	case(1):
		App->balls->ballsLeft = 15;
		break;
	case(2):
		App->balls->ballsLeft = 15;
		break;
	case(3):
		App->balls->ballsLeft = 18;
		break;
	case(4):
		App->balls->ballsLeft = 15;
		break;
	case(5):
		App->balls->ballsLeft = 22;
		break;
	case(6):
		App->balls->ballsLeft = 30; 
		break;
	}


	return ret;
}



update_status ModulePlayer::Update()
{
	/*GamePad& pad = App->input->pads[0];*/
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
		
		
		if (inmuneActivated == true)
		{
			App->particles->AddParticle(App->particles->inmune, position.x, position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::INMUNE);
		}
		
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
		if (App->input->keys[SDL_SCANCODE_4] == KEY_STATE::KEY_DOWN)
		{
		   itemEquipped = ITEM_EQUIPPED::STATIC;
		}
		if (App->input->keys[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN) {
			App->balls->ballsStop = !App->balls->ballsStop;
		}

		if (App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN) {
			lives++;
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN /*|| pad.a == true*/)
		{
			

			LOG("SHOOTING ROPE!");
			switch (itemEquipped)
			{
			case(ITEM_EQUIPPED::NONE):
				//App->particles->AddRope(App->particles->rope, position.x + 9, position.y, Collider::Type::ROPE, 0, PARTICLE_TYPE::ROPE);

				App->ropes->AddRope(App->ropes->rope, position.x + 9, position.y, Collider::Type::ROPE, ROPE_TYPE::ROPE);
				break;
			case(ITEM_EQUIPPED::HOOK):
				/*App->particles->AddRope(App->particles->hook, position.x + 9, position.y, Collider::Type::ROPE, 0, PARTICLE_TYPE::HOOK);*/
				App->ropes->AddRope(App->ropes->hook, position.x + 9, position.y, Collider::Type::ROPE, ROPE_TYPE::HOOK);
				break;
			case(ITEM_EQUIPPED::GUN):
				/*App->particles->AddRope(App->particles->shot, position.x + 9, position.y, Collider::Type::ROPE, 0, PARTICLE_TYPE::SHOT);*/
				App->ropes->AddRope(App->ropes->shot, position.x + 9, position.y, Collider::Type::ROPE, ROPE_TYPE::SHOT);
				break;

			case(ITEM_EQUIPPED::STATIC):
				/*App->particles->AddRope(App->particles->shot, position.x + 9, position.y, Collider::Type::ROPE, 0, PARTICLE_TYPE::SHOT);*/
				App->ropes->AddRope(App->ropes->staticHook, position.x + 9, position.y, Collider::Type::ROPE, ROPE_TYPE::SHOT);
				break;
			}
		}


		

		
	}
	
	
		collider->SetPos(position.x, position.y);

		currentAnimation->Update();

		

		return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::UpdateState()
{
	/*GamePad& pad = App->input->pads[0];*/
	if (playerHitted == true)
	{
		hittedCountDown++;
		if (hittedCountDown > 90)
		{
			playerHitted = false;
				hittedCountDown = 0;
		}
	}
	switch (state)
	{
	case IDLE:
	{
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT ||
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT /*|| pad.l_x < 0.0f || pad.l_x > 0.0f*/)
			ChangeState(state, RUNNING);

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN /*|| pad.a == true*/)
		{ 
			ChangeState(state, SHOOTING);
			shootCountDown = resetCountDown;
		}
			

		// TODO 5: Fill in the transition condition to start climbing
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && canClimb /*|| pad.l_y < 0.0f && canClimb*/)
			ChangeState(state, CLIMBING);

		
		if (destroyed == true) ChangeState(state, DYING);

		

		break;
	}

	case RUNNING:
	{
		if (App->input->keys[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT &&
			App->input->keys[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT /*|| pad.l_x == 0.0f && pad.l_x == 0.0f*/)
		{
			ChangeState(state, IDLE);
			shootCountDown = resetCountDown;	
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN /*|| pad.a == true*/)
		{
			ChangeState(state, SHOOTING);
		}
		//if (App->input->keys[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN)
		//	ChangeState(state, HAMMER_RUNNING);

		// TODO 5: Fill in the transition condition to start climbing
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && canClimb /*|| pad.l_y < 0.0f && canClimb*/)
			ChangeState(state, CLIMBING);

		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && canClimb /*|| pad.l_y < 0.0f && canClimb*/)
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

		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && canClimb /*|| pad.l_y < 0.0f && canClimb*/)
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
			App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT /*|| pad.l_x < 0.0f || pad.l_x > 0.0f*/)
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
			
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && canClimb /*|| pad.l_y < 0.0f && canClimb*/)
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
	/*GamePad& pad = App->input->pads[0];*/
	switch (state)
	{
	case(IDLE):
	{
		/*if (playerHitted == true) {
			switch (goingRight)
			{
			case(true):
				currentAnimation = &blinkIdleRight;
				break;
			case(false):
				currentAnimation = &blinkIdleLeft;
				break;
			}
			
		}*/
		// Nothing to do here :)
		break;
	}
	case(RUNNING):
	{
		/*if (playerHitted == true) {
			switch (goingRight)
			{
			case(true):
				currentAnimation = &blinkRight;
				break;
			case(false):
				currentAnimation = &blinkLeft;
				break;
			}
			
		}*/

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

		if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT /*|| pad.l_y < 0.0f*/)
		{
			--position.y;
			currentAnimation->Update();
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT /*|| pad.l_y > 0.0f*/)
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
					dead_vy = dead_vy + (gravityDead * deltaTime);
					position.y = position.y + (dead_vy * deltaTime) + (gravityDead * (deltaTime * deltaTime));
					position.x = position.x + (dead_vx * deltaTime);

					break;
				case(true):
					currentAnimation = &dieLeftAnim;
					dead_vx = -60;
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
	/*GamePad& pad = App->input->pads[0];*/
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
			App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT /*|| pad.l_x < 0.0f*/)
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

	const char* n1 = {"1"}; const char* n2 = { "2" }; const char* n3 = { "3" };
	const char* n4 = { "4" }; const char* n5 = { "5" }; const char* n6 = { "6" };

	switch (App->scene->levelSelection)
	{

	case(1):
		App->fonts->BlitText(179, 210, scoreFont, t01); App->fonts->BlitText(213, 223, scoreFont, n1);
		break;

	case(2):
		App->fonts->BlitText(170, 210, scoreFont, t02); App->fonts->BlitText(213, 223, scoreFont, n2);
		break;

	case(3):
		App->fonts->BlitText(170, 210, scoreFont, t03); App->fonts->BlitText(213, 223, scoreFont, n3);
		break;

	case(4):
		App->fonts->BlitText(170, 210, scoreFont, t04); App->fonts->BlitText(213, 223, scoreFont, n4);
		break;

	case(5):
		App->fonts->BlitText(170, 210, scoreFont, t05); App->fonts->BlitText(213, 223, scoreFont, n5);
		break;

	case(6):
		App->fonts->BlitText(170, 210, scoreFont, t05); App->fonts->BlitText(213, 223, scoreFont, n6);
		break;
	}

	
	//string score= to_string(number);   
	string time = to_string(App->interfaceElements->countDown);
	char printTime[4] = {};
	for (int i = 0; i<4; i++)
	{
		printTime[i] = time[i];
	}

	App->fonts->BlitText(330, 15, scoreFont, printTime);

	
	//string score= to_string(number);   
	string score = to_string(playerScore);
	char printScore[8] = {};
	for (int i = 0; i < 4; i++)
	{
		printScore[i] = score[i];
	}

	App->fonts->BlitText(80, 211, reducedFont, printScore);

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
					App->particles->DeleteInmune();

					App->particles->AddParticle(App->particles->blinkInmune, 0, 0, Collider::Type::NONE, 0, PARTICLE_TYPE::NONE);
					
					deadCountDown = 0;
				}
				if (lives == 0)
				{
					destroyed = true;
					App->particles->AddParticle(App->particles->blink, 0, 0, Collider::Type::NONE, 0, PARTICLE_TYPE::NONE);
					App->interfaceElements->AddElement(App->interfaceElements->gameOver, 130, 100, INTERFACE_ELEMENT_TYPE::UI, 70);
				}

				playerHitted = true;
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
//void ModulePlayer::DebugDrawGamepadInfo()
//{
//	GamePad& pad = App->input->pads[0];
//
//	sprintf_s(scoreText, 150, "pad 0 %s, press 1/2/3 for rumble", (pad.enabled) ? "plugged" : "not detected");
//	App->fonts->BlitText(5, 10, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "buttons %s %s %s %s %s %s %s %s %s %s %s",
//		(pad.a) ? "a" : "",
//		(pad.b) ? "b" : "",
//		(pad.x) ? "x" : "",
//		(pad.y) ? "y" : "",
//		(pad.start) ? "start" : "",
//		(pad.back) ? "back" : "",
//		(pad.guide) ? "guide" : "",
//		(pad.l1) ? "lb" : "",
//		(pad.r1) ? "rb" : "",
//		(pad.l3) ? "l3" : "",
//		(pad.r3) ? "r3" : ""
//		);
//	App->fonts->BlitText(5, 20, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "dpad %s %s %s %s",
//		(pad.up) ? "up" : "",
//		(pad.down) ? "down" : "",
//		(pad.left) ? "left" : "",
//		(pad.right) ? "right" : ""
//		);
//	App->fonts->BlitText(5, 30, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "left trigger  %0.2f", pad.l2);
//	App->fonts->BlitText(5, 40, scoreFont, scoreText);
//	sprintf_s(scoreText, 150, "right trigger %0.2f", pad.r2);
//	App->fonts->BlitText(5, 50, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "left thumb    %.2fx, %0.2fy", pad.l_x, pad.l_y);
//	App->fonts->BlitText(5, 60, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.l_dz);
//	App->fonts->BlitText(5, 70, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "right thumb   %.2fx, %0.2fy", pad.r_x, pad.r_y);
//	App->fonts->BlitText(5, 80, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.r_dz);
//	App->fonts->BlitText(5, 90, scoreFont, scoreText);
//}


