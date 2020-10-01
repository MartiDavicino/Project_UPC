#include "ModuleWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"


ModuleWin::ModuleWin(bool startEnabled) : Module(startEnabled)
{

}

ModuleWin::~ModuleWin()
{

}

// Load assets
bool ModuleWin::Start()
{
	App->audio->Enable();
	App->audio->Start();

	LOG("Loading background assets");

	bool ret = true;

	bgtitle = App->textures->Load("Assets/Win.png");
	App->audio->PlayMusic("Assets/Music/Arcade - 11 - The End", 1.0f);

	winMusic = App->audio->LoadFx("Assets/Arcade - 11 - The End.ogg");

	App->audio->PlayFx(winMusic, 0);

	/*App->render->camera.x = 0;
	App->render->camera.y = 0;*/

	App->audio->PlayFx(winMusic, 0);

	return ret;

}

update_status ModuleWin::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->Win();
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleWin::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgtitle, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}