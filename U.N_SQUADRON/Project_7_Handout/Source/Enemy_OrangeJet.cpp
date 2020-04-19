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
	turnBack.speed = 0.01f;

	flyBackUp.PushBack({ 300,6,9,33 });
	flyBackUp.PushBack({ 285,6,12,33 });
	flyBackUp.PushBack({ 263,6,19,33 });
	flyBackUp.speed = 0.01f;

	fly.PushBack({ 126,57,32,19 });
	fly.speed = 0.01f;

	turn.PushBack({ 161,21,30,18 });
	turn.PushBack({ 193,14,23,25 });
	turn.PushBack({ 219,9,15,30 });
	turn.speed = 0.01f;

	flyUp.PushBack({ 236,6,9,33 });
	flyUp.PushBack({ 248,6,12,33 });
	flyUp.PushBack({ 263,6,19,33 });
	flyUp.speed = 0.01f;
}

void Enemy_OrangeJet::Update()
{
	/*path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();*/
}