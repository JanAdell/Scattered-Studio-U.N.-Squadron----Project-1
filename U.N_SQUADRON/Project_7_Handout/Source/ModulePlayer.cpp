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
#include "SDL/include/SDL.h"
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
	
	current_state = NO_STATE;
	hp = 2;

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

	time_gp = 0;

	return ret;
}

update_status ModulePlayer::Update()
{
	GamePad& pad = App->input->pads[0];
	current_time = SDL_GetTicks();
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
		
		App->audio->PlayFx(laserFx);
	}


	current_time_gp = SDL_GetTicks();
	if (App->shop->weapons[App->shop->selectedWeapon].ammo > 0)
	{
		switch (App->shop->selectedWeapon) {

		case App->shop->BOMB:
			if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN || pad.x == KEY_STATE::KEY_DOWN) {
				App->particles->AddParticle(App->particles->dw_missile, position.x + 140, position.y + 30, ColliderType::BOMB);
				App->audio->PlayFx(laserFx);
				App->shop->weapons[App->shop->selectedWeapon].ammo--;
			}
			
			break;

		case App->shop->S_SHELL:
			if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN || pad.x == KEY_STATE::KEY_DOWN) {
				App->particles->AddParticle(App->particles->s_laser, position.x + 140, position.y + 30, ColliderType::S_LASER);
				App->audio->PlayFx(laserFx);
				App->shop->weapons[App->shop->selectedWeapon].ammo--;
			}

			break;

		case App->shop->T_LASER:
			if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN || pad.x == KEY_STATE::KEY_DOWN) {
				App->particles->AddParticle(App->particles->t_laser1, position.x + 140, position.y -20, ColliderType::T_LASER);
				App->particles->AddParticle(App->particles->t_laser2, position.x + 140, position.y, ColliderType::T_LASER);
				App->particles->AddParticle(App->particles->t_laser3, position.x + 140, position.y + 20, ColliderType::T_LASER);
				App->audio->PlayFx(laserFx);
				App->shop->weapons[App->shop->selectedWeapon].ammo--;
			}
			break;
		case App->shop->GUNPOD:
			
			if (App->input->keys[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT && current_time_gp > time_gp + 200 || pad.x == KEY_STATE::KEY_REPEAT && current_time_gp > time_gp + 200) {
				//App->particles->AddParticle(App->particles->g_p_turret, App->player->position.x + 70, App->player->position.y);
				App->particles->AddParticle(App->particles->g_p_bullets, position.x + 80, position.y - 10, ColliderType::GUNPOD);
				App->audio->PlayFx(laserFx);
				App->shop->weapons[App->shop->selectedWeapon].ammo--;
				time_gp = current_time_gp;
			}
			break;

		}
		
	}
	
	if (App->input->keys[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN || pad.y == KEY_STATE::KEY_DOWN) {
		
		int x = int(App->shop->selectedWeapon)+1;
		//LOG("X %d", x);
		for (int i = 0; i <= 10; i++) {
			if (x > 10) {
				x = 0;
			}
			if (App->shop->weapons[x].selected == true) {
				//LOG("found wep");
				App->shop->selectedWeapon = x;
				break;
			}
			x++;
			//LOG("X_v2 %d", x);
		}
	}


	if (hit == true) {
		current_state = HIT;
	}

	if (hp == 0) {
		lives--;
		if (lives == 0) {
			current_state = DEAD;
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
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		
		App->audio->PlayFx(explosionFx);

		lives -= 1;

		//if (lives == 0) {
		App->shop->shoploop = false;

		destroyed = true;
		
		//}
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