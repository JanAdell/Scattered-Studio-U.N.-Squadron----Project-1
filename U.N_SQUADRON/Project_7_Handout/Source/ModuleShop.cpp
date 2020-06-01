#include "ModuleShop.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleHud.h"


ModuleShop::ModuleShop(bool startEnabled) : Module(startEnabled)
{

}

ModuleShop::~ModuleShop()
{

}

bool ModuleShop::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	App->hud->Disable();
	bgTexture = App->textures->Load("Assets/shop.png");
	selectorTexture = App->textures->Load("Assets/selector.png");
	//App->audio->PlayMusic("", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status ModuleShop::Update()
{

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)
	{
		tiendaY -= 1;
		if (tiendaY <0)
		{
			tiendaY = 1;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN)
	{
		tiendaY += 1;
		if(tiendaY>1)
		{
			tiendaY = 0;
		}
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
	{
		tiendaX -= 1;
		if (tiendaX <0)
		{
			tiendaX = 5;
		}
	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
	{
		tiendaX += 1;
		if (tiendaX > 5)
		{
			tiendaX = 0;
		}
	}

	wpos = tiendaX + (6 * tiendaY);

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->transition->FadeToBlack(this, (Module*)App->scene, 90);

	}

	LOG("Weapon Position %d \n",wpos);
	return update_status::UPDATE_CONTINUE;
}

bool ModuleShop::CleanUp()
{
	//Enable (and properly disable) the player module
	App->textures->Unload(bgTexture);
	App->textures->Unload(selectorTexture);
	//App->audio->Disable();
	bgTexture = NULL;
	return true;
}

update_status ModuleShop::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(selectorTexture, 42+(185*tiendaX), 522+(200*tiendaY), NULL);
	return update_status::UPDATE_CONTINUE;
}

void ModuleShop::select()
{
	switch (wpos)
	{
	case Cluster:
		break;
	case Phoenix:
		break;
	case Falcon:
		break;
	case Bullpup:
		break;
	case S_Shell:
		break;
	case T_Laser:
		break;
	case Bomb:
		break;
	case Napalm:
		break;
	case Gunpod:
		break;
	case Ceiling:
		break;
	case MegaCrush:
		break;
	case Exit:
		App->transition->FadeToBlack(this, (Module*)App->scene, 90);
		break;
	}
}