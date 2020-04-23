#include "ModuleWelcomeScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"


ModuleWelcomeScene::ModuleWelcomeScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleWelcomeScene::~ModuleWelcomeScene()
{

}

// Load assets
bool ModuleWelcomeScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/sprites/scenes/WELCOMESCREEN.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;

}

update_status ModuleWelcomeScene::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->transition->FadeToBlack((Module*)App->welcomeScreen, (Module*)App->initialScreen, 60);

	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleWelcomeScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

