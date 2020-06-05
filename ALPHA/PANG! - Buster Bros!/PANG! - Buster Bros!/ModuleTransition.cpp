#include "ModuleTransition.h"
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
#include"ModuleFonts.h"
#include <stdio.h>
#include "SDL/include/SDL.h"

ModuleTransition::ModuleTransition(bool startEnabled) : Module(startEnabled)
{

}

ModuleTransition::~ModuleTransition()
{

}

// Load assets
bool ModuleTransition::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->audio->Enable();
	App->audio->Start();
	counter = 0;

	//selection = App->textures->Load("Assets/menuSelection.png");
	bgimg = App->textures->Load("Assets/menu.png");
	App->audio->PlayMusic("Assets/Music/Arcade - 12 - High Score Table.ogg", 1.0f);


	cursor = App->textures->Load("Assets/selectionCursor.png");
	blinkCursor = App->textures->Load("Assets/blinkCursor.png");

	selection.anim.PushBack({ 0,243,21,21 });
	selection.anim.PushBack({ 21,243,21,21 });

	App->scene->levelSelection++;

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

update_status ModuleTransition::Update()
{
	frameCount++;
	if (frameCount % 60 == 0)
	{
		countDown--;
	}
	if (countDown == 0)
	{
		App->fade->FadeToBlack((Module*)App->transition, (Module*)App->scene, 20);
		App->transition->Disable();
	}



	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleTransition::PostUpdate()
{
	// Draw everything --------------------------------------
	
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
	

	

	


	return update_status::UPDATE_CONTINUE;
}

