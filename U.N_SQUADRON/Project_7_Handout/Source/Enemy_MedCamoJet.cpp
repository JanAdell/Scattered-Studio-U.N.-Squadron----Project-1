#include "Enemy_MedCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_MedCamoJet::Enemy_MedCamoJet(int x, int y) : Enemy(x, y)
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

	fly.PushBack({ 275,96,30,9 });
	fly.speed = 0.01f;

	turn.PushBack({ 161,21,30,18 });
	turn.PushBack({ 193,14,23,25 });
	turn.PushBack({ 219,9,15,30 });
	turn.speed = 0.01f;

	flyOpposite.PushBack({ 236,6,9,33 });
	flyOpposite.PushBack({ 248,6,12,33 });
	flyOpposite.PushBack({ 263,6,19,33 });
	flyOpposite.speed = 0.01f;

	//path
	path.PushBack({ -4.0f , 0.f }, 100, &flyBack);
	path.PushBack({ 0.0f , 2.0f }, 50, &turnBack);
	path.PushBack({ 4.0f , 0.f }, 3000, &flyBackOpposite);
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_MedCamoJet::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}