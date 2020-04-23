#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneWin.h"
#include "ModuleFonts.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_scancode.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");
		
	cont[0] = 0;
	cont[1] = 0;
	cont[2] = 0;
	cont[3] = 0;

	bgTextures[0] = App->textures->Load("Assets/sprites/background/c1.png");
	bgTextures[1] = App->textures->Load("Assets/sprites/background/c2.png");
	bgTextures[2] = App->textures->Load("Assets/sprites/background/c3.png");
	bgTextures[3] = App->textures->Load("Assets/sprites/background/c4.png");

	App->audio->PlayMusic("Assets/music/Build/music/stage1.ogg", 6);
		
	//App->fonts->Load("");

	App->particles->Enable();

	bool ret = true;

	//Left Spawn management
	left_spawn_counter = 0;

	for (int i = 0; i < MAX_LEFT_SPAWNER; i++) left_spawn_positions[i] = 0;
	
	//---------------------------------------
	left_spawn_positions[ORANGE_JET_1] = 1250;
	left_spawn_positions[BIG_CAMO_JET_1] = 1500;
	left_spawn_positions[BLUE_JET_1] = 1700;
	//----------------------------------------
	left_spawn_positions[ORANGE_JET_2] = 2250;
	left_spawn_positions[BIG_CAMO_JET_2] = 2250;
	//----------------------------------------
	left_spawn_positions[BLUE_JETS_2] = 2900;
	//----------------------------------------
	left_spawn_positions[BLUE_JETS_3] = 3100;
	//----------------------------------------
	left_spawn_positions[BIG_CAMO_JET_3] = 3800;
	left_spawn_positions[BIG_CAMO_JET_4] = 3800;
	//-----------------------------------------


	
	//Enemies --------------------------------------------------
	//Enemy Script->Initial pos 
	//Med Camos
	//2 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 1860,400);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 1920,400);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 1980,400);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2040,400);
														   
	//3 secs											   
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 1900, 650);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 1960, 650);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2020, 650);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2080, 650);
	
	//-------------------------------------------------------------
														  
	//21 secs											   
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2500, 425);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2400, 575);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2400, 675);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2500, 725);
	
	//24 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 2500, 250);
	
	//36 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2950, 390);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2970, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2970, 550);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2950, 650);
	
	//38 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 3200, 250);
	//------------------------------------------------------------
	//44 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3275, 400);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3250, 400);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3275, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3250, 700);
	
	//46 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 3700, 250);
	//-----------------------------------------------------------
	//48 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 3500, 390);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 3575, 490);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 3500, 590);
	
	//52 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3600, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3650, 400);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3650, 500);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3600, 600);
	
	//56 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3700, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3750, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3800, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3850, 600);
	//--------------------------------------------------------------	
	
	//61 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3900, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3950, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4000, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4050, 450);
	
	//62 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 4200, 250);
	
	//63 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4150, 550);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4200, 550);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4250, 550);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4300, 550);
	//-------------------------------------------------------------
	//67 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4350, 500);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4400, 500);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4450, 500);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 4500, 500);

	//68 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 4550, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 4610, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 4670, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 4730, 350);

	//72 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 4800, 250);

	//74 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 4850, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 4910, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 4970, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5030, 350);

	//75 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 5100, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 5150, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 5200, 450);

	//77 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5250, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5275, 250);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5275, 750);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5250, 550);

	//81 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5300, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5350, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5350, 650);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5300, 650);

	//86 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 5450, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 5500, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 5550, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 5600, 350);

	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5450, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5500, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5550, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5600, 700);

	//-------------------------------------------------------------
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

update_status ModuleScene::Update()
{


	if (left_spawn_counter < MAX_LEFT_SPAWNER) {
		int camera_x = App->render->camera.x;
		if (camera_x >= left_spawn_positions[left_spawn_counter]) {
			switch (left_spawner(left_spawn_counter))
			{
			case ORANGE_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x - 70, 700);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x, 700);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x + 70, 700);
				break;
		
			case BIG_CAMO_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 70, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 70, 200);
				break;
			case BLUE_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 75, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 150, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 900);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 75, 900);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 150, 900);
				break;
			case ORANGE_JET_2:
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x - 50, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x + 50, 200);
				break;				
			case BIG_CAMO_JET_2:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 50, 700);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 700);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 50, 700);
				break;
			case BLUE_JETS_2:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 290);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 150, 290);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 510);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 150, 510);
				break;
			case BLUE_JETS_3:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 290);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 590);
				
				break;
			case BIG_CAMO_JET_3:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 70, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 70, 300);
				break;

			case BIG_CAMO_JET_4:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 70, 600);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 600);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 70, 600);
				break;

			default:
				break;
			}
			left_spawn_counter++;
		}
	
	}
	

	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	if (App->render->camera.x >= 5000) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin);
	}

	if (App->player->destroyed == true) {
		App->transition->FadeToBlack(this, (Module*)App->loose);
		App->player->collider->pendingToDelete = true;
		App->particles->enemy_shot.isAlive = false;
		
	}
	   
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->initialScreen, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->loose, 90);
	}



	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);

	for (int i = 0; i < 4; i++) {
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * cont[i], 0, NULL, i + 1);
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * (cont[i] + 1), 0, NULL, i + 1);
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * (cont[i] + 2), 0, NULL, i + 1);
	}

	return update_status::UPDATE_CONTINUE;


}

void ModuleScene::updateBackground() {

	for (int i = 0; i < 4; i++) {
		if (((App->render->camera.x) % ((SCREEN_WIDTH / (i + 1)) + 1)) == 0) {
			cont[i]++;
		}
	}
}

bool ModuleScene::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->particles->Disable();

	App->textures->Unload(bgTextures[0]);
	App->textures->Unload(bgTextures[1]);
	App->textures->Unload(bgTextures[2]);
	App->textures->Unload(bgTextures[3]);

	return true;
}
