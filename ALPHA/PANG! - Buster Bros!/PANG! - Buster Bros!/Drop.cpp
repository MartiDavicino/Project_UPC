#include "Drop.h"

#include "Collider.h"

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

//void OnCollision(Collider* collider)
//{
//	if (collider->type == Collider::Type::FLOOR)
//	{
//		//stop speed and start time count
//	}
//	if (collider->type == Collider::Type::PLAYER)
//	{
//		//equip item
//		
//	}
//		
//
//}

void Drop::OnCollision(Collider* c1, Collider* c2)
{
	
	if (c1 == collider)
	{
		if (c2->type == Collider::Type::FLOOR)
		{
			//stop speed and start time count
		}
		if (c2->type == Collider::Type::PLAYER)
		{
			//equip item
		}
	}

	
}