#include "Enemy_GreenFighter.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenFighter::Enemy_GreenFighter(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 550, 302, 214, 78 });
	//fly.speed = 0.0f;

	path.PushBack({ 0.03f , -6.0f }, 300, &fly);
	path.PushBack({ -0.03f , 6.0f }, 600, &fly);
	path.PushBack({ -0.03f , -6.0f }, 600, &fly);
	path.PushBack({ 0.03f , 6.0f }, 300, &fly);

	collider = App->collisions->AddCollider({ 0, 0, 214, 78 }, ColliderType::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenFighter::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}