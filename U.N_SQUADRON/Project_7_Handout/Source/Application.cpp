#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneWin.h"
#include "ModuleScene.h"
#include "ModuleShop.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "ModuleSceneLoose.h"
#include "ModuleWelcomeScene.h"
#include "ModuleHud.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = welcomeScreen = new ModuleWelcomeScene(true);

	modules[5] = initialScreen = new ModuleSceneIntro(false);


	modules[6] = shop = new ModuleShop(false);

	modules[7] = scene = new ModuleScene(false);

	modules[8] = sceneWin = new ModuleSceneWin(false);
	modules[9] = loose = new ModuleSceneLoose(false);

	modules[10] = player = new ModulePlayer(false);

	modules[11] = particles = new ModuleParticles(true);
	modules[12] = enemies = new ModuleEnemies(false);
	modules[13] = hud = new ModuleHud(false);
	modules[14] = collisions = new ModuleCollisions(true);
	modules[15] = transition = new ModuleFadeToBlack(true);
	modules[16] = fonts = new ModuleFonts(false);

	modules[17] = render = new ModuleRender(true);
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
	bool wants_to_quit = false;

	for (int i = 0; i < NUM_MODULES && ret != update_status::UPDATE_ERROR; ++i) {
		if (modules[i]->IsEnabled()) {
			ret = modules[i]->PreUpdate();
			if (ret == update_status::UPDATE_STOP) {
				wants_to_quit = true;
			}
		}
	}

	for (int i = 0; i < NUM_MODULES && ret != update_status::UPDATE_ERROR; ++i) {
		if (modules[i]->IsEnabled()) {
			ret = modules[i]->Update();
			if (ret == update_status::UPDATE_STOP) {
				wants_to_quit = true;
			}
		}
	}

	for (int i = 0; i < NUM_MODULES && ret != update_status::UPDATE_ERROR; ++i) {
		if (modules[i]->IsEnabled()) {
			ret = modules[i]->PostUpdate();
			if (ret == update_status::UPDATE_STOP) {
				wants_to_quit = true;
			}
		}
	}

	if (wants_to_quit) ret = update_status::UPDATE_STOP;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
