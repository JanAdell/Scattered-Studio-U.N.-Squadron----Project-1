#include "Enemy_GreenJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"

Enemy_GreenJet::Enemy_GreenJet(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	hp = 20;
	enemy_type = e_type;


	fly.PushBack({ 1726,97,156,42 });

	flydown.PushBack({ 1906,103,156,60 });

	flyup.PushBack({ 2080,97,156,54 });

	/*path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});*/

	
	path.PushBack({ -5.0f, 0.0f }, 70, &fly);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, 4.0f }, 150, &flydown);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, -4.0f }, 150, &flyup);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, 4.0f }, 150, &flydown);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ -10.0f, -4.0f }, 1500, &flyup);
	path.loop = false;

	path2.PushBack({ -5.0f, 0.0f }, 70, &fly);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ 1.0f, -4.0f }, 150, &flyup);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ 1.0f, 4.0f }, 150, &flydown);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ 1.0f, -4.0f }, 150, &flyup);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ -10.0f, 4.0f }, 1500, &flyup);
	path2.loop = false;

	path3.PushBack({ 1.0f, 6.0f }, 500, &flydown);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ 1.0f, -6.0f }, 500, &flyup);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ 1.0f, 6.0f }, 500, &flydown);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ -10.0f, -5.0f }, 1500, &flyup);
	path3.loop = false;


	collider = App->collisions->AddCollider({ 0, 0, 156, 60}, ColliderType::ENEMY, (Module*)App->enemies);

	time = 0;
}

void Enemy_GreenJet::Update()
{
	
	

	if (spawnPos.x - App->render->camera.x > SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x - App->render->camera.x > SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path2.GetCurrentAnimation();

		path2.Update();
		position = spawnPos + path2.GetRelativePosition();
		Enemy::Update();
	}
	
	current_time = SDL_GetTicks();

	if (position.x <= App->player->position.x && position.y <= App->player->position.y && current_time > time + 6000) {
		App->particles->w_missile_down.speed.x = 7;
		App->particles->w_missile_down.speed.y = 7;
		App->particles->AddParticle(App->particles->w_missile_down, position.x + 50, position.y + 60, ColliderType::ENEMY_SHOT);
		time = current_time;
	}

	if (position.x >= App->player->position.x && position.y >= App->player->position.y && current_time > time + 6000) {
		App->particles->w_missile_up_l.speed.x = -7;
		App->particles->w_missile_up_l.speed.y = -7;
		App->particles->AddParticle(App->particles->w_missile_up_l, position.x + 50, position.y + 60, ColliderType::ENEMY_SHOT);
		time = current_time;
	}

	if (position.x <= App->player->position.x && position.y >= App->player->position.y && current_time > time + 6000) {
		App->particles->w_missile_up.speed.x = 7;
		App->particles->w_missile_up.speed.y = -7;
		App->particles->AddParticle(App->particles->w_missile_down, position.x + 50, position.y + 60, ColliderType::ENEMY_SHOT);
		time = current_time;
	}

	if (position.x >= App->player->position.x && position.y <= App->player->position.y && current_time > time + 6000) {
		App->particles->w_missile_down_l.speed.x = -7;
		App->particles->w_missile_down_l.speed.y = 7;
		App->particles->AddParticle(App->particles->w_missile_down_l, position.x + 50, position.y + 60, ColliderType::ENEMY_SHOT);
		time = current_time;
	}

	/*if (spawnPos.y > SCREEN_HEIGHT) {
		currentAnim = path3.GetCurrentAnimation();

		path3.Update();
		position = spawnPos + path3.GetRelativePosition();
		Enemy::Update();
	}*/

}