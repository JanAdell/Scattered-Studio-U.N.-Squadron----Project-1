#include "Enemy_OrangeJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_OrangeJet::Enemy_OrangeJet(int x, int y) : Enemy(x, y)
{
	//fly left
	flyBack.PushBack({ 387,20,32,19 });
	flyBack.speed = 0.01f;

	//fly right
	fly.PushBack({ 126,20,32,19 });
	fly.speed = 0.01f;

	//fly upwards
	flyUp.PushBack({ 263,6,19,33 });
	flyUp.speed = 0.01f;

	//fly down
	flyDown.PushBack({ 265,348,18,31 });
	flyDown.speed = 0.01;

	//turn up from left
	turn.PushBack({ 161,21,30,18 });
	turn.PushBack({ 193,14,23,25 });
	turn.PushBack({ 219,9,15,30 });
	turn.PushBack({ 236,6,9,33 });
	turn.PushBack({ 248,6,12,33 });
	turn.loop = false;
	turn.speed = 0.08f;

	//turn up from right
	turnBack.PushBack({ 354,21,30,18 });
	turnBack.PushBack({ 329,14,23,25 });
	turnBack.PushBack({ 311,9,15,30 });
	turnBack.PushBack({ 300,6,9,33 });
	turnBack.PushBack({ 285,6,12,33 });
	turnBack.loop = false;
	turnBack.speed = 0.08f;

	//turn left from up
	turn2.PushBack({ 285,6,12,33 });
	turn2.PushBack({ 300,6,9,33 });
	turn2.PushBack({ 311,9,15,30 });
	turn2.PushBack({ 329,14,23,25 });
	turn2.PushBack({ 354,21,30,18 });
	turn2.loop = false;
	turn2.speed = 0.08f;

	//turn right from up
	turn2Back.PushBack({ 248,6,12,33 });
	turn2Back.PushBack({ 236,6,9,33 });
	turn2Back.PushBack({ 219,9,15,30 });
	turn2Back.PushBack({ 193,14,23,25 });
	turn2Back.PushBack({ 161,21,30,18 });
	turn2Back.loop = false;
	turn2Back.speed = 0.08f;

	//turn down from right
	turndownBack.PushBack({ 356,347,29,18 });
	turndownBack.PushBack({ 331,347,22,25 });
	turndownBack.PushBack({ 313,347,14,30 });
	turndownBack.PushBack({ 302,347,8,32 });
	turndownBack.PushBack({ 287,347,11,32 });
	turndownBack.loop = false;
	turndownBack.speed = 0.08f;

	//turn left from down
	turndown2.PushBack({ 287,347,11,32 });
	turndown2.PushBack({ 302,347,8,32 });
	turndown2.PushBack({ 313,347,14,30 });
	turndown2.PushBack({ 331,347,22,25 });
	turndown2.PushBack({ 356,347,29,18 });
	turndown2.loop = false;
	turndown2.speed = 0.08f;

	//turn down from left
	turndown.PushBack({ 163,347,29,18 });
	turndown.PushBack({ 195,347,22,25 });
	turndown.PushBack({ 221,347,14,30 });
	turndown.PushBack({ 238,347,8,32 });
	turndown.PushBack({ 250,347,11,32 });
	turndown.loop = false;
	turndown.speed = 0.08f;

	//turn right from down
	turndownBack2.PushBack({ 250,347,11,32 });
	turndownBack2.PushBack({ 238,347,8,32 });
	turndownBack2.PushBack({ 221,347,14,30 });
	turndownBack2.PushBack({ 195,347,22,25 });
	turndownBack2.PushBack({ 163,347,29,18 });
	turndownBack2.loop = false;
	turndownBack2.speed = 0.08f;

	//Path topright -> complete
	path.PushBack({ -3.0f , 0.f }, 30, &flyBack);
	path.PushBack({ -1.0f , 1.0f }, 60, &turndownBack);
	path.PushBack({ 0.0f, 2.0f }, 50, &flyDown);
	path.PushBack({ 1.0f , 1.0f }, 60, &turndownBack2);
	path.PushBack({ 3.0f , 0.f }, 500, &fly);

	//Path botright -> complete
	path2.PushBack({ -3.0f , 0.f }, 30, &flyBack);
	path2.PushBack({ -1.0f , -1.0f }, 60, &turnBack);
	path2.PushBack({ 0.0f, -2.0f }, 50, &flyUp);
	path2.PushBack({ 1.0f , -1.0f }, 60, &turn2Back);
	path2.PushBack({ 3.0f , 0.f }, 500, &fly);

	//Path topleft
	path3.PushBack({ 4.0f , 0.f }, 70, &fly);
	path3.PushBack({ 1.0f , 1.0f }, 60, &turndown);
	path3.PushBack({ 0.0f, 2.0f }, 50, &flyDown);
	path3.PushBack({ -1.0f , 1.0f }, 60, &turndown2);
	path3.PushBack({ -3.0f , 0.f }, 500, &flyBack);

	//Path downleft
	path4.PushBack({ 4.0f , 0.f }, 70, &fly);
	path4.PushBack({ 1.0f , -1.0f }, 60, &turn);
	path4.PushBack({ 0.0f, -2.0f }, 50, &flyUp);
	path4.PushBack({ -1.0f , -1.0f }, 60, &turn2);
	path4.PushBack({ -3.0f , 0.f }, 500, &flyBack);

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_OrangeJet::Update()
{
	if (spawnPos.x > SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path.GetCurrentAnimation();

		path.Update();
		position = spawnPos + path.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x > SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path2.GetCurrentAnimation();

		path2.Update();
		position = spawnPos + path2.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x < SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path3.GetCurrentAnimation();

		path3.Update();
		position = spawnPos + path3.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x < SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path4.GetCurrentAnimation();

		path4.Update();
		position = spawnPos + path4.GetRelativePosition();
		Enemy::Update();
	}
}