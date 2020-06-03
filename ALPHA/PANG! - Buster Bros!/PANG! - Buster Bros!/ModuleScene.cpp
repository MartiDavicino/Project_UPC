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
	App->collisions->AddCollider({ 0,201,384,7 }, Collider::Type::FLOOR);
	App->collisions->AddCollider({ 0,0,384,7 }, Collider::Type::TOP);

	lvlLoading(tiles_01);

	// each level specific colliders
	
		switch (levelSelection)
		{
		case(2):
			App->collisions->AddCollider({ 72,80,31,3 }, Collider::Type::FLOOR);
			App->collisions->AddCollider({ 72,84,31,3 }, Collider::Type::TOP);

			App->collisions->AddCollider({ 177,80,31,3 }, Collider::Type::FLOOR);
			App->collisions->AddCollider({ 177,84,31,3 }, Collider::Type::TOP);

			App->collisions->AddCollider({ 281,80,31,3 }, Collider::Type::FLOOR);
			App->collisions->AddCollider({ 281,84,31,3 }, Collider::Type::TOP);

			App->collisions->AddCollider({ 177,129,31,3 }, Collider::Type::FLOOR);
			App->collisions->AddCollider({ 177,133,31,3 }, Collider::Type::TOP);
	

			break;
		case(3):
			App->collisions->AddCollider({ 96,56,3,47 }, Collider::Type::WALL_A); //left
			App->collisions->AddCollider({ 100,56,3,47 }, Collider::Type::WALL_D); //right

			App->collisions->AddCollider({ 192,56,3,23 }, Collider::Type::WALL_A); //left
			App->collisions->AddCollider({ 196,56,3,23 }, Collider::Type::WALL_D);

			App->collisions->AddCollider({ 293,56,3,47 }, Collider::Type::WALL_A); //left
			App->collisions->AddCollider({ 293,56,3,47 }, Collider::Type::WALL_D);
	
			break;

		case(4):
			App->collisions->AddCollider({ 160,80,64,3 }, Collider::Type::FLOOR);
			App->collisions->AddCollider({ 160,84,64,3 }, Collider::Type::TOP);


			break;
		case(5): //161 153
			App->collisions->AddCollider({ 180,153,3,20 }, Collider::Type::STAIRS);
			App->collisions->AddCollider({ 201,153,3,20 }, Collider::Type::STAIRS);

			App->collisions->AddCollider({ 184,153,16,3 }, Collider::Type::FLOOR);

			App->collisions->AddCollider({ 195,153,5,43 }, Collider::Type::WALL_A);
			App->collisions->AddCollider({ 183,153,5,43 }, Collider::Type::WALL_D);

			App->collisions->AddCollider({ 128,140,10,10 }, Collider::Type::CORNICE);
			App->collisions->AddCollider({ 246,140,10,10 }, Collider::Type::CORNICE);


			break;
		case(6):
			App->collisions->AddCollider({ 80,64,15,3 }, Collider::Type::FLOOR);
			App->collisions->AddCollider({ 80,68,15,3 }, Collider::Type::TOP);

			App->collisions->AddCollider({ 184,64,15,3 }, Collider::Type::FLOOR);
			App->collisions->AddCollider({ 184,68,15,3 }, Collider::Type::TOP);

			App->collisions->AddCollider({ 296,64,15,3 }, Collider::Type::FLOOR);
			App->collisions->AddCollider({ 296,68,15,3 }, Collider::Type::TOP);
	


		}

	//Balls
	App->balls->AddBall(BALL_TYPE::BIG, 25, 25,true);
	

	App->player->Enable();
	App->balls->Enable();

	App->textures->Enable();

	App->balls->Enable();

	App->collisions->Enable();

	App->interfaceElements->Enable();



	return ret;
}

void ModuleScene::lvlLoading(int tiles[MAXT_Y][MAXT_X]) {

	for (int y = 0; y < MAXT_Y; y++) {
		for (int x = 0; x < MAXT_X; x++) {
			if (tiles[y][x] == 1) {

			}
			if (tiles[y][x] == 2) {

			}
			if (tiles[y][x] == 3) {

			}
			if (tiles[y][x] == 4) {

			}
			if (tiles[y][x] == 0) {
				LOG("EMPTY TILE")

			}


		}
	}
}

void LvlChange(int(&lvlA)[MAXT_Y][MAXT_X], int lvlB[MAXT_Y][MAXT_X]) {
	for (int a = 0; a < MAXT_Y + 1; ++a) {

		for (int b = 0; b < MAXT_X + 1; ++b) {

			lvlA[MAXT_Y][MAXT_X] = lvlB[MAXT_Y][MAXT_X];

		}
	}
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