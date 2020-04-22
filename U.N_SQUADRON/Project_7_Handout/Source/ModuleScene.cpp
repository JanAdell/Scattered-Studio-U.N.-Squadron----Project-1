#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"

#include "ModuleRender.h"

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

	bool ret = true;

	//Left Spawn management
	left_spawn_counter = 0;

	for (int i = 0; i < MAX_LEFT_SPAWNER; i++) left_spawn_positions[i] = 0;
		
	left_spawn_positions[ORANGE_JET_1] = 6000;
	left_spawn_positions[BLUE_JET_1] = 7000;
	left_spawn_positions[ORANGE_JET_2] = 8500;
	left_spawn_positions[BIG_CAMO_JET_2] = 8500;
	left_spawn_positions[BLUE_JETS_2] = 9000;
	left_spawn_positions[BLUE_JETS_3] = 9000;
	left_spawn_positions[BIG_CAMO_JET_3] = 18500;
	left_spawn_positions[BIG_CAMO_JET_4] = 19000;




	/*left_spawn_positions[BIG_CAMO_JET_1] = 900;
	left_spawn_positions[BLUE_JET_1] = 1000;
	left_spawn_positions[ORANGE_JET_2] = 1100;
	left_spawn_positions[BIG_CAMO_JET_2] = 1100;*/

	bgTextures[0] = App->textures->Load("Assets/sprites/background/c1.png");
	bgTextures[1] = App->textures->Load("Assets/sprites/background/c2.png");
	bgTextures[2] = App->textures->Load("Assets/sprites/background/c3.png");
	bgTextures[3] = App->textures->Load("Assets/sprites/background/c4.png");

	App->audio->PlayMusic("Assets/stage1.ogg", 6);

	
	
	// Enemies --------------------------------------------------
	//Enemy Script->Initial pos + spawn delay
	//Med Camos
	//2 secs 
	/*App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 5950, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 6100, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 6200, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 6300, 300);
														   
	//3 secs											   
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 6700, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 6800, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 6900, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 7000, 600);
														   
														  
	//21 secs											   
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 10000, 325);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 975, 375);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 975, 475);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1000, 525);
	
	//24 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 1000, 450);
	
	//36 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1350, 290);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1370, 350);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1370, 450);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1350, 550);
	
	//38 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 1500, 450);
	
	//44 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1675, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1650, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1675, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1650, 600);
	
	//46 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 1775, 450);

	//48 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 1875, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 1850, 390);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 1875, 490);
	
	//52 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1950, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1975, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1975, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 1950, 400);
	
	//56 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2050, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2075, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2100, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2125, 300);
		
	
	//61 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2220, 250);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2240, 250);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2280, 250);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2300, 250);
	
	//62 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 2325, 200);
	
	//63 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2425, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2450, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2425, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2450, 300);

	//67 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2525, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2550, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2575, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 2600, 100);

	//68 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 2600, 150);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 2625, 150);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 2650, 150);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 2675, 150);

	//72 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 2750, 200);

	//74 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 2850, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 2875, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 2900, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 2925, 100);

	//75 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 2950, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 2975, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 3000, 200);

	//77 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3025, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3050, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3050, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3025, 400);

	//81 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3075, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3100, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3100, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 3075, 300);

	//86 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 3150, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 3175, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 3200, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 3225, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 3150, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 3175, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 3200, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 3225, 300);*/

	//-------------------------------------------------------------
	
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 0, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 0, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 0, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 0, 900);

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
		/*if (camera_x >= left_spawn_positions[left_spawn_counter]) {
			switch (left_spawner(left_spawn_counter))
			{
			case ORANGE_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x - 100, 500);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x, 500);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x + 100, 500);
				break;
		
			case BIG_CAMO_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 100, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 200);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 100, 200);
				break;
			case BLUE_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 40, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 80, 90);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 310);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 40, 310);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 80, 310);
				break;
			case ORANGE_JET_2:
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x - 30, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, camera_x + 30, 300);
				break;				
			case BIG_CAMO_JET_2:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 30, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 30, 300);
				break;
			case BLUE_JETS_2:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 290);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 140, 290);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 510);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x - 140, 510);
				break;
			case BLUE_JETS_3:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 290);
				App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, camera_x, 590);
				
				break;
			case BIG_CAMO_JET_3:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 30, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 300);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 30, 300);
				break;

			case BIG_CAMO_JET_4:
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x - 30, 600);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x, 600);
				App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, camera_x + 30, 600);
				break;

			default:
				break;
			}
			left_spawn_counter++;
		}
	*/	
	}
	

	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	if (App->render->camera.x >= 3100) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin);
		
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
		

	return true;
}
