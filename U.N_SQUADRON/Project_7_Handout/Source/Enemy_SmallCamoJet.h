#ifndef __ENEMY_SMALL_CAMO_JET_H__
#define __ENEMY_SMALL_CAMO_JET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SmallCamoJet : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_SmallCamoJet(int x, int y, ENEMY_TYPE e_type);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	
	Path path;
	Path path2;
	

	// The enemy animation
	Animation fly;
	Animation flipfly;
	Animation turn;

	Animation flyback;
	Animation flipflyback;
	Animation turnback;

	//Shot delay
	unsigned int current_time;
	unsigned int time = 0;

	//Particle normalization
	int direction_x;
	int direction_y;
}; 

#endif
