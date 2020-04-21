#include "Enemy_OrangeJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_OrangeJet::Enemy_OrangeJet(int x, int y) : Enemy(x, y)
{
	flyBack.PushBack({ 387,20,32,19 });
	flyBack.speed = 0.01f;

	turnBack.PushBack({ 354,21,30,18 });
	turnBack.PushBack({ 329,14,23,25 });
	turnBack.PushBack({ 311,9,15,30 });
	turnBack.PushBack({ 300,6,9,33 });
	turnBack.PushBack({ 285,6,12,33 });
	turnBack.speed = 0.01f;
		
	flyBackUp.PushBack({ 263,6,19,33 });
	flyBackUp.speed = 0.01f;

	fly.PushBack({ 126,20,32,19 });
	fly.speed = 0.01f;

	turn.PushBack({ 161,21,30,18 });
	turn.PushBack({ 193,14,23,25 });
	turn.PushBack({ 219,9,15,30 });
	turn.PushBack({ 236,6,9,33 });
	turn.PushBack({ 248,6,12,33 });
	turn.speed = 0.05f;
		
	flyUp.PushBack({ 263,6,19,33 });
	flyUp.speed = 0.01f;

	flyBack.PushBack({ 387,20,32,19 });
	flyBack.speed = 0.01f;
	
	path.PushBack({ -3.0f , 0.f }, 50, &flyBack);
	path.PushBack({ -2.0f , 2.0f }, 50, &turnBack);
	path.PushBack({ 0.0f, 2.0f }, 50, &flyUp);
	path.PushBack({ 3.0f , 0.f }, 500, &fly);
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_OrangeJet::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}