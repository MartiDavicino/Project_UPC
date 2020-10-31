#include "Rope.h"

#include "Collider.h"
#include "Application.h"
#include "ModuleCollisions.h"

Rope::Rope()
{
	position.SetToZero();
	speed.SetToZero();
	

	
}

Rope::Rope(const Rope& r) : anim(r.anim), position(r.position), speed(r.speed),
frameCount(r.frameCount), lifetime(r.lifetime)
{

}

Rope::~Rope()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Rope::Update()
{
	bool ret = true;
	frameCount++;
	
	if (type != ROPE_TYPE::STATIC_HOOK)
	{
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
			if (type != ROPE_TYPE::STATIC_HOOK)
			{
				
			}
			position.x += speed.x;
			position.y += speed.y;
			if (collider != nullptr && type != ROPE_TYPE::SHOT)
			{
			}
			collider->SetPos(position.x, position.y);
		}
	}
	return ret;
}