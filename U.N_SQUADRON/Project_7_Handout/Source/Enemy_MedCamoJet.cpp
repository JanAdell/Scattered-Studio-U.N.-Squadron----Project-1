#include "Enemy_MedCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_MedCamoJet::Enemy_MedCamoJet(int x, int y) : Enemy(x, y)
{
	
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_MedCamoJet::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}