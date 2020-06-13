#include "Boss_PurpleJackal.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Boss_PurpleJackal::Boss_PurpleJackal(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	hp = 50;
	enemy_type = e_type;
	
	fly.PushBack({ 43,621,160,60 });

	flyup.PushBack({ 227,605,160,76 });
	
	flydown.PushBack({ 407,581,160,100 });

	collider = App->collisions->AddCollider({ 0, 0, 160, 76 }, ColliderType::ENEMY, (Module*)App->enemies);
	
	path.PushBack({ 5.0f, 0.0f }, 50, &fly);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, 4.0f }, 150, &flydown);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, -4.0f }, 150, &flyup);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, 4.0f }, 150, &flydown);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 10.0f, -4.0f }, 1500, &flyup);

	path2.PushBack({ -3.0f, 4.0f }, 300, &flyup);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ 4.0f, -4.0f }, 200, &flydown);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ -3.0f, 4.0f }, 200, &flydown);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ -3.0f, -4.0f }, 1500, &flyup);
	//path2.loop = true;

	path3.PushBack({ -5.0f,0.0f }, 100, &fly);
	path3.PushBack({ -3.0f, 4.0f }, 300, &flyup);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ 4.0f, -4.0f }, 200, &flydown);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ -3.0f, 4.0f }, 200, &flydown);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ -3.0f, -4.0f }, 1500, &flyup);

	//path3.PushBack({ -5.0f,0.0f }, 100, &fly);
	//path3.PushBack({ 1.0f,0.0f }, 10000000, &fly);
	
	path3.PushBack({ -5.0f,0.0f }, 100, &fly);
	path3.PushBack({ 1.0f,0.0f }, 10000000, &fly);
}

void Boss_PurpleJackal::Update()
{
	currentAnim = path3.GetCurrentAnimation();

	path3.Update();
	position = spawnPos + path3.GetRelativePosition();

	current_time = SDL_GetTicks();



	
	if (App->player->position.x >= position.x && App->player->position.y <= position.y) {
		if (front == false) {
			App->particles->AddParticle(App->particles->f_missile, position.x + 160, position.y + 40, ColliderType::FRONTMISSILE);
			
			front = true;
		}
	}
	else front = false;

	if (App->player->position.x <= position.x+160 && App->player->position.y >= position.y+80) {
		if (back == false) {
			App->particles->AddParticle(App->particles->b_bomb, position.x , position.y + 20, ColliderType::BACKBOMB);
			App->particles->AddParticle(App->particles->b_bomb, position.x + 30, position.y + 40, ColliderType::BACKBOMB);
			App->particles->AddParticle(App->particles->b_bomb, position.x + 60, position.y + 20, ColliderType::BACKBOMB);
			App->particles->AddParticle(App->particles->b_bomb, position.x + 90, position.y + 40, ColliderType::BACKBOMB);
			App->particles->AddParticle(App->particles->b_bomb, position.x + 120, position.y + 20, ColliderType::BACKBOMB);
			App->particles->AddParticle(App->particles->b_bomb, position.x + 150, position.y + 40, ColliderType::BACKBOMB);
			

			back = true;
		}
	}
	else back = false;

	Enemy::Update();
	
}