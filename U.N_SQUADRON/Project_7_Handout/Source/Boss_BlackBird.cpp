#include "Boss_BlackBird.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Boss_BlackBird::Boss_BlackBird(int x, int y) : Enemy(x, y)
{
	hp = 100;
	dead = false;
	entry_cond = true;
	entry.PushBack({ 2,1541,556,316 });

	backshot.PushBack({ 2,1873,556,316 });
	backshot.PushBack({ 1155,1547,556,316 });
	backshot.PushBack({ 1155,1879,556,316 });
	backshot.loop = false;
	backshot.speed = 0.01f;

	bombs.PushBack({594,1541,556,316});
	bombs.PushBack({594,1873,556,316});
	bombs.PushBack({1747,1547,553,316});
	bombs.PushBack({1747,1879,553,316});
	bombs.loop = false;
	bombs.speed = 0.01f;

	collider = App->collisions->AddCollider({ 0, 0, 556, 316 }, ColliderType::ENEMY, (Module*)App->enemies);
	path.PushBack({ 5.0f,-4.0f }, 150, &entry);
	path.PushBack({ 1.0f, 0.0f }, 50, &entry);


}

void Boss_BlackBird::Update()
{
	/*while (entry_cond=true)
	{
		path.Update();
		currentAnim = path.GetCurrentAnimation();
		position = spawnPos + path.GetRelativePosition();
		if (position.x >= SCREEN_WIDTH - 600) {
			entry_cond = false;
		}
	}
	
	if (entry_cond == false) {
		path2.Update();
		currentAnim = path2.GetCurrentAnimation();
		position = spawnPos + path2.GetRelativePosition();
	}*/
	
	path.Update();
	currentAnim = path.GetCurrentAnimation();
	position = spawnPos + path.GetRelativePosition();
		

	current_time = SDL_GetTicks();
	/*if (current_time > time + 4500) {
		App->particles->enemy_shot.speed.x = (position.x - App->player->position.x) * -0.007;
		App->particles->enemy_shot.speed.y = (position.y - App->player->position.y) * -0.007;
		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, ColliderType::ENEMY_SHOT);
		time = current_time;
	}*/

	Enemy::Update();


}