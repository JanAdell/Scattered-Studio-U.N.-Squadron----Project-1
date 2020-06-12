#include "Enemy_WhiteJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_WhiteJet::Enemy_WhiteJet(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	hp = 5;
	enemy_type = e_type;

	fly.PushBack({27,29,100,36});

	flydown.PushBack({251,25,100,40});

	flyup.PushBack({ 135,21,100,44 });

	/*path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});*/

	//-----------DEBUG PATH----------------
	path.PushBack({ 5.0f , 0.f }, 200, &fly );

	collider = App->collisions->AddCollider({ 0, 0, 214 * 2, 78 * 2 }, ColliderType::ENEMY, (Module*)App->enemies);

	time = 0;
}

void Enemy_WhiteJet::Update()
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