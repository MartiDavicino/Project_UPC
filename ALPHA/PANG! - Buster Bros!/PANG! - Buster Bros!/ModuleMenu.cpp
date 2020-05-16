#include "ModuleMenu.h"
#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "InterfaceElement.h"
#include "SDL/include/SDL_scancode.h"


ModuleMenu::ModuleMenu(bool startEnabled) : Module(startEnabled)
{

}

ModuleMenu::~ModuleMenu()
{

}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->audio->Enable();
	App->audio->Start();
	counter = 0;

	//selection = App->textures->Load("Assets/menuSelection.png");
	bgimg = App->textures->Load("Assets/menu.png");
	App->audio->PlayMusic("Assets/Music/Arcade - 12 - High Score Table.ogg", 1.0f);

	texture = App->textures->Load("Assets,menuSelection");

	selection.anim.PushBack({ 0,0,21,21 });
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

update_status ModuleMenu::Update()
{
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
	{
		App->scene->levelSelection++;
	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
	{
		App->scene->levelSelection--;

	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		counter++;

	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	if (counter == 0) {
		App->render->Blit(bgimg, 0, 0, NULL);

		switch (App->scene->levelSelection) //depending on the level set cursos to its pertinent position
		{
		case(1):
			break;
		case(2):
			break;
		case(3):
			break;
		case(4):
			break;
		case(5):
			break;
		case(6):
			break;
		}
	}
	if (counter == 1) {
		//App->render->Blit(selection, 0, 0, NULL);
	}
	if (counter == 2) {
		App->fade->FadeToBlack((Module*)App->sceneIntro, (Module*)App->scene, 60);

	}

	return update_status::UPDATE_CONTINUE;
}