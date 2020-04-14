#include "Enemy_BlueJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BlueJet::Enemy_BlueJet(int x, int y) : Enemy(x, y)
{
	/*fly.PushBack({ 5,72,21,22 });
	currentAnim = &fly;
	fly.speed = 0.01f;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ -0.8f , -0.5f }, 100, &fly);
	path.PushBack({ -0.8f , 0.5f }, 100, &fly);
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);*/
}

void Enemy_BlueJet::Update()
{
	/*path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();*/
}