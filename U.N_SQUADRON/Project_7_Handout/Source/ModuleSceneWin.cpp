#include "ModuleSceneWin.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleAudio.h"

ModuleSceneWin::ModuleSceneWin(bool startEnabled) : Module(startEnabled)
{
	screen = { 0,0,256,224 };
}

ModuleSceneWin::~ModuleSceneWin() {}

bool ModuleSceneWin::Start() {

	LOG("Loading Win Scene");

	bool ret = true;


	bgTexture = App->textures->Load("Assets/WinScreen.png");
	App->audio->PlayMusic("Assets/Music/soundtrack/missionclear.wav", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	if (bgTexture == nullptr) {
		ret = false;
	}

	return ret;
}

update_status ModuleSceneWin::Update() {
	update_status ret = update_status::UPDATE_CONTINUE;

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN){
		App->transition->FadeToBlack(this, (Module*)App->initialScreen, 60);
	}

	return ret;
}

// Update: draw background
update_status ModuleSceneWin::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneWin::CleanUp() {
	bool ret = true;

	if (!App->textures->Unload(bgTexture)) {
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}

	return ret;
}

