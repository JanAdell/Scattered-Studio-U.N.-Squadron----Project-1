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
	
	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz  0123456789.,ªº?!*$%&()+-/:;<=>@·    " };	yellowFont = App->fonts->Load("Assets/sprites/fonts/Font22.png", lookupTable, 5);
	greenFont = App->fonts->Load("Assets/sprites/fonts/Font444.png", lookupTable, 5);

	score = 0;
	money = 0;
	return ret;
}

update_status ModuleHud::PostUpdate() {
	update_status ret = update_status::UPDATE_CONTINUE;
	
	// draw score & money
	sprintf_s(scoreText, 10, "%7d", score);
	sprintf_s(moneyText, 10, "%7d", App->shop->money);


// Blit 
	App->fonts->BlitText(8, 10, yellowFont, "SCORE");
	App->fonts->BlitText(440, 10, yellowFont, "LEVEL");
	App->fonts->BlitText(440, 100, yellowFont, "!");

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

	App->fonts->UnLoad(yellowFont);
	App->fonts->UnLoad(greenFont);

	return ret;
}