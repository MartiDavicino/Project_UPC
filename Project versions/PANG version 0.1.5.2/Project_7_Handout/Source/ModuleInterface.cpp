#include "ModuleInterface.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Moduleplayer.h"
#include "InterfaceElement.h"

#include "SDL/include/SDL_timer.h"




ModuleInterface::ModuleInterface(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;

}

ModuleInterface::~ModuleInterface()
{

}

bool ModuleInterface::Start()
{



	LOG("Loading particles");
	texture = App->textures->Load("Assets/Interface.png");

	//position

	zeroLife.position.y = oneLife.position.y = secondLife.position.y = thirdLife.position.y = 200;
	zeroLife.position.x = oneLife.position.x = secondLife.position.x = thirdLife.position.x = 30;


	zeroLife.Display({ 0,0,0,0 });
	oneLife.Display({ 0,213,16,16 });
	secondLife.Display({ 0,213,35,16 });
	thirdLife.Display({ 0,213,70,16 });

	zeroLife.anim.loop = oneLife.anim.loop = secondLife.anim.loop = thirdLife.anim.loop = true;
	//zeroLife.anim.loop = oneLife.anim.loop = secondLife.anim.loop = thirdLife.anim.loop = true;


	Blink.Display({ 0,0,210,300 });
	Blink.anim.loop = true;






	return true;
}

bool ModuleInterface::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
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

	switch (App->player->lives)
	{
	case(3):
		App->interfaceElements->AddElement(App->interfaceElements->thirdLife, 0, 212);
		currentAnim = &thirdLife;
		break;
	case(2):
		currentAnim = &secondLife;
		break;
	case(1):
		currentAnim = &secondLife;
		break;
	case(0):
		currentAnim = &zeroLife;
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
			App->render->Blit(texture, element->position.x, element->position.y, 0);
			//&(element->anim.GetCurrentFrame())
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleInterface::AddElement(const InterfaceElement& element, int x, int y)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
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