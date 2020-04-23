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
	explosion.anim.PushBack({123, 0, 72, 75});
	explosion.anim.PushBack({201, 0, 87, 78});
	explosion.anim.PushBack({294, 0, 87, 81});
	explosion.anim.PushBack({309, 0, 93, 87});
	explosion.anim.PushBack({489, 0, 96, 87});
	explosion.anim.PushBack({591, 0, 93, 84});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	
	//Player shot
	laser.anim.PushBack({ 9, 183, 27, 18 });
	laser.anim.PushBack({ 87, 180, 24, 18 });
	laser.anim.PushBack({ 168, 183, 27, 15 });
	laser.anim.PushBack({ 237, 183, 18, 12 });
	laser.anim.PushBack({ 297, 183, 27, 9 });
	laser.anim.PushBack({ 363, 183, 24, 12 });
	laser.anim.PushBack({ 426, 180, 24, 15 });
	laser.anim.PushBack({ 483, 180, 24, 18 });
	laser.speed.x = 20;
	laser.lifetime = 180;
	laser.anim.speed = 0.3f;

	// Enemy Shot particle
	enemy_shot.anim.PushBack({ 6, 12, 21, 15 });
	enemy_shot.anim.PushBack({ 36, 9, 18, 21 });
	enemy_shot.anim.PushBack({ 63, 12, 15, 15 });
	enemy_shot.anim.PushBack({ 90, 9, 15, 21 });
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