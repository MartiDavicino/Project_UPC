#include "Application.h"
#include "Module.h"
#include "Dummy.h"
#include "DummyEsc.h"
#include "Globals.h"

Application::Application()
{
	//define los dos modulos que esta utilizando la aplicacion en este momento.
	modules[0] = new ModuleDummy();

	modules[1] = new ModuleDummyESC();
}

// INIT all modules
bool Application::Init()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		modules[i]->Init();

	}

	//Inicializa todos los modulos
	return true;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;
	//Esta sección realiza el pre, post Y el update de cada modulo. Si alguno de ellos devuelve exit, la applicación se cierra
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

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	// Esta seccion hace un cleanup entero de los modulos al llamarla.

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
	{
		ret = modules[i]->CleanUp();
		delete modules[i];
		modules[i] = nullptr;
	}

	return ret;
}
