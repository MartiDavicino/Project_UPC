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
	
	//0-10
	rope.anim.PushBack({ 3,0,16,400 });
	rope.anim.PushBack({ 20,0,14,400 });
	rope.anim.PushBack({ 37,0,14,400 });
	rope.anim.PushBack({ 54,0,15,400 });
	rope.anim.PushBack({ 71,0,14,400 });

	rope.anim.PushBack({ 88,0,14,400 });
	rope.anim.PushBack({ 105,0,14,400 });
	rope.anim.PushBack({ 122,0,14,400 });
	rope.anim.PushBack({ 137,0,14,400 });
	rope.anim.PushBack({ 154,0,14,400 });


	//10-20
	rope.anim.PushBack({ 170,0,14,400 });
	rope.anim.PushBack({ 187,0,14,400 });
	rope.anim.PushBack({ 204,0,14,400 });
	rope.anim.PushBack({ 221,0,14,400 });
	rope.anim.PushBack({ 238,0,14,400 });

	rope.anim.PushBack({ 255,0,14,400 });
	rope.anim.PushBack({ 272,0,14,400 });
	rope.anim.PushBack({ 288,0,14,400 });
	rope.anim.PushBack({ 305,0,14,400 });
	rope.anim.PushBack({ 322,0,14,400 });


	//20-30
	rope.anim.PushBack({ 338,0,14,400 });
	rope.anim.PushBack({ 355,0,14,400 });
	rope.anim.PushBack({ 372,0,14,400 });
	rope.anim.PushBack({ 386,0,14,400 });
	rope.anim.PushBack({ 403,0,14,400 });

	rope.anim.PushBack({ 420,0,14,400 });
	rope.anim.PushBack({ 437,0,14,400 });
	rope.anim.PushBack({ 454,0,14,400 });
	rope.anim.PushBack({ 471,0,14,400 });
	rope.anim.PushBack({ 487,0,14,400 });


	//30-40
	rope.anim.PushBack({ 503,0,14,400 });
	rope.anim.PushBack({ 520,0,14,400 });
	rope.anim.PushBack({ 537,0,14,400 });
	rope.anim.PushBack({ 554,0,14,400 });
	rope.anim.PushBack({ 571,0,14,400 });

	rope.anim.PushBack({ 588,0,14,400 });
	rope.anim.PushBack({ 603,0,14,400 });
	rope.anim.PushBack({ 620,0,14,400 });
	rope.anim.PushBack({ 637,0,14,400 });
	rope.anim.PushBack({ 654,0,14,400 });


	//40-50
	rope.anim.PushBack({ 670,0,14,400 });
	rope.anim.PushBack({ 687,0,14,400 });
	rope.anim.PushBack({ 703,0,14,400 });
	rope.anim.PushBack({ 720,0,14,400 });
	rope.anim.PushBack({ 737,0,14,400 });

	rope.anim.PushBack({ 754,0,14,400 });
	rope.anim.PushBack({ 768,0,14,400 });
	rope.anim.PushBack({ 785,0,14,400 });
	rope.anim.PushBack({ 802,0,14,400 });
	rope.anim.PushBack({ 819,0,14,400 });


	//50-60
	rope.anim.PushBack({ 837,0,14,400 });
	rope.anim.PushBack({ 854,0,14,400 });
	rope.anim.PushBack({ 871,0,14,400 });
	rope.anim.PushBack({ 888,0,14,400 });
	rope.anim.PushBack({ 905,0,14,400 });

	rope.anim.PushBack({ 922,0,14,400 });
	rope.anim.PushBack({ 939,0,14,400 });
	rope.anim.PushBack({ 972,0,14,400 });
	rope.anim.PushBack({ 989,0,14,400 });
	rope.anim.PushBack({ 1006,0,14,400 });


	//60-70
	rope.anim.PushBack({ 1037,0,14,400 });
	rope.anim.PushBack({ 1054,0,14,400 });
	rope.anim.PushBack({ 1070,0,14,400 });
	rope.anim.PushBack({ 1087,0,14,400 });
	rope.anim.PushBack({ 1104,0,14,400 });

	rope.anim.PushBack({ 1121,0,14,400 });
	rope.anim.PushBack({ 1138,0,14,400 });
	rope.anim.PushBack({ 1155,0,14,400 });
	rope.anim.PushBack({ 1182,0,14,400 });

	// rope.anim.PushBack({ 1195,0,14,400 }); 


		//rope.anim.PushBack({ 1212,0,14,400 });
		//rope.anim.PushBack({ 1229,0,14,400 });

		
	rope.anim.pingpong = false;
	rope.anim.loop = false;
	rope.speed.y = 0;
	rope.lifetime = 1000;
	rope.isAlive = true;
	rope.anim.speed = 0.02f;

	//Rope Collider

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