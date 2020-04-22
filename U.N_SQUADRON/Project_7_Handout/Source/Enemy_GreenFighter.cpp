#include "Enemy_GreenFighter.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenFighter::Enemy_GreenFighter(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 270, 151, 107, 39 });
	//fly.speed = 0.0f;

	path.PushBack({ 0.01f , -2.0f }, 100, &fly);
	path.PushBack({ -0.01f , 2.0f }, 200, &fly);
	path.PushBack({ -0.01f , -2.0f }, 200, &fly);
	path.PushBack({ 0.01f , 2.0f }, 100, &fly);

	collider = App->collisions->AddCollider({ 0, 0, 107, 39 }, ColliderType::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenFighter::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}