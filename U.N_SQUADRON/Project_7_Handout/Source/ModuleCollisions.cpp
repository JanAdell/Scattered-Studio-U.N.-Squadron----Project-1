#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[ColliderType::WALL][ColliderType::WALL] = false;
	matrix[ColliderType::WALL][ColliderType::PLAYER] = true;
	matrix[ColliderType::WALL][ColliderType::ENEMY] = true;
	matrix[ColliderType::WALL][ColliderType::PLAYER_SHOT] = true;
	matrix[ColliderType::WALL][ColliderType::ENEMY_SHOT] = true;
	matrix[ColliderType::WALL][ColliderType::T_LASER] = true;
	matrix[ColliderType::WALL][ColliderType::BOMB] = true;
	matrix[ColliderType::WALL][ColliderType::GUNPOD] = true;
	matrix[ColliderType::WALL][ColliderType::S_LASER] = true;
	matrix[ColliderType::WALL][ColliderType::ROUND_BOMB] = true;

	matrix[ColliderType::PLAYER][ColliderType::WALL] = true;
	matrix[ColliderType::PLAYER][ColliderType::PLAYER] = false;
	matrix[ColliderType::PLAYER][ColliderType::ENEMY] = true;
	matrix[ColliderType::PLAYER][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::PLAYER][ColliderType::ENEMY_SHOT] = true;
	matrix[ColliderType::PLAYER][ColliderType::T_LASER] = false;
	matrix[ColliderType::PLAYER][ColliderType::BOMB] = false;
	matrix[ColliderType::PLAYER][ColliderType::GUNPOD] = false;
	matrix[ColliderType::PLAYER][ColliderType::S_LASER] = false;
	matrix[ColliderType::PLAYER][ColliderType::ROUND_BOMB] = false; //change

	matrix[ColliderType::ENEMY][ColliderType::WALL] = true;
	matrix[ColliderType::ENEMY][ColliderType::PLAYER] = true;
	matrix[ColliderType::ENEMY][ColliderType::ENEMY] = false;
	matrix[ColliderType::ENEMY][ColliderType::PLAYER_SHOT] = true;
	matrix[ColliderType::ENEMY][ColliderType::ENEMY_SHOT] = false;
	matrix[ColliderType::ENEMY][ColliderType::T_LASER] = true;
	matrix[ColliderType::ENEMY][ColliderType::BOMB] = true;
	matrix[ColliderType::ENEMY][ColliderType::GUNPOD] = true;
	matrix[ColliderType::ENEMY][ColliderType::S_LASER] = true;
	matrix[ColliderType::ENEMY][ColliderType::ROUND_BOMB] = false;

	matrix[ColliderType::PLAYER_SHOT][ColliderType::WALL] = true;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::PLAYER] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::ENEMY] = true;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::ENEMY_SHOT] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::T_LASER] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::BOMB] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::GUNPOD] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::S_LASER] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::ROUND_BOMB] = false;

	matrix[ColliderType::ENEMY_SHOT][ColliderType::WALL] = true;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::PLAYER] = true;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::ENEMY] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::ENEMY_SHOT] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::T_LASER] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::BOMB] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::GUNPOD] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::S_LASER] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::ROUND_BOMB] = false;

	matrix[ColliderType::S_LASER][ColliderType::WALL] = true;
	matrix[ColliderType::S_LASER][ColliderType::PLAYER] = false;
	matrix[ColliderType::S_LASER][ColliderType::ENEMY] = true;
	matrix[ColliderType::S_LASER][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::S_LASER][ColliderType::ENEMY_SHOT] = false;
	matrix[ColliderType::S_LASER][ColliderType::T_LASER] = false;
	matrix[ColliderType::S_LASER][ColliderType::BOMB] = false;
	matrix[ColliderType::S_LASER][ColliderType::GUNPOD] = false;
	matrix[ColliderType::S_LASER][ColliderType::S_LASER] = false;
	matrix[ColliderType::S_LASER][ColliderType::ROUND_BOMB] = false;

	matrix[ColliderType::T_LASER][ColliderType::WALL] = true;
	matrix[ColliderType::T_LASER][ColliderType::PLAYER] = false;
	matrix[ColliderType::T_LASER][ColliderType::ENEMY] = true;
	matrix[ColliderType::T_LASER][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::T_LASER][ColliderType::ENEMY_SHOT] = false;
	matrix[ColliderType::T_LASER][ColliderType::T_LASER] = false;
	matrix[ColliderType::T_LASER][ColliderType::BOMB] = false;
	matrix[ColliderType::T_LASER][ColliderType::GUNPOD] = false;
	matrix[ColliderType::T_LASER][ColliderType::S_LASER] = false;
	matrix[ColliderType::T_LASER][ColliderType::ROUND_BOMB] = false;

	matrix[ColliderType::BOMB][ColliderType::WALL] = true;
	matrix[ColliderType::BOMB][ColliderType::PLAYER] = false;
	matrix[ColliderType::BOMB][ColliderType::ENEMY] = true;
	matrix[ColliderType::BOMB][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::BOMB][ColliderType::ENEMY_SHOT] = false;
	matrix[ColliderType::BOMB][ColliderType::T_LASER] = false;
	matrix[ColliderType::BOMB][ColliderType::BOMB] = false;
	matrix[ColliderType::BOMB][ColliderType::GUNPOD] = false;
	matrix[ColliderType::BOMB][ColliderType::S_LASER] = false;
	matrix[ColliderType::BOMB][ColliderType::ROUND_BOMB] = false;

	matrix[ColliderType::GUNPOD][ColliderType::WALL] = true;
	matrix[ColliderType::GUNPOD][ColliderType::PLAYER] = false;
	matrix[ColliderType::GUNPOD][ColliderType::ENEMY] = true;
	matrix[ColliderType::GUNPOD][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::GUNPOD][ColliderType::ENEMY_SHOT] = false;
	matrix[ColliderType::GUNPOD][ColliderType::T_LASER] = false;
	matrix[ColliderType::GUNPOD][ColliderType::BOMB] = false;
	matrix[ColliderType::GUNPOD][ColliderType::GUNPOD] = false;
	matrix[ColliderType::GUNPOD][ColliderType::S_LASER] = false;
	matrix[ColliderType::GUNPOD][ColliderType::ROUND_BOMB] = false;

	matrix[ColliderType::ROUND_BOMB][ColliderType::WALL] = true;
	matrix[ColliderType::ROUND_BOMB][ColliderType::PLAYER] = false;//change
	matrix[ColliderType::ROUND_BOMB][ColliderType::ENEMY] = false;
	matrix[ColliderType::ROUND_BOMB][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::ROUND_BOMB][ColliderType::ENEMY_SHOT] = false;
	matrix[ColliderType::ROUND_BOMB][ColliderType::T_LASER] = false;
	matrix[ColliderType::ROUND_BOMB][ColliderType::BOMB] = false;
	matrix[ColliderType::ROUND_BOMB][ColliderType::GUNPOD] = false;
	matrix[ColliderType::ROUND_BOMB][ColliderType::S_LASER] = false;
	matrix[ColliderType::ROUND_BOMB][ColliderType::ROUND_BOMB] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

update_status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i) {
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);
				
					
				}
				for (uint i = 0; i < MAX_LISTENERS; ++i) {
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
				}


			}
		}
	}


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return update_status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case ColliderType::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case ColliderType::WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case ColliderType::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case ColliderType::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case ColliderType::PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case ColliderType::ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, ColliderType type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

bool ModuleCollisions::DeleteCollider(Collider* collider) {
	if (collider != nullptr)
	{
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] == collider)
			{
				collider->pendingToDelete = true;
				break;
			}
		}
	}


	return false;
}