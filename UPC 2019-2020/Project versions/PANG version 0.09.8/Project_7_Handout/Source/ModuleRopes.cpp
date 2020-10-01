#include "ModuleRopes.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleRopes::ModuleRopes()
{
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
		ropes[i] = nullptr;
}

ModuleRopes::~ModuleRopes()
{

}

bool ModuleRopes::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/rope.png");

	// Explosion particle
	

	//X: the first is 20 px width, then each sprite is 17 px width
	//Y: the first is 33 px height, then each sprite increases the size by 2px

	//rope.anim.PushBack({118,0,14,200});

	rope.anim.PushBack({ 0,0,20,400 });
	rope.anim.PushBack({ 20,0,14,400 });
	rope.anim.PushBack({ 37,0,14,400 });
	rope.anim.PushBack({ 54,0,15,400 });
	rope.anim.PushBack({ 71,0,14,400 });
	rope.anim.PushBack({ 88,0,14,400 });
	rope.anim.PushBack({ 105,0,14,400 });
	rope.anim.PushBack({ 122,0,14,400 });
	rope.anim.PushBack({ 139,0,14,400 });
	rope.anim.PushBack({ 156,0,14,400 });
	rope.anim.PushBack({ 173,0,14,400 });
	rope.anim.PushBack({ 190,0,14,400 });
	rope.anim.PushBack({ 207,0,14,400 });
	rope.anim.PushBack({ 224,0,14,400 });
	rope.anim.PushBack({ 241,0,14,400 });
	rope.anim.PushBack({ 258,0,14,400 });
	rope.anim.PushBack({ 275,0,14,400 });
	rope.anim.PushBack({ 292,0,14,400 });
	rope.anim.PushBack({ 309,0,14,400 });
	rope.anim.PushBack({ 326,0,14,400 });
	rope.anim.PushBack({ 343,0,14,400 });
	rope.anim.PushBack({ 360,0,14,400 });
	rope.anim.PushBack({ 377,0,14,400 });
	rope.anim.PushBack({ 394,0,14,400 });
	rope.anim.PushBack({ 411,0,14,400 });
	rope.anim.PushBack({ 428,0,14,400 });
	rope.anim.PushBack({ 445,0,14,400 });
	rope.anim.PushBack({ 462,0,14,400 });
	rope.anim.PushBack({ 479,0,14,400 });
	rope.anim.PushBack({ 496,0,14,400 });

	rope.anim.loop = false;
	rope.speed.y = 0;
	rope.lifetime = 1000;
	rope.isAlive = true;
	rope.anim.speed = 0.4f;

	return true;
}

bool ModuleRopes::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		if (ropes[i] != nullptr)
		{
			delete ropes[i];
			ropes[i] = nullptr;
		}
	}

	return true;
}

void ModuleRopes::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		// Always destroy particles that collide
		if (ropes[i] != nullptr && ropes[i]->collider == c1)
		{
			delete ropes[i];
			ropes[i] = nullptr;
			break;
		}
	}
}

update_status ModuleRopes::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		Rope* rope = ropes[i];

		if (rope == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (rope->Update() == false)
		{
			delete rope;
			ropes[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRopes::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		Rope*rope = ropes[i];

		if (rope != nullptr && rope->isAlive)
		{
			App->render->Blit(texture,rope->position.x, rope->position.y, &(rope->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleRopes::AddRope(const Rope& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		//Finding an empty slot for a new particle
		if (ropes[i] == nullptr)
		{
			Rope* p = new Rope(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			ropes[i] = p;
			break;
		}
	}
}