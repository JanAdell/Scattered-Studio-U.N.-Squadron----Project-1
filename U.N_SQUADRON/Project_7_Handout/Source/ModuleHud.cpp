#include "ModuleHud.h"
#include "Application.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include <stdio.h>

ModuleHud::ModuleHud(bool startEnabled) : Module(startEnabled) {}

ModuleHud::~ModuleHud() {}

bool ModuleHud::Start() {
	bool ret = true;
	
	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz  0123456789.,ªº?!*$%&()+-/:;<=>@·    " };
	yellowFont = App->fonts->Load("Assets/sprites/fonts/Font2.png", lookupTable, 5);
	greenFont = App->fonts->Load("Assets/sprites/fonts/Font4.png", lookupTable, 5);
	hud_tex = App->textures->Load("Assets/hud.png");
	score = 0;
	money = 0;
	return ret;
}

update_status ModuleHud::PostUpdate() {
	update_status ret = update_status::UPDATE_CONTINUE;

	App->render->Blit(hud_tex, 0, 0, NULL);
	// draw score & money
	sprintf_s(scoreText, 10, "%7d", score);
	sprintf_s(moneyText, 10, "%7d", money);

	// Blit 
	App->fonts->BlitText(8, 10, yellowFont, "SCORE");
	App->fonts->BlitText(132, 10, yellowFont, "LEVEL");
	App->fonts->BlitText(132, 25, yellowFont, "$");
	App->fonts->BlitText(10, 25, greenFont, scoreText);
	App->fonts->BlitText(144, 25, greenFont, moneyText);
	App->fonts->BlitText(144, 10, greenFont, "      2");

	return ret;
}

bool ModuleHud::CleanUp() {
	bool ret = true;

	App->fonts->UnLoad(yellowFont);
	App->fonts->UnLoad(greenFont);

	return ret;
}