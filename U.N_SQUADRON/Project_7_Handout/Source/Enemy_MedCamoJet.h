#ifndef __ENEMY_MEDIUM_CAMO_JET_H__
#define __ENEMY_MEDIUM_CAMO_JET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_MedCamoJet : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_MedCamoJet(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	Path path;

	// The enemy animation
	Animation fly;
	Animation turn;

	Animation flyBack;
	Animation turnBack;

	Animation flyOpposite;
	Animation flyBackOpposite;
};

#endif 