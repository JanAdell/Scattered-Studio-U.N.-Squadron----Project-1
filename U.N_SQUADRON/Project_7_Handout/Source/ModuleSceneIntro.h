
#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro();

	~ModuleSceneIntro();


	bool Start();
	update_status Update();

	update_status PostUpdate();
	bool CleanUp();

private:
	SDL_Texture* tex = nullptr;
	SDL_Rect screen;
	Uint32 startTime;
	Uint32 endTime;
	Uint32 actualTime;

};
#endif
