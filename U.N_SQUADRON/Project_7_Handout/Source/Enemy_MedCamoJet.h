#ifndef __ENEMY_MEDIUM_CAMO_JET_H__
#define __ENEMY_MEDIUM_CAMO_JET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_MedCamoJet : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_MedCamoJet(int x, int y, ENEMY_TYPE e_type);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:

	Path path;
	Path path2;
	
	// The enemy animation
	Animation fly;
	Animation flyback;
	Animation turn;
	Animation turnback;
	Animation flyreverse;
	Animation flyreverseback;

	//Shot delay
	unsigned int current_time;
	unsigned int time = 0;

	//Particle normalization
	float direction_x;
	float direction_y;
};

#endif 