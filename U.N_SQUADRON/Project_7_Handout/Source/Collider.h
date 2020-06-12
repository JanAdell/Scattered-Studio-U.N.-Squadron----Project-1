#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 5

class Module;

enum ColliderType
{
	NONE = -1,
	WALL,
	PLAYER,
	ENEMY,
	PLAYER_SHOT,
	ENEMY_SHOT,
	S_LASER,
	T_LASER,
	BOMB,
	GUNPOD,
	ROUND_BOMB,
	BACKSHOT,
	AIRDROP,
	FRONTMISSILE,
	BACKBOMB,
	CLAW,

	MAX
};


struct Collider
{
	
	//Methods
	Collider(SDL_Rect rectangle, ColliderType type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	ColliderType type;
	
	int hp;
	//int dmg;
	Module* listeners[MAX_LISTENERS] = { nullptr };

};


#endif // !__COLLIDER_H__

