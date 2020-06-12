#include "Boss_BlackBird.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Boss_BlackBird::Boss_BlackBird(int x, int y) : Enemy(x, y)
{
	hp = 150;
	dead = false;
	entry_cond = true;
	entry.PushBack({ 2,1541,556,316 });

	backshot.PushBack({ 2,1873,556,316 });
	backshot.PushBack({ 1155,1547,556,316 });
	backshot.PushBack({ 1155,1879,556,316 });
	backshot.loop = false;
	backshot.speed = 0.1f;

	bombs.PushBack({594,1541,556,316});
	bombs.PushBack({594,1873,556,316});
	bombs.PushBack({1747,1547,553,316});
	bombs.PushBack({1747,1879,553,316});
	bombs.loop = false;
	bombs.speed = 0.1f;

	collider = App->collisions->AddCollider({ 0, 0, 556, 316 }, ColliderType::ENEMY, (Module*)App->enemies);
	
	path.PushBack({ 5.0f,-4.0f }, 150, &entry);
	path.PushBack({ 1.0f, 0.0f }, 50, &entry);
	path.PushBack({ 1.1f,  0.0f }, 150, &entry);
	path.PushBack({ 0.5f, -2.5f }, 170, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.PushBack({ 0.5f,  2.5f }, 150, &bombs);
	path.PushBack({ 1.5f, -2.5f }, 150, &entry);
	path.PushBack({ 0.5f, -2.5f }, 150, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.PushBack({ 0.5f,  2.5f }, 150, &entry);
	path.PushBack({ 1.5f, -2.5f }, 150, &backshot);
	path.PushBack({ 0.5f, -2.5f }, 150, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.PushBack({ 0.5f,  2.5f }, 150, &bombs);
	path.PushBack({ 1.5f, -2.5f }, 150, &entry);
	path.PushBack({ 0.5f, -2.5f }, 150, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.PushBack({ 0.5f,  2.5f }, 150, &entry);
	path.PushBack({ 1.5f, -2.5f }, 150, &backshot);
	path.PushBack({ 0.5f, -2.5f }, 150, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.loop = true - 0.5f;
}

void Boss_BlackBird::Update()
{
	path.Update();
	currentAnim = path.GetCurrentAnimation();
	position = spawnPos + path.GetRelativePosition();
	

	current_time = SDL_GetTicks();
	
	/*if (current_time ==  4500) {
		App->particles->AddParticle(App->particles->round_bomb, position.x+200, position.y+40, ColliderType::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->round_bomb, position.x+150, position.y+60, ColliderType::ENEMY_SHOT);
	}

	if (current_time == 9000) {
		App->particles->AddParticle(App->particles->round_bomb, position.x, position.y, ColliderType::ENEMY_SHOT);

	}

	if (current_time == 13500) {
		App->particles->AddParticle(App->particles->round_bomb, position.x, position.y, ColliderType::ENEMY_SHOT);

	}

	if (current_time ==18000) {
		App->particles->AddParticle(App->particles->round_bomb, position.x, position.y, ColliderType::ENEMY_SHOT);

	}

	if (current_time == 22500) {
		App->particles->AddParticle(App->particles->round_bomb, position.x, position.y, ColliderType::ENEMY_SHOT);

	}

	if (current_time == 27000) {
		App->particles->AddParticle(App->particles->round_bomb, position.x, position.y, ColliderType::ENEMY_SHOT);

	}

	if (current_time == 31500) {
		App->particles->AddParticle(App->particles->round_bomb, position.x, position.y, ColliderType::ENEMY_SHOT);

	}


	if (App->player->position.y > position.y) {
		for (int i = 0; i < 1; i++) {
			App->particles->AddParticle(App->particles->dropbomb, position.x + 140, position.y + 50, ColliderType::ENEMY_SHOT);
			App->particles->AddParticle(App->particles->dropbomb, position.x + 140, position.y + 100, ColliderType::ENEMY_SHOT);
			App->particles->AddParticle(App->particles->dropbomb, position.x + 140, position.y, ColliderType::ENEMY_SHOT);
		}
	}*/


	Enemy::Update();

	if (hp <= 0) {
		collider->pendingToDelete;
	}
}