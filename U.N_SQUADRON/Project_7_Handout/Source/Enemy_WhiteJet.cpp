#include "Enemy_WhiteJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"

Enemy_WhiteJet::Enemy_WhiteJet(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	hp = 20;
	enemy_type = e_type;

	fly.PushBack({1826,175,100,36});

	flydown.PushBack({2050,171,100,40});

	flyup.PushBack({ 1934,167,100,44 });

	/*path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});
	path.PushBack({});*/

	//-----------DEBUG PATH----------------
	//path.PushBack({ -2.0f , 0.f }, 200, &fly );
		
	path.PushBack({ 5.0f, 0.0f }, 50, &fly);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, 4.0f }, 150, &flydown);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, -4.0f }, 150, &flyup);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 1.0f, 4.0f }, 150, &flydown);
	path.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path.PushBack({ 10.0f, -4.0f }, 1500, &flyup);

	path2.PushBack({ 5.0f, 0.0f }, 100, &fly);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ 1.0f, -4.0f }, 150, &flyup);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ 1.0f, 4.0f }, 150, &flydown);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ 1.0f, -4.0f }, 150, &flydown);
	path2.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path2.PushBack({ 10.0f, 4.0f }, 1500, &flyup);

	
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ 1.0f, -4.0f }, 200, &flyup);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ 1.0f, 4.0f }, 200, &flydown);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ 1.0f, -4.0f }, 200, &flydown);
	path3.PushBack({ 1.0f, 0.0f }, 20, &fly);
	path3.PushBack({ 10.0f, 4.0f }, 1500, &flyup);



	collider = App->collisions->AddCollider({ 0, 0, 100, 40 }, ColliderType::ENEMY, (Module*)App->enemies);

	time = 0;
}

void Enemy_WhiteJet::Update()
{
	
	
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}

	if (spawnPos.y < 0) {
		currentAnim = path3.GetCurrentAnimation();

		path3.Update();
		position = spawnPos + path3.GetRelativePosition();
		Enemy::Update();
	}

	/*if (current_time > time + 4500) {
		App->particles->enemy_shot.speed.x = (position.x - App->player->position.x) * -0.007;
		App->particles->enemy_shot.speed.y = (position.y - App->player->position.y) * -0.007;
		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, ColliderType::ENEMY_SHOT);
		time = current_time;
	}*/
	

}