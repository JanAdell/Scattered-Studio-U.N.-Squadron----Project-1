
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
	char livesText[10] = { "\0" };

	SDL_Texture *hud_tex = nullptr;
	
	// Id Fonts
	int yellowFont = -1;
	int greenFont = -1;

public:
	// Score
	uint score = 0;

	SDL_Texture* wp1 = nullptr;
	SDL_Texture* wp2 = nullptr;
	SDL_Texture* wp3 = nullptr;
	SDL_Texture* wp4 = nullptr;
	SDL_Texture* helmet = nullptr;

	// Money
	uint money = 0;

	//Animation lifebar;
	//Animation helmet;


};

#endif // __ModuleHUD_H__