#include "Enemy_GreenJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_GreenJet::Enemy_GreenJet(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	hp = 20;
	enemy_type = e_type;


	fly.PushBack({ 35,221,104,28 });

	flydown.PushBack({ 151,225,104,40 });

	flyup.PushBack({ 267,221,104,36 });

	/*path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});*/

	//-----------DEBUG PATH----------------
	path.PushBack({ 5.0f , 0.f }, 200, &fly);


	collider = App->collisions->AddCollider({ 0, 0, 214 * 2, 78 * 2 }, ColliderType::ENEMY, (Module*)App->enemies);

	time = 0;
}

void Enemy_GreenJet::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	current_time = SDL_GetTicks();
	if (current_time > time + 4500) {
		App->particles->enemy_shot.speed.x = (position.x - App->player->position.x) * -0.007;
		App->particles->enemy_shot.speed.y = (position.y - App->player->position.y) * -0.007;
		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, ColliderType::ENEMY_SHOT);
		time = current_time;
	}

	Enemy::Update();


}