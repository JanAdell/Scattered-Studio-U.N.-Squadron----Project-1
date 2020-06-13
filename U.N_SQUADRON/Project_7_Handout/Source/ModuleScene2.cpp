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
	

}
// Load assets
bool ModuleScene2::Start()
{
	victory_counter = 0;
	App->hud->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->particles->Enable();

	LOG("Loading background assets\n");

	bool ret = true;


	bgTexture = App->textures->Load("Assets/background2.png");

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);

	left_spawn_counter = 0;

	for (int i = 0; i < MAX_LEFT_SPAWNER; i++) left_spawn_positions[i] = 0;
	
	//Left spawn coords
	left_spawn_positions[WHITE_JET_1] = 1000;
	left_spawn_positions[WHITE_JET_2] = 1550;
	left_spawn_positions[WHITE_JET_3] = 2000;
	left_spawn_positions[WHITE_JET_4] = 3000;
	left_spawn_positions[WHITE_JET_5] = 3300;
	left_spawn_positions[WHITE_JET_6] = 3600;
	left_spawn_positions[PURPLE_JACKAL] = 4900;
	


	// Enemies ---	

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1500, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1750, 300);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1770, -20);

	//-------------------------------------------------------------

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 2230, -20);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 2250, 300);
	//------------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 2600, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 2850, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3000, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3250, 300);
	//-------------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3500, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3700, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3900, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4100, 300);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4150, -20);
	//-------------------------------------------------------------

	App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, 4300, -20);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4400, 600);
	
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4450, -20);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4500, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4700, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4800, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 5000, 600);
	
	//-----------BOSS----------------------------------------------
	//App->enemies->AddEnemy(ENEMY_TYPE::BOSS_PURPLE_JACKAL, 4900, 600);
	//App->enemies->AddEnemy(ENEMY_TYPE::BOSS_PURPLE_JACKAL, 4950, 300);


	//falten verticals

	//Test enemies
	//App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, 1000, 400);
	//App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1000, 600);
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	moveBG1 = 0;
	moveBG2 = 1;
	loopBG = -1;
	limitBG = 0;
	return ret;
}

update_status ModuleScene2::Update() 
{
	
	if (left_spawn_counter < MAX_LEFT_SPAWNER) {
		int camera_x = App->render->camera.x;
		if (camera_x >= left_spawn_positions[left_spawn_counter]) {
			switch (left_spawner(left_spawn_counter))
			{
			case WHITE_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 300);
				break;
			case WHITE_JET_2:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 300);
				break;
			case WHITE_JET_3:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 300);
				break;
			case WHITE_JET_4:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 300);
				break;
			case WHITE_JET_5:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 600);
				break;
			case WHITE_JET_6:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 300);
				break;
			default:
				break;
			}
			left_spawn_counter++;
		}

	}

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

	/*if (victory_counter == 3) {

	}*/

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
