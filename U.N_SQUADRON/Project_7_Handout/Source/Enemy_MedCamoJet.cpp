#include "Enemy_MedCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_MedCamoJet::Enemy_MedCamoJet(int x, int y) : Enemy(x, y)
{
	//fly right
	fly.PushBack({ 275,96,30,9 });
	fly.speed = 0.1f;

	//fly left
	flyback.PushBack({ 240,96,30,9 });
	flyback.speed = 0.01f;
	
	//turn (right to left)
	turnback.PushBack({ 205,88,30,17 });
	turnback.PushBack({ 173,82,30,23 });
	turnback.PushBack({ 147,82,24,23 });
	turnback.PushBack({ 127,82,17,23 });
	turnback.PushBack({ 113,82,10,23 });
	turnback.PushBack({ 94,82,16,23 });
	turnback.PushBack({ 68,82,23,13 });
	turnback.PushBack({ 36,81,30,24 });
	turnback.loop = false;
	turnback.speed = 0.08f;

	//turn (left to right)
	turn.PushBack({ 310,88,30,17 });
	turn.PushBack({ 342,82,30,23 });
	turn.PushBack({ 374,82,24,23 });
	turn.PushBack({ 401,82,17,23 });
	turn.PushBack({ 422,82,10,23 });
	turn.PushBack({ 435,82,16,23 });
	turn.PushBack({ 454,82,23,13 });
	turn.PushBack({ 479,81,30,24 });
	turn.loop = false;
	turn.speed = 0.08f;

	//fly flipped left
	flyreverse.PushBack({ 511,89,30,16 });
	flyreverse.speed = 0.1f;

	//fly flipped right
	flyreverseback.PushBack({ 4,89,30,16 });
	flyreverseback.speed = 0.1f;

	//Left->right->left
	path.PushBack({ 5.0f , 0.f }, 100, &fly);
	path.PushBack({ -0.5f , 0.5f }, 70, &turn);
	path.PushBack({ -3.0f, 0.0f }, 300, &flyreverse);

	//Right->left->right
	path2.PushBack({ -3.0f , 0.f }, 100, &flyback);
	path2.PushBack({ -0.5f , 0.5f }, 70, &turnback);
	path2.PushBack({ 5.0f, 0.0f }, 300, &flyreverseback);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
	

}

void Enemy_MedCamoJet::Update()
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