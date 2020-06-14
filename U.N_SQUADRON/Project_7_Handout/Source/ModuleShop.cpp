#include "ModuleShop.h"
#include "ModuleCollisions.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleHud.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include <SDL_mixer\include\SDL_mixer.h>
#include <SDL\include\SDL_keyboard.h>
#include "stdio.h"



ModuleShop::ModuleShop(bool startEnabled) : Module(startEnabled)
{

}

ModuleShop::~ModuleShop()
{

}

bool ModuleShop::Start()
{
	money = 3000;
	LOG("Loading background assets");

	bool ret = true;
	App->hud->Disable();
	bgTexture = App->textures->Load("Assets/shop.png");
	selectorTexture = App->textures->Load("Assets/selector.png");
	App->audio->PlayMusic("Assets/shop.ogg", 1.0f);

	OptionSelection = App->audio->LoadFx("Assets/selection.wav");
	SelectWeapon = App->audio->LoadFx("Assets/selected.wav");
	InsuficientMoney = App->audio->LoadFx("Assets/nomoney.wav");

	WeaponsSold = App->textures->Load("Assets/selectedweapons.png");

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz  0123456789.,ªº?!*$%&()+-/:;<=>@·    " }; hudfont1 = App->fonts->Load("Assets/FontG.png", lookupTable, 5);


	// Resetting the weapons selected in the previous game


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	for (int i = 0; i < 11; i++) {
		weapons[i].selected = false;
	}

	return ret;
}

update_status ModuleShop::Update()
{
	//money = ModuleShop::money_copy;

	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a) {
		select();
	}

	if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN || pad.l_y < 0 || pad.up) && keyDownPad == false) {

		tiendaY -= 1;
		if (tiendaY < 0)tiendaY = 1;
		App->audio->PlayFx(OptionSelection);
		keyDownPad = true;
	}


	if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN || pad.l_y > 0 || pad.down) && keyDownPad == false) {
		tiendaY += 1;
		if (tiendaY > 1)tiendaY = 0;
		App->audio->PlayFx(OptionSelection);
		keyDownPad = true;

	}
	if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || pad.l_x < 0 || pad.left) && keyDownPad == false) {
		tiendaX -= 1;
		if (tiendaX < 0) {
			tiendaX = 5;
			tiendaY += (tiendaY == 1) ? -1 : 1;
		}
		App->audio->PlayFx(OptionSelection);
		keyDownPad = true;
	}

	if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || pad.l_x > 0 || pad.right) && keyDownPad == false) {
		tiendaX += 1;
		if (tiendaX > 5) {
			tiendaX = 0;
			tiendaY += (tiendaY == 1) ? -1 : 1;
		}
		App->audio->PlayFx(OptionSelection);
		keyDownPad = true;
	}

	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN) {
		infiniteMoney = true;
	}

	if (pad.l_y == 0 && pad.l_x == 0 && pad.up == false && pad.down == false && pad.left == false && pad.right == false) {
		keyDownPad = false;
	}

	weaponsition = tiendaX + (6 * tiendaY);

	if (infiniteMoney) {
		money += 10000;
		if (money >= 100000) {
			money += 100000;
		}
		if (money >= 999999) {
			money = 999999;
		}
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->initialScreen);
	}

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
		//App->audio->StopMusic();
		App->transition->FadeToBlack(this, (Module*)App->loose);
	}

	if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
		//App->audio->StopMusic();
		App->transition->FadeToBlack(this, (Module*)App->shop);
	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->scene, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->scene2, 90);
	}
	return update_status::UPDATE_CONTINUE;
}


bool ModuleShop::CleanUp()
{

	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	App->textures->Unload(selectorTexture);
	App->textures->Unload(WeaponsSold);

	App->audio->UnloadFx(OptionSelection);
	App->audio->UnloadFx(SelectWeapon);
	App->audio->UnloadFx(InsuficientMoney);

	App->fonts->UnLoad(hudfont1);


	//App->audio->Disable();
	bgTexture = NULL;
	return true;
}

update_status ModuleShop::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(selectorTexture, 48+(200*tiendaX), 522+(198*tiendaY), NULL);
	
	sprintf_s(moneyText, 10, "%7d", money);
	App->fonts->BlitText(160, 475, hudfont1, moneyText);
	
	SDL_Rect rect;
	rect = { 0,175,165,175 };
	if (weapons[S_SHELL].selected == true) {
		App->render->Blit(WeaponsSold, 875, 540, &rect);
	}

	rect = { 0,0,165,175 };
	if (weapons[T_LASER].selected == true) {
		App->render->Blit(WeaponsSold, 1075, 540, &rect);
	}

	rect = { 0,351,165,175 };
	if (weapons[GUNPOD].selected == true) {
		App->render->Blit(WeaponsSold, 477, 746, &rect);
	}

	rect = { 0,526,165,175 };
	if (weapons[BOMB].selected == true) {
		App->render->Blit(WeaponsSold, 75, 746, &rect);
	}
	

	
	return update_status::UPDATE_CONTINUE;
}

void ModuleShop::select()
{
	switch (weaponsition)
	{
	case CLUSTER:

		break;
	case PHOENIX:

		break;
	case FALCON:

		break;
	case BULLPUP:


		break;
	case S_SHELL:
		if (money >= 20000 || weapons[S_SHELL].selected == true) {
			weapons[S_SHELL].priceWeapon = 20000;
			weapons[S_SHELL].ammo = 10;
			activeSelected(S_SHELL);
		}
		else {
			App->audio->PlayFx(InsuficientMoney);
		}
		break;
	case T_LASER:

		if (money >= 16000 || weapons[T_LASER].selected == true) {
			weapons[T_LASER].priceWeapon = 16000;
			weapons[T_LASER].ammo = 10;
			activeSelected(T_LASER);
		}
		else {
			App->audio->PlayFx(InsuficientMoney);
		}
		break;
	case BOMB:

		if (money >= 2000 || weapons[BOMB].selected == true) {
			weapons[BOMB].priceWeapon = 2000;
			weapons[BOMB].ammo = 50;
			activeSelected(BOMB);
		
		}
		else {
			App->audio->PlayFx(InsuficientMoney);
		}
	
		break;
	case NAPALM:

		break;
	case GUNPOD:
		if (money >= 30000 || weapons[GUNPOD].selected == true) {
			weapons[GUNPOD].priceWeapon = 30000;
			weapons[GUNPOD].ammo = 25;
			activeSelected(GUNPOD);
		}
		else {
			App->audio->PlayFx(InsuficientMoney);
		}
		break;
	case CEILING:
		
		break;
	case MEGACRUSH:

		break;
	case EXIT:

		Mix_HaltMusic();
		
		if (shoploop == false) {
			App->transition->FadeToBlack(this, (Module*)App->scene, 90);
			shoploop = true;
		}
		if (shoploop == true) {
			App->transition->FadeToBlack(this, (Module*)App->scene2, 90);
			shoploop = false;
		}

		break;

	}
}

void ModuleShop::activeSelected(int _weapon) {
	selectedWeapon = _weapon;

	weapons[_weapon].selected = !weapons[_weapon].selected;
	if (weapons[_weapon].selected == true) {
		App->audio->PlayFx(SelectWeapon);
		money -= weapons[_weapon].priceWeapon;
	}
	else {
		money += weapons[_weapon].priceWeapon;
	}
}

