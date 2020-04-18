#include "ModuleStartScreen.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleScene.h"


ModuleStartScreen::ModuleStartScreen(){ 
	//Unicorn Animation
	unicorn_anim.PushBack({ 5,2,112,160 });
	unicorn_anim.PushBack({ 122,2,120,160 });
	unicorn_anim.PushBack({ 248,2,120,160 });
	unicorn_anim.speed = 0.1f;

	//Title rect
	title = { 235,165,236,67 };
	//text rect
	text = { 2,168,216,128 };
	//selector rect
	selector = { 236,240,13,16 };
}

ModuleStartScreen::~ModuleStartScreen() {}

bool ModuleStartScreen::Start() {
	bool ret = true;

	tex = App->textures->Load("Assets/sprites/menus/Menu-Spritesheet.png");
	if (tex == nullptr) {
		ret = false;
	}

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	selectorPos = { 68,116 };

	//Playing opening music
	App->audio->PlayMusic("Assets/music/soundtrack/opening.ogg");

	return ret;
}

update_status ModuleStartScreen::Update() {

}

update_status ModuleStartScreen::PostUpdate() {

	}
	


bool ModuleStartScreen::CleanUp() {
	bool ret = true;

	if (!App->textures->Unload(tex)) {
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}
	App->audio->StopMusic();

	return ret;
}