#include "ModuleInterface.h"
#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Moduleplayer.h"
#include "InterfaceElement.h"
#include "Drop.h"
#include "ModuleScene.h"
#include "ModuleWin.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBalls.h"

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
	ready.anim.speed = 0.1f;
	ready.lifetime = 200;

	gameOver.anim.PushBack({ 137,700,153,30 });
	gameOver.anim.PushBack({ 137,700,153,30 });
	gameOver.anim.PushBack({ 0,0,0,0});
	gameOver.anim.loop = true;
	gameOver.anim.speed = 0.1f;


	Blink.anim.loop = true;

	//equipped
	hook.anim.PushBack({ 72,257,15,16 });
	hook.anim.PushBack({ 87,257,15,16 });
	
	doubbleShot.anim.PushBack({ 111,257,13,16 });
	doubbleShot.anim.PushBack({ 124,257,13,16 });

	gun.anim.PushBack({ 150,257,17,16 });
	gun.anim.PushBack({ 167,257,17,16 });

	hook.anim.loop = doubbleShot.anim.loop = gun.anim.loop = true;
	hook.anim.speed= doubbleShot.anim.speed = gun.anim.speed = 0.1f;

	hook.lifetime = gun.lifetime = doubbleShot.lifetime = dropTime;

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
	
	banana.anim.speed = cherry.anim.speed = 0.1f;
	//scores
	score400.anim.PushBack({180,545,24,15});  

	score800.anim.PushBack({ 220,545,24,15 });

	score1600.anim.PushBack({ 251,545,40,15 });

	score400.lifetime = score800.lifetime = score1600.lifetime = scoreTime;

	score400.anim.loop = score800.anim.loop = score1600.anim.loop = true;
	score400.name = score800.name = score1600.name = DROP_TYPE::SCORE;
	
	App->interfaceElements->AddElement(App->interfaceElements->UI, 0, 0, INTERFACE_ELEMENT_TYPE::UI,0);
	//App->interfaceElements->AddElement(App->interfaceElements->blackSection, 0, 240, INTERFACE_ELEMENT_TYPE::UI);

	App->interfaceElements->AddElement(App->interfaceElements->ready,150, 100, INTERFACE_ELEMENT_TYPE::UI,70);
	//App->interfaceElements->AddElement(App->interfaceElements->gameOver, 130, 100, INTERFACE_ELEMENT_TYPE::UI,120);
	

	//App->interfaceElements->AddElement(App->interfaceElements->hook, equippedPosition.x,equippedPosition.y, INTERFACE_ELEMENT_TYPE::EQUIPPED, 70);
	App->interfaceElements->AddDrop(App->interfaceElements->banana, 120, 40,DROP_TYPE::FOOD);
	//App->interfaceElements->AddElement(App->interfaceElements->hook, equippedPosition.x, equippedPosition.y, INTERFACE_ELEMENT_TYPE::EQUIPPED);

	

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

	for (uint i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; ++i)
	{
		if (itemEquipped[i] != nullptr)
		{
			delete itemEquipped[i];
			itemEquipped[i] = nullptr;
		}
	}
	for (uint i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; ++i)
	{
		if (lives[i] != nullptr)
		{
			delete lives[i];
			lives[i] = nullptr;
		}
	}
	

	return true;
}






update_status ModuleInterface::Update()
{
	//doesnt work
	equippedTime++; LOG("equippedTime : %d", equippedTime);
	if (equippedTime >= 120) //when the counntdown has reached it lifetime unequip item
	{
		//Equip(none); 
		equippedItem = DROP_TYPE::NONE;
		equippedTime = 0;
	}

	if (countDownReached == false)
	{

		frameCount++;
		if (frameCount % 60 == 0)
		{
			countDown--;
			LOG("%d  seconds left  ", countDown);
			LOG("score : %d", App->score);
			
		}
		if (countDown == 0) countDownReached = true;
		if (countDownReached == true)
		{
			//game over
			LOG(" G A M E  O V E R");
			App->interfaceElements->AddElement(App->interfaceElements->gameOver, 130, 100, INTERFACE_ELEMENT_TYPE::UI,70);
			App->interfaceElements->AddElement(App->interfaceElements->ready, 130, 100, INTERFACE_ELEMENT_TYPE::UI, 70);
			//countDownReached = false;
		}
		if (App->balls->ballsLeft <= 0)
		{
			//reset values
			App->score = 0;
			App->balls->ballsLeft = 16;
			//transition to level
			App->fade->FadeToBlack((Module*)App->scene, (Module*)App->transition, 60);

			if (App->scene->levelSelection == 6)
			{
				App->fade->FadeToBlack((Module*)App->scene, (Module*)App->win, 60);
				App->scene->Disable();
			}
		}
	}


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
	

	

	

	switch (App->player->itemEquipped)
	{
		//the problem i¡is that is rendenring on update so the animation never finishes
	case(ITEM_EQUIPPED::NONE):
		if (equippedItem != DROP_TYPE::NONE)
		{
			LOG("Unequipped");
			Equip(none);
			equippedItem = DROP_TYPE::NONE;
		}
		break;

	case(ITEM_EQUIPPED::HOOK):
		if (equippedItem != DROP_TYPE::HOOK)
		{
			LOG("Hook equipped"); //equippedTime = 0;
			Equip(hook);
			equippedItem = DROP_TYPE::HOOK;
		}
		break;
	case(ITEM_EQUIPPED::GUN):
		if (equippedItem != DROP_TYPE::GUN)
		{
			LOG("Gun equipped"); //equippedTime = 0;
			Equip(gun);
			equippedItem = DROP_TYPE::GUN;
		}
		break;

	}


	

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleInterface::PostUpdate()
{
	switch (App->player->lives)
	{
	case(4):
		//App->interfaceElements->AddElement(App->interfaceElements->fourthLife, 10, 220, INTERFACE_ELEMENT_TYPE::UI, 0);
		ChangeLife(App->interfaceElements->fourthLife);
		break;

	case(3):
		/*fourthLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->thirdLife, 10, 220, INTERFACE_ELEMENT_TYPE::UI, 0);*/
		ChangeLife(App->interfaceElements->thirdLife);
		break;
	case(2):
	/*	thirdLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->secondLife, 10, 220, INTERFACE_ELEMENT_TYPE::UI, 0);*/
		ChangeLife(App->interfaceElements->secondLife);
		break;
	case(1):
		/*secondLife.display = false;
		App->interfaceElements->AddElement(App->interfaceElements->oneLife, 10, 220, INTERFACE_ELEMENT_TYPE::UI, 0);*/
		ChangeLife(App->interfaceElements->oneLife);
		break;
	case(0):

		ChangeLife(App->interfaceElements->none);
		break;
	}

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
				if (drop->name != DROP_TYPE::SCORE);
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

	for (uint i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; ++i)
	{
		InterfaceElement* item = itemEquipped[i];

		if (item != nullptr) // && item->display
		{
			//App->render->Blit(texture, element->position.x, element->position.y, 0);
			//&(element->anim.GetCurrentFrame())
			App->render->Blit(texture, item->position.x, item->position.y, &(item->anim.GetCurrentFrame()));


		}
		else if (item != nullptr && item->display == false)
		{
			delete item;
			itemEquipped[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; ++i)
	{
		InterfaceElement* life = lives[i];

		if (life != nullptr) // && item->display
		{
			//App->render->Blit(texture, element->position.x, element->position.y, 0);
			//&(element->anim.GetCurrentFrame())
			App->render->Blit(texture, life->position.x, life->position.y, &(life->anim.GetCurrentFrame()));


		}
		else if (life != nullptr && life->display == false)
		{
			delete life;
			lives[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleInterface::AddElement(const InterfaceElement& element, int x, int y,INTERFACE_ELEMENT_TYPE newType,uint newLifetime)
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

			e->lifetime = newLifetime;
			
			e->type = newType;

			interfaceElements[i] = e;
			break;
		}
	}
}

void ModuleInterface::ChangeLife(InterfaceElement& element)
{
	for (uint i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; ++i)
	{
		InterfaceElement* life = lives[i];
		if (life != nullptr)
		{
			delete life;
			lives[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; ++i)
	{
		//Finding an empty slot for a new element
		if (lives[i] == nullptr)
		{
			InterfaceElement* life = new InterfaceElement(element);

			//p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			life->position.x = 10;				// so when frameCount reaches 0 the particle will be activated
			life->position.y = 220;

			life->lifetime = equippedTime;

			life->type = INTERFACE_ELEMENT_TYPE::EQUIPPED;

			lives[i] = life;
			break;
		}
	}


}

void ModuleInterface::Equip(InterfaceElement& element)
{
	for (uint i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; ++i)
	{
		InterfaceElement* equipped = itemEquipped[i];
		if (equipped != nullptr)
		{
			delete equipped;
			itemEquipped[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ACTIVE_ITEMS_EQUIPPED; ++i)
	{
		//Finding an empty slot for a new element
		if (itemEquipped[i] == nullptr)
		{
			InterfaceElement* equipped = new InterfaceElement(element);

			//p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			equipped->position.x = equippedPosition.x;				// so when frameCount reaches 0 the particle will be activated
			equipped->position.y = equippedPosition.y;

			equipped->lifetime = equippedTime;

			equipped->type = INTERFACE_ELEMENT_TYPE::EQUIPPED;

			itemEquipped[i] = equipped;
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

		if (drops[i] != nullptr && (drops[i]->GetCollider() == c1 || drops[i]->collider == c2))
		{
			drops[i]->isPlaced;
			drops[i]->OnCollision(c1, c2);
		}

	}

}