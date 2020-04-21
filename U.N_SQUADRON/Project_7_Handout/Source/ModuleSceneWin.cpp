#include "ModuleSceneWin.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"

ModuleSceneWin::ModuleSceneWin(bool startEnabled) : Module(startEnabled)
{

}

ModuleSceneWin::~ModuleSceneWin() {}

bool ModuleSceneWin::Start() {
	bool ret = true;


	tex = App->textures->Load("Assets/WinScreen.png");

	if (tex == nullptr) {
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

