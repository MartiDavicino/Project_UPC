#include "Drop.h"
#include "Application.h"

//test
#include "ModuleAudio.h"
#include "ModuleParticles.h"

#include "ModuleInterface.h"
#include "Moduleplayer.h"
#include "Collider.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"

Drop::Drop()
{
	
	
}

Drop::Drop(const Drop& d) : anim(d.anim), position(d.position), speed(d.speed),
frameCount(d.frameCount), lifetime(d.lifetime)
{

}

Drop::~Drop()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Drop::Update()
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
			if (frameCount >= lifetime && isBlinking==false)
			{
				//ret = false;
				isBlinking = true;
				frameCount = 0;
				return false;
			}
			else if (frameCount >= lifetime)
			{
				//delete drop
			}
			else if (collider)
			{
				//if collision with the player is detected pick the object
			}
				
		}
		// Otherwise the particle is destroyed when the animation is finished
		

		// Update the position in the screen
		position.x += speed.x;
		position.y += speed.y;
		

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}
	

	return ret;
}


const Collider* Drop::GetCollider() const
{
	return collider;
}


void Drop::OnCollision(Collider* d1, Collider* d2)
{
	
	if (d1 == collider)
	{
		if (d2->type == Collider::Type::FLOOR)
		{
			//stop speed and start time count
		}
		if (d2->type == Collider::Type::PLAYER)
		{
			//equip item

			switch (name)
			{
			case(DROP_TYPE::FOOD):
				isAlive = false;
				//Score++
				break;
			case(DROP_TYPE::HOOK):
				isAlive = false;
				App->player->isEquipped = 1;
				break;
			case(DROP_TYPE::INMUNE):
				App->player->isInmune;
				isAlive = false;
				break;
			case(DROP_TYPE::GUN):
				isAlive = false;
				App->player->isEquipped = 2;
				break;

			}
		}

		//test collision
		if (d2->type == Collider::Type::ROPE)
		{
		
		}
	}
	

}