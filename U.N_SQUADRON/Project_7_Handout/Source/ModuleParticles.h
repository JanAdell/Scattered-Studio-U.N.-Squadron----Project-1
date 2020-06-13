#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"
#include "ModuleCollisions.h"
#include "p2Point.h"
#include "Application.h"
#include "Animation.h"

#define MAX_ACTIVE_PARTICLES 500

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);;

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, int x, int y, ColliderType colliderType = ColliderType::NONE, uint delay = 0);

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

	// An index to the last added particle
	uint lastParticle = 0;

public:
	//Template particle for an explosion
	Particle explosion;

	//Template particle for a laser
	Particle laser;

	Particle enemy_shot;

	//---Special Weapons---

	//Trilaser
	Particle t_laser1;
	Particle t_laser2;
	Particle t_laser3;

	//StraightLaser
	Particle s_laser;

	//Gunpod 
	Particle g_p_turret;
	Particle g_p_bullets;

	//Downwards missiles
	Particle dw_missile;

	//---Basic enemies---

	//Green fighter claw
	Particle g_claw;
	Particle g_claw_o;

	//White Jet Missile
	Particle w_missile_up;
	Particle w_missile_down;

	//---Boss 1---
	
	//Round Bomb
	Particle round_bomb;
	//Particle round_bomb_explosion;
	Particle subshot1;
	Particle subshot2;
	Particle subshot3;
	Particle subshot4;
	Particle subshot5;
	Particle subshot6;
	Particle subshot7;
	Particle subshot8;

	//Backshot
	Particle backshot;
	
	//Bomb drop
	Particle dropbomb;
	
	//---Boss 2---
	
	//Forward Missile
	Particle f_missile;
	Particle f_missile_explosion;

	//Backwards bomb
	Particle b_bomb;
	Particle b_bomb_explosion;
};

#endif // !__MODULEPARTICLES_H__