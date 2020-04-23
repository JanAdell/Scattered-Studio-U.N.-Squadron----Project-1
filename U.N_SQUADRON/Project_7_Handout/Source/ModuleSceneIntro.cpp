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

	bgTexture = App->textures->Load("Assets/sprites/menu/menuinicial.png");
	App->audio->PlayMusic("Assets/music/levels/opening.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	fAnim.PushBack({ 0,0,1297,960 });
	fAnim.PushBack({ 2595,0,1297,960 });
	fAnim.PushBack({ 3893,0,1297,960 });
	fAnim.PushBack({ 5191,0,1297,960 });
	fAnim.speed = 0.1f;
	fAnim.loop = true;
	menuAnim = &fAnim;

	return ret;
}

update_status ModuleSceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->transition->FadeToBlack(this, (Module*)App->scene, 90);
		
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin, 90);

	}

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->loose);
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

