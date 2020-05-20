#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleSceneIntro;
class ModuleScene;
class ModuleMenu;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleBalls;
class ModuleRopes;
class ModuleRender;
class ModuleFadeToBlack;
class ModuleInterface;
class ModuleFonts;
class ModuleWin;
class ModuleLose;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();
	update_status Win();
	int score = 0;

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;
	ModuleScene* scene = nullptr;
	ModuleSceneIntro* sceneIntro = nullptr;
	ModuleMenu* menu = nullptr;
	ModuleWin* win = nullptr;
	ModuleLose* lose = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleBalls* balls = nullptr;
	ModuleRopes* ropes = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleInterface* interfaceElements = nullptr;


	ModuleRender* render = nullptr;

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__