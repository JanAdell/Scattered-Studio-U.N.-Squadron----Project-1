#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 15

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleScene;
class ModuleParticles;
class ModuleSceneIntro;
class ModuleSceneWin;
class ModuleFadeToBlack;
class ModuleCollisions;
class ModuleEnemies;
class ModuleRender;
class ModuleFonts;
class ModuleSceneLoose;

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

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;
	ModuleSceneIntro* initialScreen = nullptr;
	ModuleScene* scene = nullptr;
	ModuleSceneWin* sceneWin = nullptr;
	ModuleSceneLoose* loose = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* transition = nullptr;

	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	UINT32 frameStart = 0;
	int frameTime;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__