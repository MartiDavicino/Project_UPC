#include "ModuleSceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

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
	counter = 0;

	bgtitle = App->textures->Load("Assets/Title.png");
	bgimg = App->textures->Load("Assets/cutrisimo.png");
	App->audio->PlayMusic("Assets/Music/Arcade - 12 - High Score Table.ogg", 1.0f);
	//if (App->player->lives < 3) {
	//	App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	//}
	//if (App->player->lives = 0) {
	//	App->fade->FadeToBlack(this, (Module*)App->lose, 90);
	//}

	/*App->render->camera.x = 0;
	App->render->camera.y = 0;*/

	return ret;	

}

update_status ModuleSceneIntro::Update()
{
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		counter++;
		
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	if (counter == 0) {
		App->render->Blit(bgimg, 0, 0, NULL);
	}
	if (counter == 1) {
		App->render->Blit(bgtitle, 0, 0, NULL);
	}
	if (counter == 2) {
		App->fade->FadeToBlack((Module*)App->sceneIntro, (Module*)App->menu, 60);

	}

	return update_status::UPDATE_CONTINUE;
}