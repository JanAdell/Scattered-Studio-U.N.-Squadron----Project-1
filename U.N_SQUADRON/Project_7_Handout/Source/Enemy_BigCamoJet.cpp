#include "Enemy_BigCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_BigCamoJet::Enemy_BigCamoJet(int x, int y) : Enemy(x, y)
{
	//fly left
	flyBack.PushBack({ 774*4,114 * 4,64 * 4,38 *4 });
	flyBack.speed = 0.01f;

	//fly right
	fly.PushBack({ 126*4,57 * 4,32 * 4,19*4 });
	fly.speed = 0.01f;

	//fly upwards
	flyUp.PushBack({ 263 * 4,43 * 4,19 * 4,33 * 4 });
	flyUp.speed = 0.01f;

	//fly down
	flyDown.PushBack({ 265 * 4,311 * 4,18 * 4,31 * 4 });
	flyDown.speed = 0.01;

	//turn up from left
	turn.PushBack({ 161 * 4,58 * 4,30 * 4,18 * 4 });
	turn.PushBack({ 193 * 4,51 *4,23 *4,25 *4 });
	turn.PushBack({ 219 *4,46 *4,15 *4,30 *4 });
	turn.PushBack({ 236 *4,43 *4,9 *4,33 *4 });
	turn.PushBack({ 248 *4,43 *4,12 *4,33*4 });
	turn.loop = false;
	turn.speed = 0.08f;

	//turn up from right
	turnBack.PushBack({ 354 *4,58 *4,30 *4,18 *4 });
	turnBack.PushBack({ 329 *4,51 *4,23 *4,25 *4 });
	turnBack.PushBack({ 311*4,46*4,15 *4,30*4 });
	turnBack.PushBack({ 300*4,43*4,9 *4,33 *4});
	turnBack.PushBack({ 285*4,43*4,12 *4,33*4 });
	turnBack.loop = false;
	turnBack.speed = 0.08f;

	//turn left from up
	turn2.PushBack({ 285*4,43*4,12*4,33*4 });
	turn2.PushBack({ 300*4,43*4, 9*4,33*4 });
	turn2.PushBack({ 311*4,46*4,15*4,30*4 });
	turn2.PushBack({ 329*4,51*4,23*4,25*4 });
	turn2.PushBack({ 354*4,58*4,30*4,18*4 });
	turn2.loop = false;
	turn2.speed = 0.08f;

	//turn right from up
	turn2Back.PushBack({ 248*4,43*4,12*4,33*4 });
	turn2Back.PushBack({ 236*4,43*4, 9*4,33*4 });
	turn2Back.PushBack({ 219*4,46*4,15*4,30*4 });
	turn2Back.PushBack({ 193*4,51*4,23*4,25*4 });
	turn2Back.PushBack({ 161*4,58*4,30*4,18*4 });
	turn2Back.loop = false;
	turn2Back.speed = 0.08f;
	
	//turn down from right
	turndownBack.PushBack({ 356*4,310*4,29*4,18*4 });
	turndownBack.PushBack({ 331*4,310*4,22*4,25*4 });
	turndownBack.PushBack({ 313*4,310*4,14*4,30*4 });
	turndownBack.PushBack({ 302*4,310*4, 8*4,32*4 });
	turndownBack.PushBack({ 287*4,310*4,11*4,32*4 });
	turndownBack.loop = false;
	turndownBack.speed = 0.08f;

	//turn left from down
	turndown2.PushBack({ 287*4,310*4,11*4,32*4 });
	turndown2.PushBack({ 302*4,310*4, 8*4,32*4 });
	turndown2.PushBack({ 313*4,310*4,14*4,30*4 });
	turndown2.PushBack({ 331*4,310*4,22*4,25*4 });
	turndown2.PushBack({ 356*4,310*4,29*4,18*4 });
	turndown2.loop = false;
	turndown2.speed = 0.08f;

	//turn down from left
	turndown.PushBack({ 163*4,310*4,29*4,18*4 });
	turndown.PushBack({ 195*4,310*4,22*4,25*4 });
	turndown.PushBack({ 221*4,310*4,14*4,30*4 });
	turndown.PushBack({ 238*4,310*4, 8*4,32*4 });
	turndown.PushBack({ 250*4,310*4,11*4,32*4 });
	turndown.loop = false;
	turndown.speed = 0.08f;

	//turn right from down
	turndownBack2.PushBack({ 250*4,310*4,11*4,32*4 });
	turndownBack2.PushBack({ 238*4,310*4, 8*4,32*4 });
	turndownBack2.PushBack({ 221*4,310*4,14*4,30*4 });
	turndownBack2.PushBack({ 195*4,310*4,22*4,25*4 });
	turndownBack2.PushBack({ 163*4,310*4,29*4,18*4 });
	turndownBack2.loop = false;
	turndownBack2.speed = 0.08f;

	//Path topright -> complete
	path.PushBack({ -6.0f , 0.f }, 40, &flyBack);
	path.PushBack({ -2.0f , 2.0f }, 40, &turndownBack);
	path.PushBack({ 0.0f, 2.0f }, 60, &flyDown);
	path.PushBack({ 2.0f , 2.0f }, 40, &turndownBack2);
	path.PushBack({ 8.0f , 0.f }, 500, &fly);
	
	//Path botright -> complete
	path2.PushBack({ -6.0f , 0.f }, 40, &flyBack);
	path2.PushBack({ -2.0f , -2.0f }, 40, &turnBack);
	path2.PushBack({ 0.0f, -2.0f }, 60, &flyUp);
	path2.PushBack({ 2.0f , -2.0f }, 40, &turn2Back); 
	path2.PushBack({ 8.0f , 0.f }, 500, &fly);

	//Path topleft
	path3.PushBack({ 8.0f , 0.f }, 60, &fly);
	path3.PushBack({ 2.0f , 2.0f }, 40, &turndown);
	path3.PushBack({ 0.0f, 2.0f }, 60, &flyDown);
	path3.PushBack({ -2.0f , 2.0f }, 40, &turndown2);
	path3.PushBack({ -8.0f , 0.f }, 500, & flyBack);

	//Path downleft
	path4.PushBack({ 8.0f , 0.f }, 60, &fly);
	path4.PushBack({ 2.0f , -2.0f }, 40, &turn);
	path4.PushBack({ 0.0f, -2.0f }, 60, &flyUp);
	path4.PushBack({ -2.0f , -2.0f }, 40, &turn2);
	path4.PushBack({ -8.0f , 0.f }, 500, & flyBack);

	collider = App->collisions->AddCollider({ 0, 0, 48 * 2, 48 * 2 }, ColliderType::ENEMY, (Module*)App->enemies);
	time = 0;
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

	current_time = SDL_GetTicks();
	if (current_time > time + 4500) {
		App->particles->enemy_shot.speed.x = (position.x - App->player->position.x) * -0.007;
		App->particles->enemy_shot.speed.y = (position.y - App->player->position.y) * -0.007;
		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y, ColliderType::ENEMY_SHOT);
		time = current_time;
	}
}