#include "Drop.h"
#include "Application.h"

//test
#include "ModuleAudio.h"
#include "ModuleParticles.h"

#include "ModuleInterface.h"
#include "Moduleplayer.h"
#include "Collider.h"
#include "ModuleInterface.h"

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
	if (isPlaced == true)
	{
		frameCount++;
	}
	

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		if (isPlaced == true)
		{
			anim.Update();
		}
		

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime )
			{
				ret = false;
				//isBlinking = true;
				//frameCount = 0;
			
			}
			
			
				
		}
		
		// Otherwise the particle is destroyed when the animation is finished
		

		// Update the position in the screen
	
		/*position.x += speed.x;
		position.y += speed.y;
		*/

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
	
	if (d1 == collider || d2 == collider)
	{
		
		if (d1->type == Collider::Type::FLOOR || d2->type == Collider::Type::FLOOR)
		{
			//stop speed and start time count
			isPlaced = true;
		}
		if (d1->type == Collider::Type::PLAYER || d2->type == Collider::Type::PLAYER)
		{
			
			App->audio->PlayFx(App->interfaceElements->objectPickedFX);

			LOG("Item picked");
			lifetime = 1;
			switch (name)
			{
				
			case(DROP_TYPE::FOOD):
				isAlive = false;
				
				App->interfaceElements->AddDrop(App->interfaceElements->score400, position.x, position.y, DROP_TYPE::SCORE);
				//Score++
				break;
			case(DROP_TYPE::HOOK):
				isAlive = false;
				App->player->itemEquipped =ITEM_EQUIPPED::HOOK;
				break;
			case(DROP_TYPE::INMUNE):
				App->player->isInmune = true;
				App->player->inmuneActivated = true;
				isAlive = false;
				break;
			case(DROP_TYPE::GUN):
				isAlive = false;
				App->player->itemEquipped = ITEM_EQUIPPED::GUN;
				break;

			}
		}

		
	}
	

}