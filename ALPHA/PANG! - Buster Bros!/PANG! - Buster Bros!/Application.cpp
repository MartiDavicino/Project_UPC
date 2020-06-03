#include "Application.h"


#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleBalls.h"
#include "ModuleRopes.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleScene.h"
#include "ModuleWin.h"
#include "ModuleLose.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInterface.h"
#include "ModuleFonts.h"
#include "ModuleMenu.h"
#include "ModuleTransition.h"


Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = sceneIntro = new ModuleSceneIntro(true);
	modules[5] = scene = new ModuleScene(false);
	modules[6] = menu = new ModuleMenu(false);
	modules[7] = transition = new ModuleTransition(false);
	modules[8] = win = new ModuleWin(false);
	modules[9] = lose = new ModuleLose(false);

	modules[15] = ropes = new ModuleRopes(true);
	modules[11] = player = new ModulePlayer(false);

	modules[12] = interfaceElements = new ModuleInterface(false);
	modules[13] = balls = new ModuleBalls(false);

	modules[14] = fade = new ModuleFadeToBlack(true);
	modules[17] = fonts = new ModuleFonts(true);

	modules[16] = collisions = new ModuleCollisions(true);


	

	modules[10] = particles = new ModuleParticles(true);
	modules[18] = render = new ModuleRender(true);

	
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	//By now we will consider that all modules are always active
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;



	return ret;
}

update_status Application::Win() {
	return update_status::UPDATE_STOP;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;


	return ret;
}