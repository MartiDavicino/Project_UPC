#include "ModuleLose.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"


ModuleLose::ModuleLose(bool startEnabled) : Module(startEnabled)
{

}

ModuleLose::~ModuleLose()
{

}

// Load assets
bool ModuleLose::Start()
{
		LOG("Loading background assets");

	bool ret = true;

	bgtitle = App->textures->Load("Assets/game over.png");
	//App->audio->PlayMusic("Assets/Music/Arcade - 01f - Game Over.ogg", 1.0f);
	loseMusic = App->audio->LoadFx("Assets/Arcade - 01f - Game Over.ogg");
	App->audio->PlayFx(loseMusic, 0);

	/*App->render->camera.x = 0;
	App->render->camera.y = 0;*/

	return ret;

}

update_status ModuleLose::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->player->lives = 1;
		App->player->destroyed = false;
		App->fade->FadeToBlack((Module*)App->lose, (Module*)App->sceneIntro, 60);
		
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleLose::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgtitle, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}