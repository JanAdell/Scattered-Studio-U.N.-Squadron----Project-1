#include "ModuleSceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"

#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_scancode.h"


ModuleSceneIntro::ModuleSceneIntro(bool startEnabled) : Module(startEnabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{

}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro Scene");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/titlescreen.png");
	App->audio->PlayMusic("Assets/Music/opening", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status ModuleSceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->transition->FadeToBlack(this, (Module*)App->scene, 90);
		
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}
