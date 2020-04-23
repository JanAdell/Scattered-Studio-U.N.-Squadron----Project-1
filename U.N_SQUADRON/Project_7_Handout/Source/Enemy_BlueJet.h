#ifndef __ENEMY_BLUE_JET_H__
#define __ENEMY_BLUE_JET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BlueJet : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BlueJet(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;
	Path path2;
	Path path3;
	Path path4;

	// The enemy animation
	Animation fly;
	Animation flyUp;
	Animation flyDown;
	Animation flyBack;
	Animation flyBackUp;
	Animation flyBackDown;

	//Shot delay
	unsigned int current_time;
	unsigned int time = 0;
};

#endif 
