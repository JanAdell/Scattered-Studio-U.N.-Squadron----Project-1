#ifndef __MODULE_SCENE_2_H__
#define __MODULE_SCENE_2_H__

#include "Module.h"

#include "Animation.h"

struct SDL_Texture;

class ModuleScene2 : public Module
{
public:
	//Constructor
	ModuleScene2(bool startEnabled);

	//Destructor
	~ModuleScene2();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;
	void updateBackground();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

private:

	// BackGround
	SDL_Texture* bgTexture = nullptr;
	int bg1 = 0;
	int bg2 = 1;
	int bgloop = -1;
	int bgs = 0;
	int bgy = 0;



	//Left spawn management state machine
	/*enum left_spawner : int //30, un per cada spawn
	{
		ORANGE_JET_1,
		BIG_CAMO_JET_1,
		BLUE_JET_1,
		ORANGE_JET_2,
		BIG_CAMO_JET_2,
		BLUE_JETS_2,
		BLUE_JETS_3,
		BIG_CAMO_JET_3,
		BIG_CAMO_JET_4,

		MAX_LEFT_SPAWNER
	};

	int left_spawn_positions[MAX_LEFT_SPAWNER];
	int left_spawn_counter;*/

};
#endif