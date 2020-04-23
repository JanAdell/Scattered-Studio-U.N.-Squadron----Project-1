
#ifndef __MODULEWELCOMESCENE_H__
#define __MODULEWELCOMESCENE_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include"Path.h"


struct SDL_Texture;

class ModuleWelcomeScene : public Module
{
public:
	ModuleWelcomeScene(bool startEnabled);

	~ModuleWelcomeScene();


	bool Start() override;
	update_status Update() override;

	update_status PostUpdate() override;


public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	

};

#endif