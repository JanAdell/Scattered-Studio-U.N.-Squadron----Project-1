
#ifndef __MODULESCENEWIN_H__
#define __MODULESCENEWIN_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
class ModuleSceneWin : public Module
{
public:
	ModuleSceneWin(bool startEnabled);
	~ModuleSceneWin();


	bool Start() override;
	update_status Update() override;

	update_status PostUpdate() override;

	bool CleanUp() override;
public:
	SDL_Texture* bgTexture = nullptr;
	SDL_Rect screen;
	Uint32 startTime;
	Uint32 endTime;
	Uint32 actualTime;
};
#endif
