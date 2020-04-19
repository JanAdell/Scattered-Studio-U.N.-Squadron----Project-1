#include "Enemy_BigCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BigCamoJet::Enemy_BigCamoJet(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 387,57,32,19 });
	fly.speed = 0.01f;

	turn.PushBack({ 354,58,30,18 });
	turn.PushBack({ 329,51,23,25 });
	turn.PushBack({ 311,46,15,30 });
	turn.speed = 0.01f;

	flyUp.PushBack({ 300,43,9,33 });
	flyUp.PushBack({ 289,43,12,33 });
	flyUp.PushBack({ 263,43,19,33 });
	flyUp.speed = 0.01f;
}

void Enemy_BigCamoJet::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}