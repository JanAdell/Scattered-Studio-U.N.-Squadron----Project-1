#include "Enemy_RedBird.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedBird::Enemy_RedBird(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	flyAnim.PushBack({5*4,6*4,24*4,24*4});
	flyAnim.PushBack({38 * 4, 6 * 4, 24 * 4, 24 * 4 });
	flyAnim.PushBack({71 * 4, 6 * 4, 24 * 4, 24 * 4 });
	flyAnim.PushBack({104 * 4, 6 * 4, 24 *4, 24 * 4 });
	flyAnim.PushBack({137 * 4, 6 * 4, 24 * 4, 24 * 4 });
	flyAnim.PushBack({170 * 4, 6 * 4, 24 * 4, 24 * 4 });
	flyAnim.PushBack({203 * 4, 6 * 4, 24 * 4, 24 * 4 });
	flyAnim.PushBack({236 * 4, 6 * 4, 24 * 4, 24 * 4 });
	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 24 * 2, 24 * 2 }, ColliderType::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird::Update()
{
	waveRatio += waveRatioSpeed;

	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
