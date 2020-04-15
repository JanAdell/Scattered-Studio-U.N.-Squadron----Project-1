#include "Enemy_BlueJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BlueJet::Enemy_BlueJet(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 308,131,30,9 });
	fly.speed = 0.01f;

	flyBack.PushBack({ 207,131,30,9 });
	flyBack.speed = 0.01f;

	flyUp.PushBack({ 341,129,30,13 });
	flyUp.speed = 0.01f;
	
	flyBackUp.PushBack({ 174,129,30,13 });
	flyBackUp.speed = 0.01f;

	flyDown.PushBack({ 275,131,30,14 });
	flyDown.speed = 0.01f;

	flyBackDown.PushBack({ 240,131,30,14 });
	flyBackDown.speed = 0.01f;



	// TODO 3: Have the Brown Cookies describe a path in the screen
	
	path.PushBack({ 0.5f , -0.5f }, 100, &flyUp);
	path.PushBack({ 0.5f , 0.5f }, 100, &flyDown);
	path.PushBack({ 1.0f , 0.f }, 100, &fly);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueJet::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();

}