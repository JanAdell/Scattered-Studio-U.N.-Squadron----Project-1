
#ifndef __MODULE_HUD_H__
#define __MODULE_HUD_H__

#include "Module.h"

struct SDL_Texture;

class ModuleHud : public Module
{
public:
	ModuleHud(bool startEnabled);

	~ModuleHud();

	bool Start();

	update_status PostUpdate();

	bool CleanUp();

private:
	char scoreText[10] = { "\0" };
	char moneyText[10] = { "\0" };
	SDL_Texture *hud_tex = nullptr;
	
	// Id Fonts
	int yellowFont = -1;
	int greenFont = -1;

public:
	// Score
	uint score = 0;

	// Money
	uint money = 0;



};

#endif // __ModuleHUD_H__