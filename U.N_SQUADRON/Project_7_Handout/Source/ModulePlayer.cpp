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

#include <stdio.h>
#include "SDL/include/SDL_scancode.h"
#include <string>


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 105, 0, 96, 33 });

	// move upwards

	upAnim.PushBack({ 207, 6, 96, 36 });
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 0, 3, 96, 39 });
	downAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz  0123456789.,ªº?!*$%&()+-/:;<=>@·    " };
	yellowFont = App->fonts->Load("Assets/sprites/fonts/Font22.png", lookupTable, 5);
	greenFont = App->fonts->Load("Assets/sprites/fonts/Font444.png", lookupTable, 5);

	score = 0;
	bool ret = true;

	destroyed = false;

	texture = App->textures->Load("Assets/sprites/player/player_sprites.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/music/Build/sfx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/music/Build/sfx/explosion.wav");

	//FONTS
	//scoreFont = App->fonts->Load("assets/Fonts/"".png", "", 1);

	//scoreFont2 = App->fonts->Load("assets/Fonts/"".png", "", 2);
	
	position.x = 100;
	position.y = 600;

	collider = App->collisions->AddCollider({ position.x, position.y, 90, 45 }, ColliderType::PLAYER, this);

	score_value = 0;

	return ret;
}

update_status ModulePlayer::Update()
{

	// Moving the player with the camera scroll

	//TODO Limit camera movement
	App->player->position.x += 1;

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->player->position.x >= App->render->camera.x)
	{
		position.x -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && App->player->position.x < SCREEN_WIDTH + App->render->camera.x - 100)
	{
		position.x += speed;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->player->position.y < SCREEN_HEIGHT- 40)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->player->position.y >= 0)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 90, position.y+10, ColliderType::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}


	//God Mode
	
	if (App->input->keys[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN)
		godModeUpdate();

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;

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

		// draw score & money
		sprintf_s(scoreText, 10, "%5d", score);
		//sprintf_s(moneyText, 10, "%7d", money);

		// Blit 
		App->fonts->BlitText(8, 10, yellowFont, "SCORE");
		//App->fonts->BlitText(132, 10, yellowFont, "LEVEL");
		//App->fonts->BlitText(132, 25, yellowFont, "$");


		std::string s = std::to_string(score_value);
		char const* pchar = s.c_str();
		App->fonts->BlitText(100, 65, greenFont, pchar);

		//App->fonts->BlitText(144, 25, greenFont, moneyText);
		//App->fonts->BlitText(144, 10, greenFont, "      2");

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
	App->fonts->UnLoad(yellowFont);
	//App->fonts->UnLoad(greenFont);

	return true;
}