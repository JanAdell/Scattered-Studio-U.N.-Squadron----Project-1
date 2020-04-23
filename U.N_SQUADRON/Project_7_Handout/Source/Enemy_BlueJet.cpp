#include "Enemy_BlueJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_BlueJet::Enemy_BlueJet(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 616,262,60,18 });
	fly.speed = 0.01f;

	flyBack.PushBack({ 207*2,131 * 2,30 * 2,9 * 2 });
	flyBack.speed = 0.01f;

	flyUp.PushBack({ 341 * 2,129 * 2,30 * 2,13 * 2 });
	flyUp.speed = 0.01f;
	
	flyBackUp.PushBack({ 174 * 2,129 * 2,30 * 2,13 * 2 });
	flyBackUp.speed = 0.01f;

	flyDown.PushBack({ 275 * 2,131 * 2,30 * 2,14 * 2 });
	flyDown.speed = 0.01f;

	flyBackDown.PushBack({ 240 * 2,131 * 2,30 * 2,14 * 2 });
	flyBackDown.speed = 0.01f;



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

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, ColliderType::ENEMY, (Module*)App->enemies);

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
	if (current_time > time + 3500) {
		App->particles->enemy_shot.speed.x = (position.x - App->player->position.x) * -0.01;
		App->particles->enemy_shot.speed.y = (position.y - App->player->position.y) * -0.01;
		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, ColliderType::ENEMY_SHOT);
		time = current_time;
	}
}