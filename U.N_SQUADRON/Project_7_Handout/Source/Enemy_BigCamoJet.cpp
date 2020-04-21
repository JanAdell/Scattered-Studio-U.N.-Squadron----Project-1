#include "Enemy_BigCamoJet.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BigCamoJet::Enemy_BigCamoJet(int x, int y) : Enemy(x, y)
{
	//fly left
	flyBack.PushBack({ 387,57,32,19 });
	flyBack.speed = 0.01f;

	//fly right
	fly.PushBack({ 126,57,32,19 });
	fly.speed = 0.01f;

	//fly upwards
	flyUp.PushBack({ 263,43,19,33 });
	flyUp.speed = 0.01f;

	//fly down
	flyDown.PushBack({ 265,311,18,31 });
	flyDown.speed = 0.01;

	//turn up from right
	turn.PushBack({ 161,58,30,18 });
	turn.PushBack({ 193,51,23,25 });
	turn.PushBack({ 219,46,15,30 });
	turn.PushBack({ 236,43,9,33 });
	turn.PushBack({ 248,43,12,33 });
	turn.speed = 0.1f;

	//turn up from left
	turnBack.PushBack({ 354,58,30,18 });
	turnBack.PushBack({ 329,51,23,25 });
	turnBack.PushBack({ 311,46,15,30 });
	turnBack.PushBack({ 300,43,9,33 });
	turnBack.PushBack({ 285,43,12,33 });
	turnBack.speed = 0.01f;

	//turn up from right
	turn.PushBack({ 161,58,30,18 });
	turn.PushBack({ 193,51,23,25 });
	turn.PushBack({ 219,46,15,30 });
	turn.PushBack({ 236,43,9,33 });
	turn.PushBack({ 248,43,12,33 });
	turn.speed = 0.1f;

	//turn right from up
	turn2Back.PushBack({ 248,43,12,33 });
	turn2Back.PushBack({ 236,43,9,33 });
	turn2Back.PushBack({ 219,46,15,30 });
	turn2Back.PushBack({ 193,51,23,25 });
	turn2Back.PushBack({ 161,58,30,18 });
	turn2Back.speed = 0.01f;


	

	
	//Path downright
	path.PushBack({ -3.0f , 0.f }, 50, &flyBack);
	path.PushBack({ -1.0f , -1.0f }, 50, &turnBack);
	path.PushBack({ 0.0f, -2.0f }, 50, &flyUp);
	path.PushBack({ 1.0f , -1.0f }, 50, &turn2Back);
	path.PushBack({ 3.0f , 0.f }, 500, &fly);
	/*
	//Path topright
	path.PushBack({ -3.0f , 0.f }, 50, &flyBack);
	path.PushBack({ -1.0f , -1.0f }, 50, &turnBack);
	path.PushBack({ 0.0f, -2.0f }, 50, &flyUp);
	path.PushBack({ 1.0f , -1.0f }, 50, &turn2Back);
	path.PushBack({ 3.0f , 0.f }, 500, &fly);

	//Path downleft
	path.PushBack({ -3.0f , 0.f }, 50, &flyBack);
	path.PushBack({ -1.0f , -1.0f }, 50, &turnBack);
	path.PushBack({ 0.0f, -2.0f }, 50, &flyUp);
	path.PushBack({ 1.0f , -1.0f }, 50, &turn2Back);
	path.PushBack({ 3.0f , 0.f }, 500, &fly);

	//Path topleft
	path.PushBack({ -3.0f , 0.f }, 50, &flyBack);
	path.PushBack({ -1.0f , -1.0f }, 50, &turnBack);
	path.PushBack({ 0.0f, -2.0f }, 50, &flyUp);
	path.PushBack({ 1.0f , -1.0f }, 50, &turn2Back);
	path.PushBack({ 3.0f , 0.f }, 500, &fly);*/
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BigCamoJet::Update()
{
	currentAnim = path.GetCurrentAnimation();

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}