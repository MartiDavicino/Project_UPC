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
	blackSection.anim.PushBack({ 0,600,400,400 });

	UI.anim.loop=zeroLife.anim.loop = oneLife.anim.loop = secondLife.anim.loop = thirdLife.anim.loop = true;
	
	ready.anim.PushBack({ 0,700,71, 30 });
	ready.anim.PushBack({ 0,700,71, 30 });
	ready.anim.PushBack({ 0,0,0,0 });
	ready.anim.loop = true;
	ready.anim.speed = 40;

	gameOver.anim.PushBack({ 99,700,153,30 });
	gameOver.anim.loop = true;
	ready.anim.speed = 40;


	Blink.anim.loop = true;

	//equipped
	hook.anim.PushBack({ 71,255,17,17 });
	
	gun.anim.PushBack({ 92,255,17,17 });


	//Drops
	hookDrop.anim.PushBack({71,255,17,17}); 
	hookDrop.blink.PushBack({160,258,14,14 });
	
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
	inmuneDrop.anim.speed = 0.3f;

	//food
	banana.anim.PushBack({ 70,324,16,16 });
	banana.anim.PushBack({ 70,417,16,16 });

	cherry.anim.PushBack({ 8,324,16,16 });
	cherry.anim.PushBack({ 8,417,16,16 });
	
	banana.anim.speed = cherry.anim.speed = 0.3f;
	//scores
	score400.anim.PushBack({180,545,24,15});  

	score800.anim.PushBack({ 220,545,24,15 });

	score1600.anim.PushBack({ 251,545,40,15 });

	score400.lifetime = score800.lifetime = score1600.lifetime = 300;

	score400.anim.loop = score800.anim.loop = score1600.anim.loop = true;
	
	App->interfaceElements->AddElement(App->interfaceElements->UI, 0, 0, INTERFACE_ELEMENT_TYPE::UI);
	//App->interfaceElements->AddElement(App->interfaceElements->blackSection, 0, 240, INTERFACE_ELEMENT_TYPE::UI);

	App->interfaceElements->AddDrop(App->interfaceElements->hookDrop, 120, 40,DROP_TYPE::HOOK);
	//App->interfaceElements->AddElement(App->interfaceElements->hook, equippedPosition.x, equippedPosition.y, INTERFACE_ELEMENT_TYPE::EQUIPPED);
	App->interfaceElements->AddElement(App->interfaceElements->score400, 220,40, INTERFACE_ELEMENT_TYPE::UI);
	App->interfaceElements->AddElement(App->interfaceElements->score400, 200, 50, INTERFACE_ELEMENT_TYPE::UI);
	App->interfaceElements->AddElement(App->interfaceElements->score400, 240, 60, INTERFACE_ELEMENT_TYPE::UI);
	App->interfaceElements->AddElement(App->interfaceElements->score400, 250, 30, INTERFACE_ELEMENT_TYPE::UI);

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

void ModuleInterface::CleanEquipped()
{
	
}

void ModuleInterface::Equip(InterfaceElement element)
{
	//clean
	for (int i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; i++)
	{
		InterfaceElement* item = itemEquipped[i];

		if (item != nullptr && item != &element)
		{
			delete itemEquipped[i];
			itemEquipped[i] = nullptr;
		}
	}
	//addd new item
	for (int i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; i++)
	{
		InterfaceElement* item = itemEquipped[i];

		if (item ==nullptr)
		{
			item = new InterfaceElement(element);
			
			item->position.x = 60;
			item->position.y = 220;

			itemEquipped[i] = item;
		}
	}
	

}


update_status ModuleInterface::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_INTERFACE_ELEMENTS; ++i)
	{
		InterfaceElement* element = interfaceElements[i];

		if (element== nullptr)	continue;

		
			// Call particle Update. If it has reached its lifetime, destroy it
			if (element->Update() == false)
			{
				delete element;
				interfaceElements[i] = nullptr;
			}
		
	}
	for (uint i = 0; i < MAX_ACTIVE_DROPS; ++i)
	{
		Drop*drop= drops[i];

		if (drop == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (drop->Update() == false)
		{
			delete drop;
			drops[i] = nullptr;
		}
	}
	

	

	switch (App->player->lives)
	{
	case(4):
		App->interfaceElements->AddElement(App->interfaceElements->fourthLife, 10, 220,INTERFACE_ELEMENT_TYPE::UI);

		break;

	case(3):
		fourthLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->thirdLife, 10, 220, INTERFACE_ELEMENT_TYPE::UI);
		
		break;
	case(2):
		thirdLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->secondLife,10, 220, INTERFACE_ELEMENT_TYPE::UI);
		
		break;
	case(1):
		secondLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->oneLife, 10,220, INTERFACE_ELEMENT_TYPE::UI);
		
		break;
	case(0):
		
		
		break;
	}

	switch (App->player->isEquipped)
	{
	case(0):
		Equip(hook);
		//App->interfaceElements->AddElement(App->interfaceElements->hook, 10, 220, INTERFACE_ELEMENT_TYPE::EQUIPPED);
		break;

	case(1):
		Equip(score400);
		//App->interfaceElements->AddElement(App->interfaceElements->hook, equippedPosition.x+20, equippedPosition.y, INTERFACE_ELEMENT_TYPE::EQUIPPED);
		break;
	case(2):
		Equip(score800);
		//App->interfaceElements->AddElement(App->interfaceElements->gun, equippedPosition.x, equippedPosition.y, INTERFACE_ELEMENT_TYPE::EQUIPPED);
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

			if (drop->isPlaced == false)
			{
				drop->position.y++;
				drop->collider->SetPos(drop->position.x, drop->position.y);
			}

			

			
		}
		/*else if (drop != nullptr && drop->isAlive == false)
		{
			delete drop;
			drops[i] = nullptr;
		}*/


	}
	return update_status::UPDATE_CONTINUE;
}

void ModuleInterface::AddElement(const InterfaceElement& element, int x, int y,INTERFACE_ELEMENT_TYPE type)
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

			if (type == INTERFACE_ELEMENT_TYPE::EQUIPPED)
				e->equipped = true;

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
		App->interfaceElements->AddDrop(hookDrop, x, y, DROP_TYPE::HOOK);
		App->interfaceElements->AddDrop(inmuneDrop, x, y, DROP_TYPE::INMUNE);
		App->interfaceElements->AddDrop(gunDrop, x, y, DROP_TYPE::GUN);
	    break;
	case(4): //food
		App->interfaceElements->AddDrop(banana, x, y, DROP_TYPE::FOOD);
		App->interfaceElements->AddDrop(banana, x, y, DROP_TYPE::FOOD);
		break;
	
	}
	itemsCount++;
}


void ModuleInterface::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_DROPS; ++i)
	{
		drops[i]->isPlaced;
		if (drops[i] != nullptr && drops[i]->GetCollider() == c1 && c2->type == Collider::Type::PLAYER)
		{
			drops[i]->OnCollision(c1, c2);
		}

		if (drops[i] != nullptr && drops[i]->GetCollider() == c1 && c2->type == Collider::Type::FLOOR)
		{
			drops[i]->OnCollision(c1, c2);
		}

		//test collision
		if (drops[i] != nullptr && drops[i]->GetCollider() == c1 && c2->type == Collider::Type::ROPE)
		{
			drops[i]->OnCollision(c1, c2);
		}
	}

}