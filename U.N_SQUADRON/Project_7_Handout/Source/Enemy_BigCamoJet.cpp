#include "Enemy_BigCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Enemy_BigCamoJet::Enemy_BigCamoJet(int x, int y) : Enemy(x, y)
{
	//fly left
	flyBack.PushBack({ 774,114,64,38 });
	flyBack.speed = 0.01f;

	//fly right
	fly.PushBack({ 126*2,57 *2,32 *2,19*2 });
	fly.speed = 0.01f;

	//fly upwards
	flyUp.PushBack({ 263 *2,43 *2,19 *2,33 *2 });
	flyUp.speed = 0.01f;

	//fly down
	flyDown.PushBack({ 265 *2,311 *2,18 *2,31 *2 });
	flyDown.speed = 0.01;

	//turn up from left
	turn.PushBack({ 161 *2,58 *2,30 *2,18 *2 });
	turn.PushBack({ 193 *2,51 *2,23 *2,25 *2 });
	turn.PushBack({ 219 *2,46 *2,15 *2,30 *2 });
	turn.PushBack({ 236 *2,43 *2,9 *2,33 *2 });
	turn.PushBack({ 248 *2,43 *2,12 *2,33*2 });
	turn.loop = false;
	turn.speed = 0.08f;

	//turn up from right
	turnBack.PushBack({ 354 *2,58 *2,30 *2,18 *2 });
	turnBack.PushBack({ 329 *2,51 *2,23 *2,25 *2 });
	turnBack.PushBack({ 311*2,46*2,15 *2,30*2 });
	turnBack.PushBack({ 300*2,43*2,9 *2,33 *2});
	turnBack.PushBack({ 285*2,43*2,12 *2,33*2 });
	turnBack.loop = false;
	turnBack.speed = 0.08f;

	//turn left from up
	turn2.PushBack({ 285*2,43*2,12*2,33*2 });
	turn2.PushBack({ 300*2,43*2, 9*2,33*2 });
	turn2.PushBack({ 311*2,46*2,15*2,30*2 });
	turn2.PushBack({ 329*2,51*2,23*2,25*2 });
	turn2.PushBack({ 354*2,58*2,30*2,18*2 });
	turn2.loop = false;
	turn2.speed = 0.08f;

	//turn right from up
	turn2Back.PushBack({ 248*2,43*2,12*2,33*2 });
	turn2Back.PushBack({ 236*2,43*2, 9*2,33*2 });
	turn2Back.PushBack({ 219*2,46*2,15*2,30*2 });
	turn2Back.PushBack({ 193*2,51*2,23*2,25*2 });
	turn2Back.PushBack({ 161*2,58*2,30*2,18*2 });
	turn2Back.loop = false;
	turn2Back.speed = 0.08f;
	
	//turn down from right
	turndownBack.PushBack({ 356*2,310*2,29*2,18*2 });
	turndownBack.PushBack({ 331*2,310*2,22*2,25*2 });
	turndownBack.PushBack({ 313*2,310*2,14*2,30*2 });
	turndownBack.PushBack({ 302*2,310*2, 8*2,32*2 });
	turndownBack.PushBack({ 287*2,310*2,11*2,32*2 });
	turndownBack.loop = false;
	turndownBack.speed = 0.08f;

	//turn left from down
	turndown2.PushBack({ 287*2,310*2,11*2,32*2 });
	turndown2.PushBack({ 302*2,310*2, 8*2,32*2 });
	turndown2.PushBack({ 313*2,310*2,14*2,30*2 });
	turndown2.PushBack({ 331*2,310*2,22*2,25*2 });
	turndown2.PushBack({ 356*2,310*2,29*2,18*2 });
	turndown2.loop = false;
	turndown2.speed = 0.08f;

	//turn down from left
	turndown.PushBack({ 163*2,310*2,29*2,18*2 });
	turndown.PushBack({ 195*2,310*2,22*2,25*2 });
	turndown.PushBack({ 221*2,310*2,14*2,30*2 });
	turndown.PushBack({ 238*2,310*2, 8*2,32*2 });
	turndown.PushBack({ 250*2,310*2,11*2,32*2 });
	turndown.loop = false;
	turndown.speed = 0.08f;

	//turn right from down
	turndownBack2.PushBack({ 250*2,310*2,11*2,32*2 });
	turndownBack2.PushBack({ 238*2,310*2, 8*2,32*2 });
	turndownBack2.PushBack({ 221*2,310*2,14*2,30*2 });
	turndownBack2.PushBack({ 195*2,310*2,22*2,25*2 });
	turndownBack2.PushBack({ 163*2,310*2,29*2,18*2 });
	turndownBack2.loop = false;
	turndownBack2.speed = 0.08f;

	//Path topright -> complete
	path.PushBack({ -6.0f , 0.f }, 40, &flyBack);
	path.PushBack({ -2.0f , 2.0f }, 80, &turndownBack);
	path.PushBack({ 0.0f, 2.0f }, 60, &flyDown);
	path.PushBack({ 2.0f , 2.0f }, 80, &turndownBack2);
	path.PushBack({ 6.0f , 0.f }, 1000, &fly);
	
	//Path botright -> complete
	path2.PushBack({ -6.0f , 0.f }, 40, &flyBack);
	path2.PushBack({ -2.0f , -2.0f }, 80, &turnBack);
	path2.PushBack({ 0.0f, -2.0f }, 80, &flyUp);
	path2.PushBack({ 2.0f , -2.0f }, 60, &turn2Back); 
	path2.PushBack({ 6.0f , 0.f }, 1000, &fly);

	//Path topleft
	path3.PushBack({ 8.0f , 0.f }, 60, &fly);
	path3.PushBack({ 2.0f , 2.0f }, 80, &turndown);
	path3.PushBack({ 0.0f, 2.0f }, 80, &flyDown);
	path3.PushBack({ -2.0f , 2.0f }, 60, &turndown2);
	path3.PushBack({ -6.0f , 0.f }, 1000, & flyBack);

	//Path downleft
	path4.PushBack({ 8.0f , 0.f }, 60, &fly);
	path4.PushBack({ 2.0f , -2.0f }, 80, &turn);
	path4.PushBack({ 0.0f, -2.0f }, 80, &flyUp);
	path4.PushBack({ -2.0f , -2.0f }, 60, &turn2);
	path4.PushBack({ -6.0f , 0.f }, 1000, & flyBack);

	collider = App->collisions->AddCollider({ 0, 0, 64, 64}, ColliderType::ENEMY, (Module*)App->enemies);
}

void Enemy_BigCamoJet::Update()
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
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2 && spawnPos.y < SCREEN_HEIGHT / 2) {
		currentAnim = path3.GetCurrentAnimation();

		path3.Update();
		position = spawnPos + path3.GetRelativePosition();
		Enemy::Update();
	}
	if (spawnPos.x - App->render->camera.x < SCREEN_WIDTH / 2 && spawnPos.y > SCREEN_HEIGHT / 2) {
		currentAnim = path4.GetCurrentAnimation();

		path4.Update();
		position = spawnPos + path4.GetRelativePosition();
		Enemy::Update();
	}
}