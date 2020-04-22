#include "Enemy_SmallCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_SmallCamoJet::Enemy_SmallCamoJet(int x, int y) : Enemy(x, y)
{
	//fly right
	fly.PushBack({ 274,112,26,8 });
	fly.speed = 0.1f;

	//fly left
	flyback.PushBack({ 245,112,26,8 });
	flyback.speed = 0.01f;

	//return flip (left)
	flipfly.PushBack({ 479,112,26,10 });
	flipfly.PushBack({ 450,110,26,15 });
	flipfly.PushBack({ 245,112,26,8 });
	flipfly.PushBack({ 215,113,26,10 });
	flipfly.PushBack({ 185,110,26,15 });
	flipfly.PushBack({ 245,112,26,8 });
	flipfly.speed = 0.15f;
	
	//return flip (right)
	flipflyback.PushBack({ 40,112,26,10 });
	flipflyback.PushBack({ 69,110,26,15 });
	flipflyback.PushBack({ 274,112,26,8 });
	flipflyback.PushBack({ 304,113,26,10 });
	flipflyback.PushBack({ 334,110,26,15 });
	flipflyback.PushBack({ 274,112,26,8 });
	flipflyback.speed = 0.15f;

	//turn (right to left)
	turn.PushBack({ 334,110,26,15 });
	turn.PushBack({ 364,110,19,15 });
	turn.PushBack({ 387,109,14,17 });
	turn.PushBack({ 404,108,9,19 });
	turn.PushBack({ 415,109,11,17 });
	turn.PushBack({ 428,110,18,15 });
	turn.PushBack({ 450,110,26,15 });
	turn.loop = false;
	turn.speed = 0.07f;

	//turn (left to right)
	turnback.PushBack({ 185,110,26,15 });
	turnback.PushBack({ 163,110,19,15 });
	turnback.PushBack({ 144,109,14,17 });
	turnback.PushBack({ 132,108,9,19 });
	turnback.PushBack({ 119,109,11,17 });
	turnback.PushBack({ 99,110,18,15 });
	turnback.PushBack({ 69,110,26,15 });
	turnback.loop = false;
	turnback.speed = 0.07;

	//Left->right->left
	path.PushBack({ 5.0f , 0.f }, 100, &fly);
	path.PushBack({ -0.5f , 0.5f }, 70, &turn);
	path.PushBack({ -3.0f, 0.0f }, 300, &flipfly);

	//Right->left->right
	path2.PushBack({ -3.0f , 0.f }, 100, &flyback);
	path2.PushBack({ -0.5f , 0.5f }, 70, &turnback);
	path2.PushBack({ 5.0f, 0.0f }, 300, &flipflyback);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_SmallCamoJet::Update()
{
	if (spawnPos.x < SCREEN_WIDTH / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x > SCREEN_WIDTH / 2) {
		currentAnim = path2.GetCurrentAnimation();

		path2.Update();
		position = spawnPos + path2.GetRelativePosition();
		Enemy::Update();
	}
}