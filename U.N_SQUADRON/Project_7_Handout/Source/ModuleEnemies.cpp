#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"

#include "Enemy.h"

#include "Mech.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownShip.h"

//UN Squadron enemies
#include "Enemy_BigCamoJet.h"
#include "Enemy_MedCamoJet.h"
#include "Enemy_OrangeJet.h"
#include "Enemy_BlueJet.h"
#include "Enemy_GreenFighter.h"
#include "Enemy_SmallCamoJet.h"

//Player for Score value
#include "ModulePlayer.h"


#define SPAWN_MARGIN 200


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
	}

	App->textures->Unload(texture);
	//App->audio->

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
				case ENEMY_TYPE::REDBIRD:
					enemies[i] = new Enemy_RedBird(info.x, info.y);
					break;
				case ENEMY_TYPE::BROWNSHIP:
					enemies[i] = new Enemy_BrownShip(info.x, info.y);
					break;
				case ENEMY_TYPE::MECH:
					enemies[i] = new Mech(info.x, info.y);
					break;
				case ENEMY_TYPE::BIG_CAMO_JET:
					enemies[i] = new Enemy_BigCamoJet(info.x, info.y);
					break;
				case ENEMY_TYPE::MEDIUM_CAMO_JET:
					enemies[i] = new Enemy_MedCamoJet(info.x, info.y);
					break;
				case ENEMY_TYPE::GREEN_FIGHTER:
					enemies[i] = new Enemy_GreenFighter(info.x, info.y);
					break;
				case ENEMY_TYPE::BLUE_JET:
					enemies[i] = new Enemy_BlueJet(info.x, info.y);
					break;
				case ENEMY_TYPE::ORANGE_JET:
					enemies[i] = new Enemy_OrangeJet(info.x, info.y);
					break;
				case ENEMY_TYPE::SMALL_CAMO_JET:
					enemies[i] = new Enemy_SmallCamoJet(info.x, info.y);
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
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
  			App->player->score_value += 300;
			LOG("score value is %d", App->player->score_value)
			delete enemies[i];
			enemies[i] = nullptr;

			break;
		}
	}
}

