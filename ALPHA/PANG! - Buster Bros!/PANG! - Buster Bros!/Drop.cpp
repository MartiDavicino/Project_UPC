#include "Drop.h"

#include "Collider.h"

Drop::Drop()
{
	position.SetToZero();
	//speed.SetToZero();
	//Set an starting vertical speed
	
}

Drop::Drop(const Drop& d) : idle(d.idle), position(d.position), speed(d.speed),
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
		idle.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime && isBlinking==false)
			{
				//ret = false;
				isBlinking = true;
				frameCount = 0;
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
		
		

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}
	position.y += speed.y;

	return ret;
}