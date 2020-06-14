#include "Enemy_MedCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_MedCamoJet::Enemy_MedCamoJet(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{

	hp = 5;
	enemy_type = e_type;

	//fly right
	fly.PushBack({ 1100,384,120,36 });
	fly.speed = 0.1f;

	//fly left
	flyback.PushBack({ 960,384,120,36 });
	flyback.speed = 0.01f;
	
	//turn (right to left)
	turnback.PushBack({ 820,352,120,68 });
	turnback.PushBack({ 692,328,120,92 });
	turnback.PushBack({ 588,328,96,92 });
	turnback.PushBack({ 508,328,68,92 });
	turnback.PushBack({ 452,328,40,92 });
	turnback.PushBack({ 376,328,64,92 });
	turnback.PushBack({  272,328,92,92 });
	turnback.PushBack({  144,324,120,96 });
	turnback.PushBack({  16,356,120,64 });

	turnback.loop = false;
	turnback.speed = 0.08f;

	//turn (left to right)
	turn.PushBack({ 1240,352,30*4,68 });
	turn.PushBack({ 1368,328,30*4,92 });
	turn.PushBack({ 1496,328,96,92 });
	turn.PushBack({ 1604,328,68,92 });
	turn.PushBack({ 1688,328,10*4,92 });
	turn.PushBack({ 1740,328,64,92 });
	turn.PushBack({ 1816,328,92,92 });
	turn.PushBack({ 1916,324,30*4,96 });
	turn.PushBack({ 2044,356,30*4,64 });
	turn.loop = false;
	turn.speed = 0.08f;

	//fly flipped left
	flyreverse.PushBack({ 511*4,89*4,30 * 4,16*4 });
	flyreverse.speed = 0.1f;

	//fly flipped right
	flyreverseback.PushBack({ 4*4,89*4,30 * 4,16*4 });
	flyreverseback.speed = 0.1f;

	//Left->right->left
	path.PushBack({ 5.0f , 0.f }, 200, &fly);
	path.PushBack({ -1.0f , 1.0f }, 70, &turn);
	path.PushBack({ -4.0f, 0.0f }, 700, &flyreverse);

	//Right->left->right
	path2.PushBack({ -3.0f , 0.f }, 200, &flyback);
	path2.PushBack({ -0.5f , 0.5f }, 70, &turnback);
	path2.PushBack({ 4.0f, 0.0f }, 700, &flyreverseback);

	collider = App->collisions->AddCollider({ 0, 0, 48 * 2, 24 * 2 }, ColliderType::ENEMY, (Module*)App->enemies);
	
	time = 0;

	

}

void Enemy_MedCamoJet::Update()
{
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x > SCREEN_WIDTH / 2) {
		currentAnim = path2.GetCurrentAnimation();

		path2.Update();
		position = spawnPos + path2.GetRelativePosition();
		Enemy::Update();
	}

	current_time = SDL_GetTicks();
	if (current_time > time + 8000) {
		direction_x = float(App->player->position.x - position.x);
		direction_y = float(App->player->position.y - position.y);
		float normal = sqrt(pow(direction_x, 2) + pow(direction_y, 2));
		App->particles->enemy_shot.speed.x = int((direction_x / normal) * 7);
		App->particles->enemy_shot.speed.y = int((direction_y / normal) * 7);
		App->particles->AddParticle(App->particles->enemy_shot, position.x + 50, position.y + 30, ColliderType::ENEMY_SHOT);
		//LOG("speed value in x %d and y %d", App->particles->enemy_shot.speed.x, App->particles->enemy_shot.speed.y);
		time = current_time;
	}

}