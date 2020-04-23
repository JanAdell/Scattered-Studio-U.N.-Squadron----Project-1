#include "Enemy_SmallCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Enemy_SmallCamoJet::Enemy_SmallCamoJet(int x, int y) : Enemy(x, y)
{
	//fly right
	fly.PushBack({ 274*2,112 * 2,26 * 2,8 * 2 });
	fly.speed = 0.1f;

	//fly left
	flyback.PushBack({ 245 * 2,112 * 2,26 * 2,8 * 2 });
	flyback.speed = 0.01f;

	//return flip (left)
	flipfly.PushBack({ 479*2,112*2,26*2,10*2 });
	flipfly.PushBack({ 450*2,110*2,26*2,15*2 });
	flipfly.PushBack({ 245*2,112*2,26*2,8 *2});
	flipfly.PushBack({ 215*2,113*2,26*2,10*2 });
	flipfly.PushBack({ 185*2,110*2,26*2,15*2 });
	flipfly.PushBack({ 245*2,112*2,26*2,8 *2});
	flipfly.speed = 0.15f;
	
	//return flip (right)
	flipflyback.PushBack({  40*2,112*2,26*2,10*2 });
	flipflyback.PushBack({  69*2,110*2,26*2,15*2 });
	flipflyback.PushBack({ 274*2,112*2,26*2,8 *2});
	flipflyback.PushBack({ 304*2,113*2,26*2,10*2 });
	flipflyback.PushBack({ 334*2,110*2,26*2,15*2 });
	flipflyback.PushBack({ 274*2,112*2,26*2,8 *2});
	flipflyback.speed = 0.15f;

	//turn (right to left)
	turn.PushBack({ 334*2,110*2,26*2,15*2 });
	turn.PushBack({ 364*2,110*2,19*2,15*2 });
	turn.PushBack({ 387*2,109*2,14*2,17*2 });
	turn.PushBack({ 404*2,108*2, 9*2,19*2 });
	turn.PushBack({ 415*2,109*2,11*2,17*2 });
	turn.PushBack({ 428*2,110*2,18*2,15*2 });
	turn.PushBack({ 450*2,110*2,26*2,15*2 });
	turn.loop = false;
	turn.speed = 0.07f;

	//turn (left to right)
	turnback.PushBack({ 185*2,110*2,26*2,15*2 });
	turnback.PushBack({ 163*2,110*2,19*2,15*2 });
	turnback.PushBack({ 144*2,109*2,14*2,17*2 });
	turnback.PushBack({ 132*2,108*2, 9*2,19*2 });
	turnback.PushBack({ 119*2,109*2,11*2,17*2 });
	turnback.PushBack({  99*2,110*2,18*2,15*2 });
	turnback.PushBack({  69*2,110*2,26*2,15*2 });
	turnback.loop = false;
	turnback.speed = 0.07;

	//Left->right->left
	path.PushBack({ 7.0f , 0.f }, 200, &fly);
	path.PushBack({ -3.0f , 3.0f }, 70, &turn);
	path.PushBack({ -4.0f, 0.0f }, 500, &flipfly);

	//Right->left->right
	path2.PushBack({ -7.0f , 0.f }, 200, &flyback);
	path2.PushBack({ -3.0f , 3.0f }, 70, &turnback);
	path2.PushBack({ 5.0f, 0.0f }, 300, &flipflyback);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, ColliderType::ENEMY, (Module*)App->enemies);


}

void Enemy_SmallCamoJet::Update()
{
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2) {
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