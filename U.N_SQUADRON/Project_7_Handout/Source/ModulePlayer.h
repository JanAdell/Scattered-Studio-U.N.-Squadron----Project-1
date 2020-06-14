#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

enum Player_States
{
	NO_STATE = -1,
	HIT,
	DEAD
};

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;
	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;
	void godModeUpdate();

	bool CleanUp() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Draws gamepad debug info in the screen
	void DebugDrawGamepadInfo();

private:
	int currentCameraX;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 10;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool godMode = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	int score_value;
	int money_value;


	// Font score index
	uint money = 0000000;
	uint score = 000;
	char moneyText[10] = { "\0" };
	int yellowFont = -1;
	int greenFont = -1;

	char scoreText[10] = { "\0" };
	int scoreFont = -1;
	int scoreFont2 = 2;

	char* saludo;

	// Debugdraw for gamepad data
	bool debugGamepadInfo = false;

	//Player HP system
	bool hit;
	int hp;
	int lives;
	int recovery_time;
	int current_time;
	Player_States current_state;
};


#endif //!__MODULE_PLAYER_H__