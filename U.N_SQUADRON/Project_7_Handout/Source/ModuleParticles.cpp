#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/sprites/praticles/particles_rz.png");
	//texture = App->textures->Load("Assets/sprites/particles/particles.png");



	// Explosion particle
	explosion.anim.PushBack({123 * 2, 0, 72 * 2, 75 * 2 });
	explosion.anim.PushBack({201 * 2, 0, 87 * 2, 78 * 2 });
	explosion.anim.PushBack({294 * 2, 0, 87 * 2, 81 * 2 });
	explosion.anim.PushBack({309 * 2, 0, 93 * 2, 87 * 2 });
	explosion.anim.PushBack({489 * 2, 0, 96 * 2, 87 * 2 });
	explosion.anim.PushBack({591 * 2, 0, 93 * 2, 84 * 2 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	
	//Player shot
	laser.anim.PushBack({ 9 * 2, 183 * 2, 27 * 2, 18 * 2 });
	laser.anim.PushBack({ 87 * 2, 180 * 2, 24 * 2, 18 * 2 });
	laser.anim.PushBack({ 168 * 2, 183 * 2, 27 * 2, 15 * 2 });
	laser.anim.PushBack({ 237 * 2, 183 * 2, 18 * 2, 12 * 2 });
	laser.anim.PushBack({ 297 * 2, 183 * 2, 27 * 2, 9 * 2 });
	laser.anim.PushBack({ 363 * 2, 183 * 2, 24 * 2, 12 * 2 });
	laser.anim.PushBack({ 426 * 2, 180 * 2, 24 * 2, 15 * 2 });
	laser.anim.PushBack({ 483 * 2, 180 * 2, 24 * 2, 18 * 2 });
	laser.speed.x = 20;
	laser.lifetime = 180;
	laser.anim.speed = 0.3f;

	// Enemy Shot particle
	enemy_shot.anim.PushBack({ 6 * 2, 12 * 2, 21 * 2, 15 * 2 });
	enemy_shot.anim.PushBack({ 36 * 2, 9 * 2, 18 * 2, 21 * 2 });
	enemy_shot.anim.PushBack({ 63 * 2, 12 * 2, 15 * 2, 15 * 2 });
	enemy_shot.anim.PushBack({ 90*2, 9 * 2, 15 * 2, 21 * 2 });
	enemy_shot.anim.speed = 0.3f;
	enemy_shot.lifetime = 200;
	/*enemy_shot.speed.x = 5;
	enemy_shot.speed.y = 5;*/

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}
	//App->textures->Unload();
	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}
		

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, ColliderType colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != ColliderType::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}