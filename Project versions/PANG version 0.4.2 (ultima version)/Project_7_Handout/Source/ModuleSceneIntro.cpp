#include "ModuleSceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"


ModuleSceneIntro::ModuleSceneIntro(bool startEnabled) : Module(startEnabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{

}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->audio->Enable();
	App->audio->Start();

	bgtitle = App->textures->Load("Assets/Title.png");
	App->audio->PlayMusic("Assets/Music/Arcade - 12 - High Score Table.ogg", 1.0f);

	/*App->render->camera.x = 0;
	App->render->camera.y = 0;*/

	return ret;	

}

update_status ModuleSceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgtitle, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}