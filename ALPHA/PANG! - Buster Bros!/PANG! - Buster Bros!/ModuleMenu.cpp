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
#include "ModuleInterface.h"
#include <stdio.h>
#include "SDL/include/SDL.h"

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
	

	levelFX = App->audio->LoadFx("Assets/level selection.wav");
	planeFX = App->audio->LoadFx("Assets/[FX]-Plane movement.wav");

	

	cursor = App->textures->Load("Assets/selectionCursor.png");
	blinkCursor = App->textures->Load("Assets/blinkCursor.png");

	selection.anim.PushBack({ 0,243,21,21 });
	selection.anim.PushBack({ 21,243,21,21 });

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
	count++;
	if (count > 120)
	{
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
		{
			if (App->scene->levelSelection < 6)
			{
				App->audio->PlayFx(levelFX, 0);
				App->scene->levelSelection++;
			}
		}


		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
		{
			if (App->scene->levelSelection > 1)
			{
				App->audio->PlayFx(levelFX, 0);
				App->scene->levelSelection--;
			}
		}
	}

	App->audio->PlayMusic("Assets/Music/intro.ogg", 1.0f);
	App->audio->PlayMusic("Assets/Music/intro.wav", 1.0f);


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
			App->render->Blit(blinkCursor, 337, 78, NULL);
			App->render->Blit(cursor, 337, 78, NULL);

			break;
		case(2):
			App->render->Blit(cursor, 297, 78, NULL);
			break;
		case(3):
			App->render->Blit(cursor, 281, 115, NULL);
			break;
		case(4):
			App->render->Blit(cursor, 297, 115, NULL);
			break;
		case(5):
			App->render->Blit(cursor, 326, 185, NULL);
			break;
		case(6):
			App->render->Blit(cursor, 261, 110, NULL);
			break;
		}

		LOG("Level %d prepared to be loaded", App->scene->levelSelection);
	}

	if (count > 120)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			LOG("Level %d loaded", App->scene->levelSelection);
			App->audio->PlayFx(planeFX, 0);
			App->fade->FadeToBlack((Module*)App->sceneIntro, (Module*)App->scene, 60);
			App->menu->Disable();
		}
	}

	//draw all elements
	for (uint i = 0; i < MAX_ACTIVE_SELECTIONS; ++i)
	{
		InterfaceElement* selection = selectionCursor[i];

		if (selection != nullptr && selection->display == true)
		{
			//App->render->Blit(texture, element->position.x, element->position.y, 0);
			//&(element->anim.GetCurrentFrame())
			App->render->Blit(texture, selection->position.x, selection->position.y, &(selection->anim.GetCurrentFrame()));


		}
		else if (selection != nullptr && selection->display == false)
		{
			delete selection;
			selectionCursor[i] = nullptr;
		}
	}


	return update_status::UPDATE_CONTINUE;
}

void ModuleMenu::Selection(const InterfaceElement& element, int x, int y)
{
	for (uint i = 0; i < MAX_ACTIVE_SELECTIONS; ++i)
	{
		//Finding an empty slot for a new element
		if (selectionCursor[i] == nullptr)
		{
			InterfaceElement* e = new InterfaceElement(element);

			//p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			e->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			e->position.y = y;

			e->speed.y = -0.5f;


			e->display = true;

			selectionCursor[i] = e;
			break;
		}
	}
}