#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"
#include "ModuleHud.h"
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

	App->hud->Enable();
	LOG("Loading background assets");
		
	cont[0] = 0;
	cont[1] = 0;
	cont[2] = 0;
	cont[3] = 0;

	bgTextures[0] = App->textures->Load("Assets/sprites/background/c1.png");
	bgTextures[1] = App->textures->Load("Assets/sprites/background/c2.png");
	bgTextures[2] = App->textures->Load("Assets/sprites/background/c3.png");
	bgTextures[3] = App->textures->Load("Assets/sprites/background/c4.png");

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz  0123456789.,ªº?!*$%&()+-/:;<=>@·    " };	yellowFont = App->fonts->Load("Assets/FontY.png", lookupTable, 5);
	greenFont = App->fonts->Load("Assets/FontG.png", lookupTable, 5);

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
	left_spawn_positions[BOSS_BLACKBIRD] = 4500;
	


	//----------Enemy Debug--------------------
	//App->enemies->AddEnemy(ENEMY_TYPE::BOSS_BLACKBIRD, 100, 1000);

	
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
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2500, 325);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2400, 475);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2400, 575);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 2500, 625);
	
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
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3275, 320);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3250, 320);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3275, 640);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3250, 640);
	
	//46 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 3700, 250);
	//-----------------------------------------------------------
	//48 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 3500, 390);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 3575, 490);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 3500, 590);
	
	//52 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3600, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3650, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3650, 400);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3600, 500);
	
	//56 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3700, 500);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3750, 500);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3800, 500);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 3850, 500);
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
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5250, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5275, 250);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5275, 650);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5250, 550);

	//81 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5300, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5350, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5350, 550);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 5300, 550);

	//86 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 5450, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 5500, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 5550, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 5600, 350);

	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5450, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5500, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5550, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 5600, 700);

	//Boss
	//App->enemies->AddEnemy(ENEMY_TYPE::BOSS_BLACKBIRD, 5700, 1000);

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
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x - 120, 700);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x, 700);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x + 120, 700);
				break;
		
			case BIG_CAMO_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 120, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 120, 200);
				break;
			case BLUE_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 120, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 240, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 900);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 120, 900);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 240, 900);
				break;
			case ORANGE_JET_2:
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x - 120, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x + 120, 200);
				break;				
			case BIG_CAMO_JET_2:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 120, 700);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 700);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 120, 700);
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
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 120, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 120, 300);
				break;

			case BIG_CAMO_JET_4:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 120, 600);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 600);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 120, 600);
				break;
			case BOSS_BLACKBIRD:
				App->enemies->AddEnemy(ENEMY_TYPE::BOSS_BLACKBIRD, camera_x+150, 1000);
				break;
			default:
				break;
			}
			left_spawn_counter++;
		}
	
	}
	

	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	/*if (App->render->camera.x >= 5000) {
		App->hud->Disable();
		//change to when blackbird dies
	}*/

	if (App->player->destroyed == true) {
		App->transition->FadeToBlack(this, (Module*)App->loose);
		App->player->collider->pendingToDelete = true;
		App->particles->enemy_shot.isAlive = false;
		App->hud->Disable();
		//App->particles->CleanUp();
		App->collisions->CleanUp();
	}
	   
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->initialScreen, 90);
		App->hud->Disable();
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin, 90);
		App->hud->Disable();
	}

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->loose, 90);
		App->hud->Disable();
	}
	if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
		//App->audio->StopMusic();
		App->transition->FadeToBlack(this, (Module*)App->shop);
	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->scene, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->scene2, 90);
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

	App->fonts->BlitText(715, 10, greenFont, "1");


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
	App->player->CleanUp();
	App->enemies->CleanUp();
	App->particles->CleanUp();
	App->hud->Disable();
	App->fonts->UnLoad(yellowFont);
	App->fonts->UnLoad(greenFont);
	App->textures->Unload(bgTextures[0]);
	App->textures->Unload(bgTextures[1]);
	App->textures->Unload(bgTextures[2]);
	App->textures->Unload(bgTextures[3]);

	App->audio->StopMusic();
	return true;
}
