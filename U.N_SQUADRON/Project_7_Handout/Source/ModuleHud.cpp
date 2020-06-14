#include "ModuleHud.h"
#include "Application.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleShop.h"
#include <string>
#include <stdio.h>

ModuleHud::ModuleHud(bool startEnabled) : Module(startEnabled) {}

ModuleHud::~ModuleHud() {}

bool ModuleHud::Start() {
	bool ret = true;
	
	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz  0123456789.,ªº?!*$%&()+-/:;<=>@·    " };	yellowFont = App->fonts->Load("Assets/FontY.png", lookupTable, 5);
	greenFont = App->fonts->Load("Assets/FontG.png", lookupTable, 5);
	wp1 = App->textures->Load("Assets/sprites/hud/WEAPONSBOMB.png");
	wp2 = App->textures->Load("Assets/sprites/hud/WEAPONSGUNPOD.png");
	wp3 = App->textures->Load("Assets/sprites/hud/WEAPONSS_SHELL.png");
	wp4 = App->textures->Load("Assets/sprites/hud/WEAPONST_LASER.png");

	score = 0;
	money = 0;
	return ret;
}

update_status ModuleHud::PostUpdate() {
	update_status ret = update_status::UPDATE_CONTINUE;
	
	// draw score & money
	sprintf_s(scoreText, 10, "%7d", score);
	sprintf_s(moneyText, 10, "%7d", App->shop->money);

	switch (App->shop->selectedWeapon) {
	case App->shop->BOMB:
		App->render->Blit(wp1, App->render->camera.x + 100, 0, NULL);
		App->fonts->BlitText(900, 878, yellowFont, "BOMB");


		break;

	case App->shop->S_SHELL:
		App->render->Blit(wp3, App->render->camera.x + 100, 0, NULL);
		App->fonts->BlitText(900, 878, yellowFont, "S.SHELL");



		break;

	case App->shop->T_LASER:
		App->render->Blit(wp4, App->render->camera.x + 100, 0, NULL);
		App->fonts->BlitText(900, 878, yellowFont, "T.LASER");


		break;
	case App->shop->GUNPOD:
		App->render->Blit(wp2, App->render->camera.x + 100, 0, NULL);
		App->fonts->BlitText(900, 878, yellowFont, "GUNPOD");

		break;
		
	}

// Blit 
	App->fonts->BlitText(8, 10, yellowFont, "SCORE");
	App->fonts->BlitText(440, 10, yellowFont, "LEVEL");
	App->fonts->BlitText(440, 100, yellowFont, "$");

	std::string s = std::to_string(score);
	std::string d = std::to_string(App->shop->money);
	char const* pchar = s.c_str();
	char const* dchar = d.c_str();
	//Score value
	App->fonts->BlitText(100, 65, greenFont, pchar);
	//Money value

	App->fonts->BlitText(595, 100, greenFont, dchar);
	App->fonts->BlitText(715, 10, greenFont, "2");

	return ret;
}

bool ModuleHud::CleanUp() {
	bool ret = true;
	App->textures->Unload(wp1);
	App->textures->Unload(wp2);
	App->textures->Unload(wp3);
	App->textures->Unload(wp4);
	App->fonts->UnLoad(yellowFont);
	App->fonts->UnLoad(greenFont);

	return ret;
}