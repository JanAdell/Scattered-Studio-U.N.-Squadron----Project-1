#ifndef __BOSS_PURPLE_JACKAL_H__
#define __BOSS_PURPLE_JACKAL_H__

#include "Enemy.h"
#include "Path.h"

class Boss_PurpleJackal : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Boss_PurpleJackal(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;
	// A set of steps that define the position in the screen
// And an animation for each step
	Path path;
	Path path2;
	Path path3;

	// The enemy animation
	Animation fly;
	Animation flyup;
	Animation flydown;

	//Shot delay
	unsigned int current_time;
	unsigned int time = 0;
};

#endif 
