#include "Globals.h"
#include "Module.h"
#include "Dummy.h"

#define NUM_MODULES 2

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:

	Module* modules[NUM_MODULES];

};
