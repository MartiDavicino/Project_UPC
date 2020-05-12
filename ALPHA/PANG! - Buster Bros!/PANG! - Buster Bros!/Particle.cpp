#include "Particle.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Collider.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed),
										frameCount(p.frameCount), lifetime(p.lifetime)
{

}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Particle::Update()
{
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		// Update the position in the screen

		if (type == PARTICLE_TYPE::INMUNE) {
			position.x = App->player->position.x;
			position.y = App->player->position.y;
		}
		else{
			position.x += speed.x;
			position.y += speed.y;
		}

		

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}

void Particle::SetPos(int x, int y)
{

	position.x = x;
	position.y = y;

}