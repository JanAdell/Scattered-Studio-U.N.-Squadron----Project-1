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

	matrix[ColliderType::PLAYER][ColliderType::WALL] = true;
	matrix[ColliderType::PLAYER][ColliderType::PLAYER] = false;
	matrix[ColliderType::PLAYER][ColliderType::ENEMY] = true;
	matrix[ColliderType::PLAYER][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::PLAYER][ColliderType::ENEMY_SHOT] = true;

	matrix[ColliderType::ENEMY][ColliderType::WALL] = true;
	matrix[ColliderType::ENEMY][ColliderType::PLAYER] = true;
	matrix[ColliderType::ENEMY][ColliderType::ENEMY] = false;
	matrix[ColliderType::ENEMY][ColliderType::PLAYER_SHOT] = true;
	matrix[ColliderType::ENEMY][ColliderType::ENEMY_SHOT] = false;

	matrix[ColliderType::PLAYER_SHOT][ColliderType::WALL] = true;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::PLAYER] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::ENEMY] = true;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::PLAYER_SHOT][ColliderType::ENEMY_SHOT] = false;

	matrix[ColliderType::ENEMY_SHOT][ColliderType::WALL] = true;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::PLAYER] = true;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::ENEMY] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::PLAYER_SHOT] = false;
	matrix[ColliderType::ENEMY_SHOT][ColliderType::ENEMY_SHOT] = false;
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