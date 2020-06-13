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
	int moveBG1 = 0;
	int moveBG2 = 1;
	int loopBG = -1;
	int limitBG = 0;
	int Y_BG = 0;



	//Left spawn management state machine
	enum left_spawner : int //30, un per cada spawn
	{
		WHITE_JET_1,		
		WHITE_JET_2,
		WHITE_JET_3,
		WHITE_JET_4,
		WHITE_JET_5,
		WHITE_JET_6,
		PURPLE_JACKAL,

		MAX_LEFT_SPAWNER
		//check if top-spawning units should be spawned from left SM
	};

	int left_spawn_positions[MAX_LEFT_SPAWNER];
	int left_spawn_counter;
	int victory_counter;
};
#endif