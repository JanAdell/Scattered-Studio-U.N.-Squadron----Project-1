#include "Enemy_MedCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_MedCamoJet::Enemy_MedCamoJet(int x, int y) : Enemy(x, y)
{
	//fly right
	fly.PushBack({ 275 * 2,96 * 2,30 * 2,9 * 2 });
	fly.speed = 0.1f;

	//fly left
	flyback.PushBack({ 240 * 2,96 * 2,30 * 2,9 * 2 });
	flyback.speed = 0.01f;
	
	//turn (right to left)
	turnback.PushBack({ 205*2,88*2,30*2,17*2 });
	turnback.PushBack({ 173*2,82*2,30*2,23*2 });
	turnback.PushBack({ 147*2,82*2,24*2,23*2 });
	turnback.PushBack({ 127*2,82*2,17*2,23*2 });
	turnback.PushBack({ 113*2,82*2,10*2,23*2 });
	turnback.PushBack({  94*2,82*2,16*2,23*2 });
	turnback.PushBack({  68*2,82*2,23*2,13*2 });
	turnback.PushBack({  36*2,81*2,30*2,24*2 });
	turnback.loop = false;
	turnback.speed = 0.08f;

	//turn (left to right)
	turn.PushBack({ 310*2,88*2,30*2,17*2 });
	turn.PushBack({ 342*2,82*2,30*2,23*2 });
	turn.PushBack({ 374*2,82*2,24*2,23*2 });
	turn.PushBack({ 401*2,82*2,17*2,23*2 });
	turn.PushBack({ 422*2,82*2,10*2,23*2 });
	turn.PushBack({ 435*2,82*2,16*2,23*2 });
	turn.PushBack({ 454*2,82*2,23*2,13*2 });
	turn.PushBack({ 479*2,81*2,30*2,24*2 });
	turn.loop = false;
	turn.speed = 0.08f;

	//fly flipped left
	flyreverse.PushBack({ 511 * 2,89 * 2,30 * 2,16 * 2 });
	flyreverse.speed = 0.1f;

	//fly flipped right
	flyreverseback.PushBack({ 4 * 2,89 * 2,30 * 2,16 * 2 });
	flyreverseback.speed = 0.1f;

	//Left->right->left
	path.PushBack({ 5.0f , 0.f }, 200, &fly);
	path.PushBack({ -1.0f , 1.0f }, 70, &turn);
	path.PushBack({ -4.0f, 0.0f }, 700, &flyreverse);

	//Right->left->right
	path2.PushBack({ -3.0f , 0.f }, 200, &flyback);
	path2.PushBack({ -0.5f , 0.5f }, 70, &turnback);
	path2.PushBack({ 4.0f, 0.0f }, 700, &flyreverseback);

	collider = App->collisions->AddCollider({ 0, 0, 48, 24 }, ColliderType::ENEMY, (Module*)App->enemies);
	
	time = 0;

	

}

void Enemy_MedCamoJet::Update()
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
	if (current_time > time + 4500) {
		App->particles->enemy_shot.speed.x = (position.x - App->player->position.x)*-0.007;
		App->particles->enemy_shot.speed.y = (position.y - App->player->position.y)*-0.007;
		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, ColliderType::ENEMY_SHOT);
		time = current_time;
	}

}