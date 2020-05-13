#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "ModuleBalls.h"
#include "ModulePlayer.h"
#include "ModuleInterface.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->audio->Enable();
	App->audio->Start();

	bgTexture_01 = App->textures->Load("Assets/01.png");
	bgTexture_02 = App->textures->Load("Assets/02.png");
	bgTexture_03 = App->textures->Load("Assets/03.png");
	bgTexture_04 = App->textures->Load("Assets/04.png");
	bgTexture_05 = App->textures->Load("Assets/05.png");
	bgTexture_06 = App->textures->Load("Assets/06.png");

	blockTexture_01 = App->textures->Load("Assets/bk_01.png");
	blockTexture_02 = App->textures->Load("Assets/bk_02.png");
	blockTexture_03 = App->textures->Load("Assets/bk_03.png");
	blockTexture_04 = App->textures->Load("Assets/bk_04.png");
	blockTexture_05 = App->textures->Load("Assets/bk_05.png");
	blockTexture_06 = App->textures->Load("Assets/bk_06.png");


	/*SDL_Rect section = &bgTexture;*/
	//App->audio->PlayMusic("Assets/Arcade - 01a - Mt. Fuji.ogg", 1.0f);
	//Bottomside collider
	/*App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::FLOOR);*/

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0,7,200 }, Collider::Type::WALL_A);
	App->collisions->AddCollider({ 377, 0, 7, 200 }, Collider::Type::WALL_D);
	App->collisions->AddCollider({ 0,200,384,8 }, Collider::Type::FLOOR);
	App->collisions->AddCollider({ 0,0,384,8 }, Collider::Type::TOP);
	// each ñevel specific colliders
	switch (levelSelection)
	{
	case(2):
		App->collisions->AddCollider({ 70,30,200,80 }, Collider::Type::FLOOR);
		break;
	case(3):
		App->collisions->AddCollider({ 130,70,3,200 }, Collider::Type::FLOOR);
		break;
	}
	//Balls
	App->balls->AddBall(BALL_TYPE::BIG, 150, 25,true);
	//App->balls->AddBall(BALL_TYPE::BIG, 70, 25, false);
	//App->balls->AddBall(BALL_TYPE::MEDIUM, 150, 25,true);
	//App->balls->AddBall(BALL_TYPE::SMALL, 150, 25,true);
	//App->balls->AddBall(BALL_TYPE::TINY, 150, 25,true);

	App->player->Enable();
	App->balls->Enable();

	App->textures->Enable();

	App->balls->Enable();

	App->collisions->Enable();

	App->interfaceElements->Enable();



	return ret;
}

update_status ModuleScene::Update()
{


	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	

	// Draw everything --------------------------------------
	switch (levelSelection)
	{
	
	case(1):
		App->render->Blit(bgTexture_01, 0, 0, NULL);

		
		break;

	case(2):
		App->render->Blit(bgTexture_02, 0, 0, NULL);

		App->render->Blit(blockTexture_02, 0, 0, NULL);
		break;

	case(3):
		App->render->Blit(bgTexture_03, 0, 0, NULL);

		App->render->Blit(blockTexture_03, 0, 0, NULL);
		break;

	case(4):
		App->render->Blit(bgTexture_04, 0, 0, NULL);

		App->render->Blit(blockTexture_04, 0, 0, NULL);
		break;

	case(5):
		App->render->Blit(bgTexture_05, 0, 0, NULL);

		App->render->Blit(blockTexture_05, 0, 0, NULL);
		break;

	case(6):
		App->render->Blit(bgTexture_06, 0, 0, NULL);

		App->render->Blit(blockTexture_06, 0, 0, NULL);
		break;
	}
	
	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module

	App->player->CleanUp();
	App->player->Disable();
	

	//App->textures->CleanUp();
	//App->textures->Disable();

	App->balls->CleanUp();
	App->balls->Disable();

	App->collisions->CleanUp();
	App->collisions->Disable();

	App->interfaceElements->CleanUp();
	App->interfaceElements->Disable();

	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}