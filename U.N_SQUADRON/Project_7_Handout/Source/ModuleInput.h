#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300
#define MAX_PADS 4

struct _SDL_GameController;
struct _SDL_Haptic;


enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};
struct GamePad
{
	//Input data
	bool start, back, guide;
	bool x, y, a, b, l1, r1, l3, r3;
	bool up, down, left, right;
	float l2, r2;
	float l_x, l_y, r_x, r_y, l_dz, r_dz;

	//Controller data
	bool enabled;
	int index;
	_SDL_GameController* controller;
	_SDL_Haptic* haptic;

	//Rumble controller
	int rumble_countdown;
	float rumble_strength;
};


class ModuleInput : public Module
{
public:
	// Constructor
	ModuleInput(bool startEnabled);

	// Destructor
	~ModuleInput();

	// Called on application start.
	// Initializes the SDL system for input detection
	bool Init() override;

	// Called at the beginning of the application loop
	// Updates all input data received from SDL
	update_status PreUpdate() override;

	// Called on application exit.
	// Uninitializes the SDL system for input detection
	bool CleanUp() override;

	// Activates SDL device funcionallity when a gamepad has been connected
	void HandleDeviceConnection(int index);

	// Deactivates SDL device funcionallity when a gamepad has been disconnected
	void HandleDeviceRemoval(int index);

	// Called at PreUpdate
	// Iterates through all active gamepads and update all input data
	void UpdateGamepadsInput();

	const char* GetControllerName(int id) const;

public:
	// An array to fill in the state of all the keyboard keys
	KEY_STATE keys[MAX_KEYS] = { KEY_IDLE };

	// An array to fill in all detected gamepads
	GamePad pads[MAX_PADS];

private:
	int controllerCharacterSelection;
	SDL_Event ev;
};


#endif // __ModuleInput_H__