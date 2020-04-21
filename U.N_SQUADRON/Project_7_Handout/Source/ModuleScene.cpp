#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "ModuleEnemies.h"

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

	

	bgTextures[0] = App->textures->Load("Assets/sprites/background/c1.png");
	bgTextures[1] = App->textures->Load("Assets/sprites/background/c2.png");
	bgTextures[2] = App->textures->Load("Assets/sprites/background/c3.png");
	bgTextures[3] = App->textures->Load("Assets/sprites/background/c4.png");

	App->audio->PlayMusic("Assets/stage1.ogg", 6);

	
	/*
	// Enemies --------------------------------------------------
	//Enemy Script->Initial pos + spawn delay
	//Med Camos
	//2 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	
	//3 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);

	//7 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);

	//9 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);

	//14 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);

	//17 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	
	//21 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);

	//24 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 800, 100);

	//33 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);

	//36 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);

	//38 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 800, 100);

	//39 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	
	//44 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);

	//46 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 800, 100);

	//48 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);

	//52 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);

	//56 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);

	//58 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);

	//58,5 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);

	//61 secs 
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);

	//62 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 800, 100);

	//63 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);

	//67 secs
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 800, 100);

	//68 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);

	//72 secs
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 800, 100);

	//74 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);

	//75 secs
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 800, 100);

	//77 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);

	//81 secs
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALL_CAMO_JET, 800, 100);

	//86 secs
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 800, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 800, 100);

	//-------------------------------------------------------------
	*/
	
	//Testing enemies
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 500, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 550, 300);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 500, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 550, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 0, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 0, 300);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 0, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::BLUE_JET, 0, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 600, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 625, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::MEDIUM_CAMO_JET, 650, 200);

	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 900, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 925, 300);
	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 950, 300);

	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 900, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 925, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::ORANGE_JET, 950, 100);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_FIGHTER, 1000, 200);

	App->enemies->AddEnemy(ENEMY_TYPE::BIG_CAMO_JET, 600, 300);
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

update_status ModuleScene::Update()
{
	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

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
