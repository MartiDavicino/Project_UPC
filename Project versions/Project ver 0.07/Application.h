#pragma once

#include "Globals.h"


#define NUM_MODULES 2
class Module;

class ModuleWindow;
class ModuleRender;


class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();
	~Application();


	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:

	Module* modules[NUM_MODULES];


	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;

};

extern Application* App;