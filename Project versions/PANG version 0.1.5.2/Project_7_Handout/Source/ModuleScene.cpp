#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleBalls.h"
#include "ModulePlayer.h"

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

	bgTexture = App->textures->Load("Assets/01.png");
	/*SDL_Rect section = &bgTexture;*/
	App->audio->PlayMusic("Assets/Arcade - 01a - Mt. Fuji.ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::FLOOR);

	//First two columns colliders
	App->collisions->AddCollider({ 0, 0,7,300 }, Collider::Type::WALL_A);
	App->collisions->AddCollider({ 377, 0, 7, 300 }, Collider::Type::WALL_D);
	App->collisions->AddCollider({ 0,201,384,8 }, Collider::Type::FLOOR);

	
	//Balls
	App->balls->AddBall(BALL_TYPE::BIG, 150, 25,true);
	/*App->balls->AddBall(BALL_TYPE::MEDIUM, 100, 25);*/
	//App->balls->AddBall(BALL_TYPE::SMALL, 50, 25);
	//App->balls->AddBall(BALL_TYPE::TINY, 35, 25);

	App->player->Enable();
	App->balls->Enable();



	return ret;
}

update_status ModuleScene::Update()
{
	//App->render->camera.x += 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture,0,0,NULL);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->balls->Disable();
	App->textures->CleanUp();
	App->balls->CleanUp();
	App->collisions->CleanUp();
	App->player->CleanUp();


	// TODO 5: Remove All Memory Leaks - no solution here guys ;)

	return true;
}