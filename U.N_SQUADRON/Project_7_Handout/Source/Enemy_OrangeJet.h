#ifndef __ENEMY_ORANGE_JET_H__
#define __ENEMY_ORANGE_JET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_OrangeJet : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_OrangeJet(int x, int y);

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
	Path path4;

	// The enemy animation
	Animation fly;
	Animation turn;

	Animation flyBack;
	Animation turnBack;

	Animation turn2;
	Animation turn2Back;

	Animation flyDown;
	Animation flyUp;

	Animation turndown;
	Animation turndownBack;

	Animation turndown2;
	Animation turndownBack2;
};

#endif 
