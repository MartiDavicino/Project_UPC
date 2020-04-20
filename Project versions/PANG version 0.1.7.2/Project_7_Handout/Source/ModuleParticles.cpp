#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

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
	texture = App->textures->Load("Assets/balls.png");

	// Explosion particle
	/*explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;*/

	dieRightAnim.anim.PushBack({ 6,150,34,24 });
	dieLeftAnim.anim.PushBack({ 40,150,34,24 });
	dieRightAnim.speed.y = dieLeftAnim.speed.y = -10;
	dieRightAnim.speed.x = 2;
	dieLeftAnim.speed.x = -dieRightAnim.speed.x;


	bigExplosion.anim.PushBack({ 120,5,51,42 });
	bigExplosion.anim.PushBack({ 175,6,46,42 });
	bigExplosion.anim.PushBack({ 223,5 , 44,40 });
	bigExplosion.anim.PushBack({ 268,0,52,48});
	bigExplosion.anim.loop = false;

	mediumExplosion.anim.PushBack({ 325,12,33,27 });
	mediumExplosion.anim.PushBack({ 359,9,38,27 });
	mediumExplosion.anim.PushBack({ 402,7,36,36 });
	mediumExplosion.anim.PushBack({ 442,10,36,34 });
	mediumExplosion.anim.loop = false;

	smallExplosion.anim.PushBack({ 495,19,23,18 });
	smallExplosion.anim.PushBack({ 516,18,18,21 });
	smallExplosion.anim.PushBack({ 540,20,22,20 });
	smallExplosion.anim.loop = false;

	blink.anim.PushBack({ 0,180,400,208 });
	blink.anim.loop = false;
	blink.lifetime = 30.0f;
	blink.frameCount = 1;

	//bigExplosion,mediumExplosion, etc . . .



	
	
	

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

	dieLeftAnim.speed.y = dieLeftAnim.speed.y + (gravity * deltaTime);

	dieLeftAnim.position.y = dieLeftAnim.position.y + (dieLeftAnim.speed.y * deltaTime) + (gravity * (deltaTime * deltaTime));
	dieLeftAnim.position.x = dieLeftAnim.position.x + (dieLeftAnim.speed.x * deltaTime);

	dieRightAnim.speed.y = dieRightAnim.speed.y + (gravity * deltaTime);

	dieRightAnim.position.y = dieRightAnim.position.y + (dieRightAnim.speed.y * deltaTime) + (gravity * (deltaTime * deltaTime));
	dieRightAnim.position.x = dieRightAnim.position.x + (dieRightAnim.speed.x * deltaTime);


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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
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
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}