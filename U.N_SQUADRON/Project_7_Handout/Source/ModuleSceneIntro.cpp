#include "ModuleSceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleStartScreen.h"

#include "ModuleScene.h"

#include "SDL/include/SDL_scancode.h"


ModuleSceneIntro::ModuleSceneIntro(){


	//screen rect
	screen = { 0,0,256,256 };

}
ModuleSceneIntro::~ModuleSceneIntro() {}

bool ModuleSceneIntro::Start() {

	bool ret = true;
	
	
	tex = App->textures->Load("Assets/sprites/menus/InitialScreen.png");
	if (tex == nullptr) {
		ret = false;
	}



	//Playing opening music
	//App->audio->PlayMusic("Assets/music/soundtrack/xxx.ogg");

	return ret;
}

update_status ModuleSceneIntro::Update() {
	
}

update_status ModuleSceneIntro::PostUpdate() {
	update_status ret = update_status::UPDATE_CONTINUE;
	//blit unicorn

	return ret;
}

bool ModuleSceneIntro::CleanUp() {
	bool ret = true;
	if (!App->textures->Unload(tex)) {
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}
	App->audio->StopMusic();

	return ret;
}