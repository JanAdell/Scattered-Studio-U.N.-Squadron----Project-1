#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleHud.h"
#include "ModuleShop.h"

#include <stdio.h>
#include "SDL/include/SDL_scancode.h"
#include <string>


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 105 * 2, 0, 96 * 2, 33 * 2 });

	// move upwards

	upAnim.PushBack({ 207 * 2, 6 * 2, 96 * 2, 36 * 2 });
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 0, 3 * 2, 96 * 2, 39 * 2 });
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	

	bool ret = true;

	destroyed = false;

	texture = App->textures->Load("Assets/sprites/player/player_sprites2.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/music/Build/sfx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/music/Build/sfx/explosion.wav");

	//FONTS
	//scoreFont = App->fonts->Load("assets/Fonts/"".png", "", 1);

	//scoreFont2 = App->fonts->Load("assets/Fonts/"".png", "", 2);
	
	position.x = 100;
	position.y = 600;

	collider = App->collisions->AddCollider({ position.x, position.y, 180, 90 }, ColliderType::PLAYER, this);

	score_value = 0;
	money_value = 3000;

	return ret;
}

update_status ModulePlayer::Update()
{
	GamePad& pad = App->input->pads[0];

	// Moving the player with the camera scroll

	//TODO Limit camera movement
	App->player->position.x += 1;

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->position.x >= App->render->camera.x || pad.l_x < 0.0f && App->player->position.x >= App->render->camera.x)
	{
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->position.x < SCREEN_WIDTH + App->render->camera.x - PLAYER_WIDTH || pad.l_x > 0.0f && App->player->position.x < SCREEN_WIDTH + App->render->camera.x - PLAYER_WIDTH)
	{
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->player->position.y < SCREEN_HEIGHT - PLAYER_HEIGHT || pad.l_y > 0.0f && App->player->position.y < SCREEN_HEIGHT - PLAYER_HEIGHT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->player->position.y >= 0 || pad.l_y < 0.0f && App->player->position.y >= 0)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 140, position.y + 30, ColliderType::PLAYER_SHOT);
		//App->particles->AddParticle(App->particles->f_missile, position.x + 300, position.y + 30, ColliderType::FRONTMISSILE);


		App->audio->PlayFx(laserFx);
	}

	//if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN == KEY_STATE::KEY_DOWN) {
	//	App->particles->AddParticle(App->particles->dw_missile, position.x + 140, position.y + 30, ColliderType::BOMB);
	//	App->audio->PlayFx(laserFx);

	//}

	if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN == KEY_STATE::KEY_DOWN)
	{
		switch (App->shop->selectedWeapon) {

		case App->shop->BOMB:
			App->particles->AddParticle(App->particles->dw_missile, position.x + 140, position.y + 30, ColliderType::BOMB);
			App->audio->PlayFx(laserFx);
			break;

		case App->shop->S_SHELL:
			App->particles->AddParticle(App->particles->s_laser, position.x + 140, position.y + 30, ColliderType::S_LASER);
			App->audio->PlayFx(laserFx);
			break;

		case App->shop->T_LASER:
			App->particles->AddParticle(App->particles->t_laser1, position.x + 140, position.y + 30, ColliderType::T_LASER);
			App->particles->AddParticle(App->particles->t_laser2, position.x + 140, position.y + 30, ColliderType::T_LASER);
			App->particles->AddParticle(App->particles->t_laser3, position.x + 140, position.y + 30, ColliderType::T_LASER);
			App->audio->PlayFx(laserFx);
			break;

		}

	}

		//God Mode

		if (App->input->keys[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN)
			godModeUpdate();

		// If no up/down movement detected, set the current animation back to idle
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
			currentAnimation = &idleAnim;

		// Switch gamepad debug info
		if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
			debugGamepadInfo = !debugGamepadInfo;


		collider->SetPos(position.x, position.y);

		currentAnimation->Update();



		return update_status::UPDATE_CONTINUE;
	}




update_status ModulePlayer::PostUpdate()
{

	

	if (!destroyed)
	{  
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);

	
		

	

	}

	return update_status::UPDATE_CONTINUE;
}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && godMode == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, ColliderType::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, ColliderType::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, ColliderType::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, ColliderType::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, ColliderType::NONE, 21);


		App->audio->PlayFx(explosionFx);

		destroyed = true;

	}
		
}

void ModulePlayer::godModeUpdate()
{
	godMode = !godMode;
}

bool ModulePlayer::CleanUp() {
	bool ret = true;

	App->textures->Unload(texture);
	collider->pendingToDelete = true;

	return true;
}