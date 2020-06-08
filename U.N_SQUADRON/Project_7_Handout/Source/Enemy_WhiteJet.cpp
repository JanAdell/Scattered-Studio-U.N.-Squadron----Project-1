#include "Enemy_WhiteJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_WhiteJet::Enemy_WhiteJet(int x, int y) : Enemy(x, y)
{

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