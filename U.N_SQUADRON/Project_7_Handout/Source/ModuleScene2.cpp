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
	App->hud->Enable();
	//App->enemies->Enable();
	App->collisions->Enable();

	LOG("Loading background assets\n");

	bool ret = true;


	bgTexture = App->textures->Load("Assets/background2.png");

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);

	// Enemies ---	

	//Test enemies
	App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, 1860, 400);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1920, 400);
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	moveBG1 = 0;
	moveBG2 = 1;
	loopBG = -1;
	limitBG = 0;
	return ret;
}

update_status ModuleScene2::Update() {



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


	limitBG = App->render->camera.x + SCREEN_WIDTH;


	return update_status::UPDATE_CONTINUE;
}

void ModuleScene2::updateBackground() {



	if ((limitBG % (3859 / 2)) == 0) {
		loopBG += 1;
		if (loopBG > 1) {
			((loopBG % 2) == 0) ? moveBG1 += 2 : moveBG2 += 2;
		}
	}

	Y_BG = -(App->player->position.y * 0.32f) + -12 ;


}


// Update: draw background

update_status ModuleScene2::PostUpdate() {

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 3859 * moveBG1, Y_BG, NULL, 2);
	App->render->Blit(bgTexture, 3859 * moveBG2, Y_BG, NULL, 2);



	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene2::CleanUp()
{
	//Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->hud->Disable();
	App->textures->Disable();
	App->audio->Disable();
	App->textures->Unload(bgTexture);


	return true;
}
