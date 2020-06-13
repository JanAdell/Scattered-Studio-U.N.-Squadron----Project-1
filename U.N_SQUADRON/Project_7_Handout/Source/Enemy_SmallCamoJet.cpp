#include "Enemy_SmallCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_SmallCamoJet::Enemy_SmallCamoJet(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	hp = 5;
	enemy_type = e_type;

	//fly right
	fly.PushBack({ 1096,448,104,32 });
	fly.speed = 0.1f;

	//fly left
	flyback.PushBack({ 980,448,104,32 });
	flyback.speed = 0.01f;

	//return flip (left)
	flipfly.PushBack({ 479*4,112*4,26*4,10*4 });
	flipfly.PushBack({ 450*4,110*4,26*4,15*4 });
	flipfly.PushBack({ 245*4,112*4,26*4,8 *4});
	flipfly.PushBack({ 215*4,113*4,26*4,10*4 });
	flipfly.PushBack({ 185*4,110*4,26*4,15*4 });
	flipfly.PushBack({ 245*4,112*4,26*4,8 *4});
	flipfly.speed = 0.15f;
	
	//return flip (right)
	flipflyback.PushBack({  40*4,112*4,26*4,10*4 });
	flipflyback.PushBack({  69*4,110*4,26*4,15*4 });
	flipflyback.PushBack({ 274*4,112*4,26*4,8 *4});
	flipflyback.PushBack({ 304*4,113*4,26*4,10*4 });
	flipflyback.PushBack({ 334*4,110*4,26*4,15*4 });
	flipflyback.PushBack({ 274*4,112*4,26*4,8 *4});
	flipflyback.speed = 0.15f;

	//turn (right to left)
	turn.PushBack({ 334*4,110*4,26*4,15*4 });
	turn.PushBack({ 364*4,110*4,19*4,15*4 });
	turn.PushBack({ 387*4,109*4,14*4,17*4 });
	turn.PushBack({ 404*4,108*4, 9*4,19*4 });
	turn.PushBack({ 415*4,109*4,11*4,17*4 });
	turn.PushBack({ 428*4,110*4,18*4,15*4 });
	turn.PushBack({ 450*4,110*4,26*4,15*4 });
	turn.loop = false;
	turn.speed = 0.07f;

	//turn (left to right)
	turnback.PushBack({ 185*4,110*4,26*4,15*4 });
	turnback.PushBack({ 163*4,110*4,19*4,15*4 });
	turnback.PushBack({ 144*4,109*4,14*4,17*4 });
	turnback.PushBack({ 132*4,108*4, 9*4,19*4 });
	turnback.PushBack({ 119*4,109*4,11*4,17*4 });
	turnback.PushBack({  99*4,110*4,18*4,15*4 });
	turnback.PushBack({  69*4,110*4,26*4,15*4 });
	turnback.loop = false;
	turnback.speed = 0.07;

	//Left->right->left
	path.PushBack({ 6.0f , 0.f }, 100, &fly);
	path.PushBack({ -3.0f , 3.0f }, 70, &turn);
	path.PushBack({ -4.0f, 0.0f }, 500, &flipfly);

	//Right->left->right
	path2.PushBack({ -6.0f , 0.f }, 100, &flyback);
	path2.PushBack({ -3.0f , 3.0f }, 70, &turnback);
	path2.PushBack({ 5.0f, 0.0f }, 300, &flipflyback);

	collider = App->collisions->AddCollider({ 0, 0, 48*2, 24*2 }, ColliderType::ENEMY, (Module*)App->enemies);

	time = 0;
}

void Enemy_SmallCamoJet::Update()
{
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x > SCREEN_WIDTH / 2) {
		currentAnim = path2.GetCurrentAnimation();

		path2.Update();
		position = spawnPos + path2.GetRelativePosition();
		Enemy::Update();
	}

	current_time = SDL_GetTicks();
	if (current_time > time + 6000) {
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