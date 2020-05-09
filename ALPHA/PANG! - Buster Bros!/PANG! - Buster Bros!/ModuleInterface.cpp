#include "ModuleInterface.h"
#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Moduleplayer.h"
#include "InterfaceElement.h"
#include "Drop.h"


#include "SDL/include/SDL_timer.h"
#include<stdio.h>
#include<stdlib.h>




ModuleInterface::ModuleInterface(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_INTERFACE_ELEMENTS; ++i)
		interfaceElements[i] = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_DROPS; ++i)
		drops[i] = nullptr;


}

ModuleInterface::~ModuleInterface()
{

}

bool ModuleInterface::Start()
{

	equippedPosition.x = 90;
	equippedPosition.y = 220;

	LOG("Loading particles");
	texture = App->textures->Load("Assets/Interface.png");

	
	//Interface Elements
	zeroLife.anim.PushBack({ 0,0,0,0 });
	oneLife.anim.PushBack({ 0,258,15,16 });
	secondLife.anim.PushBack({ 0,258,32,16 });
	thirdLife.anim.PushBack({ 0,258,48,16 });
	fourthLife.anim.PushBack({ 0,258,64,16 });
	UI.anim.PushBack({0,0,380,240});

	UI.anim.loop=zeroLife.anim.loop = oneLife.anim.loop = secondLife.anim.loop = thirdLife.anim.loop = true;
	


	
	Blink.anim.loop = true;


	//Drops
	hookDrop.anim.PushBack({71,255,17,17}); 
	hookDrop.blink.PushBack({160,258,14,14 });
	/*hookDrop.idle.PushBack({ 0,0,200,200 });
	hookDrop.blink.PushBack({ 0,0,200,200});*/
	hookDrop.anim.loop = hookDrop.blink.loop = true;
	hookDrop.blink.speed = 2;

	inmuneDrop.anim.PushBack({ 9,283,22,22 });
	inmuneDrop.anim.PushBack({ 43,280,25,25 });
	inmuneDrop.anim.PushBack({ 81,280,25,25 });
	inmuneDrop.anim.PushBack({ 117,280,27,27 });
	inmuneDrop.anim.PushBack({ 155,280,27,27 });
	inmuneDrop.anim.PushBack({ 192,280,27,27 });
	inmuneDrop.anim.PushBack({ 229,280,27,27 });
	inmuneDrop.anim.PushBack({ 117,280,27,27 });
	inmuneDrop.anim.PushBack({ 229,283,27,27 });
	inmuneDrop.anim.loop = true;

	//food
	banana.anim.PushBack({ 70,324,16,16 });
	banana.anim.PushBack({ 70,417,16,16 });

	cherry.anim.PushBack({ 8,324,16,16 });
	cherry.anim.PushBack({ 8,417,16,16 });
	
	//scores
	score400.anim.PushBack({180,545,24,15});  

	score800.anim.PushBack({ 220,545,24,15 });

	score1600.anim.PushBack({ 251,545,40,15 });

	score400.anim.loop = score800.anim.loop = score1600.anim.loop = true;
	
	App->interfaceElements->AddElement(App->interfaceElements->UI, 0, 0);
	/*App->interfaceElements->AddDrop(App->interfaceElements->hookDrop, 40, 40);*/
	App->interfaceElements->AddDrop(App->interfaceElements->hookDrop, equippedPosition.x, equippedPosition.y,DROP_TYPE::HOOK);
	App->interfaceElements->AddElement(App->interfaceElements->score400, 220,40);

	return true;
}

bool ModuleInterface::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_INTERFACE_ELEMENTS; ++i)
	{
		if (interfaceElements[i] != nullptr)
		{
			delete interfaceElements[i];
			interfaceElements[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ACTIVE_DROPS; ++i)
	{
		if (drops[i] != nullptr)
		{
			delete drops[i];
			drops[i] = nullptr;
		}
	}

	

	return true;
}



update_status ModuleInterface::Update()
{
	//for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	//{
	//	Particle* particle = particles[i];

	//	if (particle == nullptr)	continue;

	//	// Call particle Update. If it has reached its lifetime, destroy it
	//	/*if (particle->Update() == false)
	//	{
	//		delete particle;
	//		particles[i] = nullptr;
	//	}*/
	//}
	//App->interfaceElements->AddElement(App->interfaceElements->UI, 0,0);

	

	switch (App->player->lives)
	{
	case(4):
		App->interfaceElements->AddElement(App->interfaceElements->fourthLife, 10, 220);

		break;

	case(3):
		fourthLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->thirdLife, 10, 220);
		
		break;
	case(2):
		thirdLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->secondLife,10, 220);
		
		break;
	case(1):
		secondLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->oneLife, 10,220);
		
		break;
	case(0):
		App->interfaceElements->AddElement(App->interfaceElements->zeroLife, 10,0 );
		
		break;
	}

	switch (App->player->isEquipped)
	{
	case(1):
		break;
	case(2):
		break;
	case(3):
		break;
	case(4):
		break;

	}


	

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleInterface::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_INTERFACE_ELEMENTS; ++i)
	{
		InterfaceElement* element = interfaceElements[i];

		if (element != nullptr && element->display)
		{
			//App->render->Blit(texture, element->position.x, element->position.y, 0);
			//&(element->anim.GetCurrentFrame())
			App->render->Blit(texture,element->position.x, element->position.y, &(element->anim.GetCurrentFrame()));

			
		}
		else if (element != nullptr && element->display == false)
		{
			delete element;
			interfaceElements[i] = nullptr;
		}
	}


	for (uint i = 0; i < MAX_ACTIVE_DROPS; ++i)
	{
		Drop* drop = drops[i];

		if (drop != nullptr && drop->isAlive == true)
		{
			//App->render->Blit(texture, element->position.x, element->position.y, 0);
			//&(element->anim.GetCurrentFrame())
			App->render->Blit(texture, drop->position.x, drop->position.y, &(drop->anim.GetCurrentFrame()));

			//if not detected a collision with either player or floor
			//if (drop.collider)
			//{
			//	drop->position.y++;
			//	drop->collider->SetPos(drop->position.x, drop->position.y);

			//	//if the collision is with the player make the item dissapear
			//	if (1)
			//	{
			//		//equip the item
			//	}
			//}
			//drop->OnCollision(collider);
			

			
		}
		/*else if (drop != nullptr && drop->isAlive == false)
		{
			delete drop;
			drops[i] = nullptr;
		}*/


	}
	return update_status::UPDATE_CONTINUE;
}

void ModuleInterface::AddElement(const InterfaceElement& element, int x, int y)
{
	for (uint i = 0; i < MAX_ACTIVE_INTERFACE_ELEMENTS; ++i)
	{
		//Finding an empty slot for a new element
		if (interfaceElements[i] == nullptr)
		{
			InterfaceElement* e = new InterfaceElement(element);

			//p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			e->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			e->position.y = y;

			e->speed.y = -0.5f;

			

			interfaceElements[i] = e;
			break;
		}
	}
}



void ModuleInterface::AddDrop(const Drop& drop, int x, int y,DROP_TYPE name)
{
	for (uint i = 0; i < MAX_ACTIVE_DROPS; ++i)
	{
		//Finding an empty slot for a new element
		if (drops[i] == nullptr)
		{
			Drop* d = new Drop(drop);

			//p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			d->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			d->position.y = y;

			d->speed.y = 0.5f;
			//Adding the particle's collider
			/*if (colliderType != Collider::Type::NONE)
				e->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);*/
			
			// this collider is creating away from its or
			d->collider = App->collisions->AddCollider(d->anim.GetCurrentFrame(), Collider::Type::DROP, this);
			d->collider->SetPos(x, y);

			d->name = name;

			drops[i] = d;
			break;
		}
	}
}

void ModuleInterface::RandomDrop(int x,int y)
{
	//function to put where a ball explodes
	if (itemsCount == 5)itemsCount = 0;
	//random parameter to determine which is the drop
	switch (itemsCount)
	{
	case(3): //power up
		App->interfaceElements->AddDrop(hookDrop, x, y, DROP_TYPE::FOOD);
		App->interfaceElements->AddDrop(inmuneDrop, x, y, DROP_TYPE::FOOD);
		App->interfaceElements->AddDrop(gunDrop, x, y, DROP_TYPE::FOOD);
	    break;
	case(4): //food
		App->interfaceElements->AddDrop(banana, x, y, DROP_TYPE::FOOD);
		App->interfaceElements->AddDrop(banana, x, y, DROP_TYPE::FOOD);
		break;
	
	}
	itemsCount++;
}