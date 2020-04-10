#include "Application.h"
#include "Module.h"
#include "Dummy.h"
#include "DummyEsc.h"

Application::Application()
{
	modules[0] = new ModuleDummy();

	// TODO 7: Create your new module "DummyESC".
	// It should check if the player hits ESC key. Use _kbhit() and _getch().
	modules[1] = new ModuleDummyESC();
}

// INIT all modules
bool Application::Init()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		modules[i]->Init();

	}

	// TODO 5: Make sure that App exits correctly if Init/PreUpdate/Update/PostUpdate/CleanUp return exit

	return true;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;
	// TODO 2: Make sure all modules receive its update
	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
	{
		ret = modules[i]->PreUpdate();

	}

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
	{
		ret = modules[i]->Update();

	}

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
	{
		ret = modules[i]->PostUpdate();

	}

	// TODO 4: Add PreUpdate and PostUpdate calls

	// TODO 5: Make sure that App exits correctly if Init/PreUpdate/Update/PostUpdate/CleanUp return exit

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	// TODO 3: Make sure all modules have a chance to cleanup
	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
	{
		ret = modules[i]->CleanUp();
		/*if (modules[i]->CleanUp() == false) { return false;}*/
		delete modules[i];
		modules[i] = nullptr;
	}

	return ret;
}
