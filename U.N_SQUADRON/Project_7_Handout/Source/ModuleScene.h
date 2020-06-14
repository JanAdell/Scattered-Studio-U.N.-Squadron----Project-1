#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene(bool startEnabled);

	//Destructor
	~ModuleScene();

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

	bool CleanUp();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTextures[4] = { nullptr };
	int cont[4] = { 0 };

	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;

	enum left_spawner : int //30, un per cada spawn
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
		BOSS_BLACKBIRD,
		
		MAX_LEFT_SPAWNER
	};

	int left_spawn_positions[MAX_LEFT_SPAWNER];
	int left_spawn_counter;


private:
	int yellowFont = -1;
	int greenFont = -1;
};

#endif