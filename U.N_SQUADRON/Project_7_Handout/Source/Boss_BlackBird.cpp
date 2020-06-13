#include "Boss_BlackBird.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Boss_BlackBird::Boss_BlackBird(int x, int y, ENEMY_TYPE e_type) : Enemy(x, y, e_type)
{
	hp = 150;
	
	entry_cond = true;
	entry.PushBack({ 2,1541,556,316 });
	enemy_type = e_type;
	
	backshot.PushBack({ 2,1873,556,316 });
	backshot.PushBack({ 1155,1547,556,316 });
	backshot.PushBack({ 1155,1879,556,316 });
	backshot.loop = false;
	backshot.speed = 0.1f;
	backshot.name[0] = 'b';
	backshot.name[1] = 'a';
	backshot.name[2] = 'c';
	backshot.name[3] = 'k';
	backshot.name[4] = 's';
	backshot.name[5] = 'h';
	backshot.name[6] = 'o';
	backshot.name[7] = 't';
	backshot.name[8] = '\0';
	
	bombs.PushBack({594,1541,556,316});
	bombs.PushBack({594,1873,556,316});
	bombs.PushBack({1747,1547,553,316});
	bombs.PushBack({1747,1879,553,316});
	bombs.loop = false;
	bombs.speed = 0.1f;
	bombs.name[0] = 'b';
	bombs.name[1] = 'o';
	bombs.name[2] = 'm';
	bombs.name[3] = 'b';
	bombs.name[4] = 's';
	bombs.name[5] = '\0';
	
	collider = App->collisions->AddCollider({ 0, 0, 556, 316 }, ColliderType::ENEMY, (Module*)App->enemies);
	
	path.PushBack({ 5.0f,-4.0f }, 150, &entry);
	path.PushBack({ 1.0f, 0.0f }, 50, &entry);
	path.PushBack({ 0.5f, -2.5f }, 170, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.PushBack({ 0.5f,  2.5f }, 150, &bombs);
	path.PushBack({ 1.5f, -2.5f }, 150, &entry);
	path.PushBack({ 0.5f, -2.5f }, 150, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.PushBack({ 0.5f,  2.5f }, 150, &entry);
	path.PushBack({ 1.5f, -2.5f }, 150, &backshot);
	path.PushBack({ 0.5f, -2.5f }, 150, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.PushBack({ 0.5f,  2.5f }, 150, &bombs);
	path.PushBack({ 1.5f, -2.5f }, 150, &entry);
	path.PushBack({ 0.5f, -2.5f }, 150, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.PushBack({ 0.5f,  2.5f }, 150, &entry);
	path.PushBack({ 1.5f, -2.5f }, 150, &backshot);
	path.PushBack({ 0.5f, -2.5f }, 150, &bombs);
	path.PushBack({ 1.5f,  2.5f }, 150, &backshot);
	path.loop = true - 0.5f;


}

void Boss_BlackBird::Update()
{
	path.Update();
	currentAnim = path.GetCurrentAnimation();
	position = spawnPos + path.GetRelativePosition();
	
	current_time = SDL_GetTicks();
	
	if (strcmp(currentAnim->name, "bombs") == 0) {
		//LOG("round_bomb shot frame %f", currentAnim->currentFrame);
		if (bomb_shot == false) {
			App->particles->AddParticle(App->particles->round_bomb, position.x + 200, position.y + 60, ColliderType::ROUND_BOMB);
			App->particles->AddParticle(App->particles->round_bomb, position.x + 250, position.y + 140, ColliderType::ROUND_BOMB);
			bomb_shot = true;
		}

	}
	else bomb_shot = false;

	if (strcmp(currentAnim->name, "backshot") == 0) {
		if (back_shot == false) {
			App->particles->AddParticle(App->particles->backshot, position.x + 200, position.y + 200, ColliderType::BACKSHOT);
			App->particles->AddParticle(App->particles->backshot, position.x + 250, position.y + 200, ColliderType::BACKSHOT);
			App->particles->AddParticle(App->particles->backshot, position.x + 300, position.y + 200, ColliderType::BACKSHOT);
			App->particles->AddParticle(App->particles->backshot, position.x + 350, position.y + 200, ColliderType::BACKSHOT);
			App->particles->AddParticle(App->particles->backshot, position.x + 400, position.y + 200, ColliderType::BACKSHOT);
			App->particles->AddParticle(App->particles->backshot, position.x + 450, position.y + 200, ColliderType::BACKSHOT);
			back_shot = true;
		}
		
	}
	else back_shot = false;

	if (App->player->position.y >= position.y+316) {
		if (under == false) {
			App->particles->AddParticle(App->particles->dropbomb, position.x + 50, position.y + 60, ColliderType::AIRDROP);
			App->particles->AddParticle(App->particles->dropbomb, position.x + 50, position.y + 140, ColliderType::AIRDROP);
			App->particles->AddParticle(App->particles->dropbomb, position.x + 50, position.y + 220, ColliderType::AIRDROP);

			under = true;
		}
	}
	else under = false;

	Enemy::Update();
		
}