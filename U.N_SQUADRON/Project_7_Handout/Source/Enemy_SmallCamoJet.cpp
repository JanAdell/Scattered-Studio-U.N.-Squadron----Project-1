#include "Enemy_SmallCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_SmallCamoJet::Enemy_SmallCamoJet(int x, int y) : Enemy(x, y)
{
	flyBack.PushBack({ 387,20,32,19 });
	flyBack.speed = 0.01f;

	turnBack.PushBack({ 354,21,30,18 });
	turnBack.PushBack({ 329,14,23,25 });
	turnBack.PushBack({ 311,9,15,30 });
	turnBack.speed = 0.01f;

	flyBackOpposite.PushBack({ 300,6,9,33 });
	flyBackOpposite.PushBack({ 285,6,12,33 });
	flyBackOpposite.PushBack({ 263,6,19,33 });
	flyBackOpposite.speed = 0.01f;

	fly.PushBack({ 126,57,32,19 });
	fly.speed = 0.01f;

	turn.PushBack({ 161,21,30,18 });
	turn.PushBack({ 193,14,23,25 });
	turn.PushBack({ 219,9,15,30 });
	turn.speed = 0.01f;

	flyOpposite.PushBack({ 236,6,9,33 });
	flyOpposite.PushBack({ 248,6,12,33 });
	flyOpposite.PushBack({ 263,6,19,33 });
	flyOpposite.speed = 0.01f;

	path.PushBack({ -3.0f , 0.f }, 100, &flyBack);
	path.PushBack({ 0.0f , 1.0f }, 50, &turnBack);
	path.PushBack({ 3.0f , 0.f }, 3000, &flyBackOpposite);
}

void Enemy_SmallCamoJet::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}