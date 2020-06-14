#include "Enemy_BlueJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_BlueJet::Enemy_BlueJet(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	hp = 5;
	enemy_type = e_type;
	
	flyBackDown.PushBack({ 960,524,120,56 });
	flyBackDown.speed = 0.01f;

	flyBackUp.PushBack({ 696,516,120,52 });
	flyBackUp.speed = 0.01f;

	flyDown.PushBack({ 1100,524,120,56 });
	flyDown.speed = 0.01f;

	flyBack.PushBack({ 828,524,120,36 });
	flyBack.speed = 0.01f;

	fly.PushBack({ 1232,524,120,36});
	fly.speed = 0.01f;

	flyUp.PushBack({ 1364,516,120,52 });
	flyUp.speed = 0.01f;


	//Botright	
	path.PushBack({ -4.0f , 0.f }, 100, &flyBack);
	path.PushBack({ -4.0f , -4.0f }, 400, &flyBackUp);

	//Topright
	path2.PushBack({ -4.0f , 0.f }, 100, &flyBack);
	path2.PushBack({ -4.0f , 4.0f }, 400, &flyBackDown);

	//Botleft
	path3.PushBack({ 4.0f , 0.f }, 100, &fly);
	path3.PushBack({ 4.0f , -4.0f }, 400, &flyUp);

	//Topleft
	path4.PushBack({ 4.0f , 0.f }, 100, &fly);
	path4.PushBack({ 4.0f , 4.0f }, 400, &flyDown);

	collider = App->collisions->AddCollider({ 0, 0, 48 * 2, 24 * 2 }, ColliderType::ENEMY, (Module*)App->enemies);

	time = 0;
}

void Enemy_BlueJet::Update()
{
	if (spawnPos.x > SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x > SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path2.GetCurrentAnimation();

		path2.Update();
		position = spawnPos + path2.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path3.GetCurrentAnimation();

		path3.Update();
		position = spawnPos + path3.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path4.GetCurrentAnimation();

		path4.Update();
		position = spawnPos + path4.GetRelativePosition();
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