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
	LOG("Loading background assets");

	bool ret = true;

	bgtitle = App->textures->Load("Assets/Win.png");
	App->audio->PlayMusic("Assets/Music/Arcade - 01e - Continue.ogg", 1.0f);

	/*App->render->camera.x = 0;
	App->render->camera.y = 0;*/

	return ret;

}

update_status ModuleWin::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
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