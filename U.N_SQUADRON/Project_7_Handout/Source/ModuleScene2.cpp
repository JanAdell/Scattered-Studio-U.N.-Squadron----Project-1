#include "ModuleScene2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleHud.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleSceneWin.h"
#include "ModuleFonts.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_scancode.h"


ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene2::~ModuleScene2() {
	CleanUp();

}
// Load assets
bool ModuleScene2::Start()
{
	App->player->Enable();
	//App->hud->Enable();
	//App->enemies->Enable();
	App->collisions->Enable();

	LOG("Loading background assets\n");

	bool ret = true;


	bgTexture = App->textures->Load("Assets/background2.png");

	//App->audio->PlayMusic("Assets", );

	// Enemies ---	

	//Test enemies
	App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, 1860, 400);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1920, 400);
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	bg1 = 0;
	bg2 = 1;
	bgloop = -1;
	bgs = 0;

	return ret;
}

update_status ModuleScene2::Update() {

	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	/*if (App->render->camera.x >= 5000) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin);
	}

	if (App->player->destroyed == true) {
		App->transition->FadeToBlack(this, (Module*)App->loose);
		App->player->collider->pendingToDelete = true;
		App->particles->enemy_shot.isAlive = false;
	}*/

if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
	App->transition->FadeToBlack(this, (Module*)App->initialScreen, 90);
}

if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
	App->transition->FadeToBlack(this, (Module*)App->sceneWin, 90);
}

if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
	App->transition->FadeToBlack(this, (Module*)App->loose, 90);
}


	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	bgs = App->render->camera.x + SCREEN_WIDTH;


	return update_status::UPDATE_CONTINUE;
}

void ModuleScene2::updateBackground() {


	if ((bgs % (3860/2)) == 0) {
		bgloop += 1;
		if (bgloop > 1) {
			((bgloop % 2) == 0) ? bg1 += 2 : bg2 += 2;
		}
	}

//	bgy = -(App->player->position.y * (+;

}


// Update: draw background

update_status ModuleScene2::PostUpdate() {

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 3860 * bg1, bgy, NULL, 2);
	App->render->Blit(bgTexture, 3860 * bg2, bgy, NULL, 2);



	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene2::CleanUp()
{
	//Enable (and properly disable) the player module
	App->player->Disable();
	//App->enemies->Disable();
	App->collisions->Disable();
	//App->hud->Disable();
	//App->textures->Disable();
	//App->audio->Disable();

	App->textures->Unload(bgTexture);


	return true;
}
