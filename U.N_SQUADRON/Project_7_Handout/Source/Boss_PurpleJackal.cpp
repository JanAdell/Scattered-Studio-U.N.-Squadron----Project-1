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
	


}

void Boss_PurpleJackal::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	current_time = SDL_GetTicks();
	

	Enemy::Update();


}