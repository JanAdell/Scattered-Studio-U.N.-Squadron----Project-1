#include "Enemy_GreenFighter.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenFighter::Enemy_GreenFighter(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 257,151,107,39 });
	fly.speed = 0.01f;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenFighter::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}