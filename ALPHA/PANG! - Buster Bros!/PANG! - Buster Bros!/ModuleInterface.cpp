#include "ModuleInterface.h"
#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Moduleplayer.h"
#include "InterfaceElement.h"
#include "Drop.h"


#include "SDL/include/SDL_timer.h"




ModuleInterface::ModuleInterface(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_INTERFACE_ELEMENTS; ++i)
		particles[i] = nullptr;

}

ModuleInterface::~ModuleInterface()
{

}

bool ModuleInterface::Start()
{



	LOG("Loading particles");
	texture = App->textures->Load("Assets/newInterface.png");

	
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
	hook.idle.PushBack({0,0,0,0}); 
	hook.blink.PushBack({ 0,0,0,0 });
	hook.idle.loop = hook.blink.loop = true;
	hook.blink.speed = 2;



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
	App->interfaceElements->AddElement(App->interfaceElements->UI, 0, 0);

	

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

			//Adding the particle's collider
			/*if (colliderType != Collider::Type::NONE)
				e->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);*/

			interfaceElements[i] = e;
			break;
		}
	}
}