#include "ModuleEnemies.h"

#include "Application.h"
#include "ModuleHud.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleShop.h"
#include "Enemy.h"
#include "Collider.h"

#include "Mech.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownShip.h"

//UN Squadron enemies
//Lvl1
#include "Enemy_BigCamoJet.h"
#include "Enemy_MedCamoJet.h"
#include "Enemy_OrangeJet.h"
#include "Enemy_BlueJet.h"
#include "Enemy_GreenFighter.h"
#include "Enemy_SmallCamoJet.h"

//Lvl2
#include "Enemy_GreenJet.h"
#include "Enemy_WhiteJet.h"

//Bosses
#include "Boss_BlackBird.h"
#include "Boss_PurpleJackal.h"

//Player for Score value
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene2.h"
#include "ModuleParticles.h"

#define SPAWN_MARGIN 150


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/sprites/enemies/basic_enemies_3.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/explosion.wav");
	

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		
		spawnQueue[i].type = ENEMY_TYPE::NO_TYPE;
	}

	App->textures->Unload(texture);
	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
			else if (enemies[i]->position.x * SCREEN_SIZE > ((App->render->camera.x)+ SCREEN_WIDTH) + SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case REDBIRD:
					enemies[i] = new Enemy_RedBird(info.x, info.y, REDBIRD);
					break;
				case BROWNSHIP:
					enemies[i] = new Enemy_BrownShip(info.x, info.y, BROWNSHIP);
					break;
				case MECH:
					enemies[i] = new Mech(info.x, info.y, MECH);
					break;
				case BIG_CAMO_JET:
					enemies[i] = new Enemy_BigCamoJet(info.x, info.y, BIG_CAMO_JET);
					break;
				case MEDIUM_CAMO_JET:
					enemies[i] = new Enemy_MedCamoJet(info.x, info.y, MEDIUM_CAMO_JET);
					break;
				case GREEN_FIGHTER:
					enemies[i] = new Enemy_GreenFighter(info.x, info.y, GREEN_FIGHTER);
					break;
				case BLUE_JET:
					enemies[i] = new Enemy_BlueJet(info.x, info.y, BLUE_JET);
					break;
				case ORANGE_JET:
					enemies[i] = new Enemy_OrangeJet(info.x, info.y, ORANGE_JET);
					break;
				case SMALL_CAMO_JET:
					enemies[i] = new Enemy_SmallCamoJet(info.x, info.y, SMALL_CAMO_JET);
					break;
				case WHITE_JET_LVL_2:
					enemies[i] = new Enemy_WhiteJet(info.x, info.y, WHITE_JET_LVL_2);
					break;
				case GREEN_JET_LVL_2:
					enemies[i] = new Enemy_GreenJet(info.x, info.y, GREEN_JET_LVL_2);
					break;
				case BOSS_BLACKBIRD:
					enemies[i] = new Boss_BlackBird(info.x, info.y, BOSS_BLACKBIRD);
					break;
				case BOSS_PURPLE_JACKAL:
					enemies[i] = new Boss_PurpleJackal(info.x, info.y, BOSS_PURPLE_JACKAL);
					break;
				
			}

			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			int x = 0;
			LOG("bullet type %d %d", c2->type, c1->type);
			switch (c2->type)
			{
				case PLAYER_SHOT:
					LOG("normal collision");
					x = 5;
					break;
				case S_LASER:
					x = 15;
					break;
				case T_LASER:
					x = 10;
					break;
				case GUNPOD:
					x = 6;
					break;
				case BOMB:
					x = 20;
					break;
				case PLAYER:
					x = 30;
					break;
			}

			enemies[i]->OnCollision(c2, x); //Notify the enemy of a collision
			
			LOG("score value is %d", App->hud->score)
			
			if (enemies[i]->destroy) {
				
				switch (enemies[i]->enemy_type) {
				case BIG_CAMO_JET:
					App->shop->money += 300;
					App->hud->score += 100;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case MEDIUM_CAMO_JET:
					App->shop->money += 300;
					App->hud->score += 100;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case GREEN_FIGHTER:
					App->shop->money += 400;
					App->hud->score += 200;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case BLUE_JET:
					App->shop->money += 300;
					App->hud->score += 100;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case ORANGE_JET:
					App->shop->money += 300;
					App->hud->score += 100;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case SMALL_CAMO_JET:
					App->shop->money += 300;
					App->hud->score += 100;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case WHITE_JET_LVL_2:
					App->shop->money += 400;
					App->hud->score += 200;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case GREEN_JET_LVL_2:
					App->shop->money += 400;
					App->hud->score += 200;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case BOSS_BLACKBIRD:
					App->shop->money += 30000;
					App->hud->score += 10000;
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x+100, enemies[i]->position.y + 100);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x + 200, enemies[i]->position.y + 150);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x + 200, enemies[i]->position.y + 300);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x + 100, enemies[i]->position.y + 350);
					App->transition->FadeToBlack((Module*)App->scene, (Module*)App->sceneWin);
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case BOSS_PURPLE_JACKAL:
					App->shop->money += 30000;
					App->hud->score += 10000;
					App->scene2->victory_counter += 1;
					delete enemies[i];
					enemies[i] = nullptr;
					break;
				case PLAYER:
					App->player->hit = true;
					App->player->hp -= 1;
				}
								
			}

			break;
		}
	}
}





