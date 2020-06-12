#ifndef __BOSS_BLACKBIRD_H__
#define __BOSS_BLACKBIRD_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleEnemies.h"

class Boss_BlackBird : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Boss_BlackBird(int x, int y, ENEMY_TYPE e_type);

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

	// The enemy animation
	Animation fly;
	
	/*Animation flyup;
	Animation flydown;*/
	Animation entry;

	Animation backshot;
	Animation bombs;
	Animation drop_bombs;

	Animation backshot_u;
	Animation bombs_u;
	Animation drop_bombs_u;

	//Shot delay
	unsigned int current_time;
	unsigned int time = 0;

	//boss stats
	bool dead;
	bool entry_cond;

	
};

#endif 
