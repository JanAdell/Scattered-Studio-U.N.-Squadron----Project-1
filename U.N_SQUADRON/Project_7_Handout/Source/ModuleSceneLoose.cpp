#include "ModuleSceneLoose.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"


ModuleSceneLoose::ModuleSceneLoose(bool startEnabled) : Module(startEnabled)
{

}

ModuleSceneLoose::~ModuleSceneLoose()
{

}

// Load assets
bool ModuleSceneLoose::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgtitle = App->textures->Load("Assets/gameover.png"); 
	App->audio->PlayMusic("Assets/gameover.ogg", 1.0f);
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;

}

update_status ModuleSceneLoose::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->transition->FadeToBlack((Module*)App->loose, (Module*)App->initialScreen, 60);

	}

	if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->initialScreen);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneLoose::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgtitle, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}