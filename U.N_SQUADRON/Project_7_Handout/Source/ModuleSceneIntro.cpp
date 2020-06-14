#include "ModuleSceneIntro.h"
#include "Application.h"
#include "ModuleTextures.h"

#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"

#include "ModuleShop.h"

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

	bgTexture = App->textures->Load("Assets/sprites/menu/menuinicial_1.png");
	App->audio->PlayMusic("Assets/music/Build/music/opening.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	fAnim.PushBack({ 0,0,1297,960 });
	fAnim.PushBack({ 1326,0,1297,960 });
	fAnim.PushBack({ 2670,0,1297,960 });
	//fAnim.PushBack({ 5191,0,1297,960 });
	fAnim.speed = 0.2f;
	fAnim.loop = true;
	menuAnim = &fAnim;

	App->shop->shoploop = false;

	return ret;
}

update_status ModuleSceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{

		App->transition->FadeToBlack(this, (Module*)App->shop, 60.0f);
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin, 90);

	}

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
		//App->audio->StopMusic();
		App->transition->FadeToBlack(this, (Module*)App->loose);
	}

	if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
		//App->audio->StopMusic();
		App->transition->FadeToBlack(this, (Module*)App->shop);
	}


	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->initialScreen, 90);

	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->scene, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->scene2, 90);
	}


	if (menuAnim != nullptr)
	{
		menuAnim->Update();
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexture, 0, 0, &(menuAnim->GetCurrentFrame()));

	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneIntro::CleanUp() {
	bool ret = true;

	if (!App->textures->Unload(bgTexture)) {
		LOG("Start Screen -> Error unloading the texture.");
		ret = false;
	}
	App->textures->Unload(bgTexture);
	App->audio->StopMusic();
	return true;
}

