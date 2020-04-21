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



	//Topright	
	path.PushBack({ -4.0f , 0.f }, 50, &flyBack);
	path.PushBack({ -3.0f , 3.0f }, 200, &flyBackDown);

	//Botright
	path2.PushBack({ -4.0f , 0.f }, 50, &flyBack);
	path2.PushBack({ -3.0f , -3.0f }, 200, &flyBackUp);

	//Topleft
	path3.PushBack({ 4.0f , 0.f }, 50, &flyBack);
	path3.PushBack({ 3.0f , -3.0f }, 200, &flyDown);

	//Botleft
	path4.PushBack({ 4.0f , 0.f }, 50, &fly);
	path4.PushBack({ 3.0f , 3.0f }, 200, &flyUp);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueJet::Update()
{
	if (spawnPos.x > SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x > SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path2.GetCurrentAnimation();

		path2.Update();
		position = spawnPos + path2.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x < SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path3.GetCurrentAnimation();

		path3.Update();
		position = spawnPos + path3.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x < SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path4.GetCurrentAnimation();

		path4.Update();
		position = spawnPos + path4.GetRelativePosition();
		Enemy::Update();
	}

	/*currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();*/

}