#include "ModuleRopes.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleRopes::ModuleRopes(bool startEnabled) : Module(startEnabled)
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
	texture = App->textures->Load("Assets/newRope.png");
	FiringFx = App->audio->LoadFx("Assets/[FX]- firing sound.wav");

	// Explosion particle
	//old rope
	//0-10
	//rope.anim.PushBack({ 3,0,16,400 });
	//rope.anim.PushBack({ 20,0,14,400 });
	//rope.anim.PushBack({ 37,0,14,400 });
	//rope.anim.PushBack({ 54,0,15,400 });
	//rope.anim.PushBack({ 71,0,14,400 });

	//rope.anim.PushBack({ 88,0,14,400 });
	//rope.anim.PushBack({ 105,0,14,400 });
	//rope.anim.PushBack({ 122,0,14,400 });
	//rope.anim.PushBack({ 137,0,14,400 });
	//rope.anim.PushBack({ 154,0,14,400 });


	////10-20
	//rope.anim.PushBack({ 170,0,14,400 });
	//rope.anim.PushBack({ 187,0,14,400 });
	//rope.anim.PushBack({ 204,0,14,400 });
	//rope.anim.PushBack({ 221,0,14,400 });
	//rope.anim.PushBack({ 238,0,14,400 });

	//rope.anim.PushBack({ 255,0,14,400 });
	//rope.anim.PushBack({ 272,0,14,400 });
	//rope.anim.PushBack({ 288,0,14,400 });
	//rope.anim.PushBack({ 305,0,14,400 });
	//rope.anim.PushBack({ 322,0,14,400 });


	////20-30
	//rope.anim.PushBack({ 338,0,14,400 });
	//rope.anim.PushBack({ 355,0,14,400 });
	//rope.anim.PushBack({ 372,0,14,400 });
	//rope.anim.PushBack({ 386,0,14,400 });
	//rope.anim.PushBack({ 403,0,14,400 });

	//rope.anim.PushBack({ 420,0,14,400 });
	//rope.anim.PushBack({ 437,0,14,400 });
	//rope.anim.PushBack({ 454,0,14,400 });
	//rope.anim.PushBack({ 471,0,14,400 });
	//rope.anim.PushBack({ 487,0,14,400 });


	////30-40
	//rope.anim.PushBack({ 503,0,14,400 });
	//rope.anim.PushBack({ 520,0,14,400 });
	//rope.anim.PushBack({ 537,0,14,400 });
	//rope.anim.PushBack({ 554,0,14,400 });
	//rope.anim.PushBack({ 571,0,14,400 });

	//rope.anim.PushBack({ 588,0,14,400 });
	//rope.anim.PushBack({ 603,0,14,400 });
	//rope.anim.PushBack({ 620,0,14,400 });
	//rope.anim.PushBack({ 637,0,14,400 });
	//rope.anim.PushBack({ 654,0,14,400 });


	////40-50
	//rope.anim.PushBack({ 670,0,14,400 });
	//rope.anim.PushBack({ 687,0,14,400 });
	//rope.anim.PushBack({ 703,0,14,400 });
	//rope.anim.PushBack({ 720,0,14,400 });
	//rope.anim.PushBack({ 737,0,14,400 });

	//rope.anim.PushBack({ 754,0,14,400 });
	//rope.anim.PushBack({ 768,0,14,400 });
	//rope.anim.PushBack({ 785,0,14,400 });
	//rope.anim.PushBack({ 802,0,14,400 });
	//rope.anim.PushBack({ 819,0,14,400 });


	////50-60
	//rope.anim.PushBack({ 837,0,14,400 });
	//rope.anim.PushBack({ 854,0,14,400 });
	//rope.anim.PushBack({ 871,0,14,400 });
	//rope.anim.PushBack({ 888,0,14,400 });
	//rope.anim.PushBack({ 905,0,14,400 });

	//rope.anim.PushBack({ 922,0,14,400 });
	//rope.anim.PushBack({ 939,0,14,400 });
	//rope.anim.PushBack({ 972,0,14,400 });
	//rope.anim.PushBack({ 989,0,14,400 });
	//rope.anim.PushBack({ 1006,0,14,400 });


	////60-70
	//rope.anim.PushBack({ 1039,0,14,400 });
	//rope.anim.PushBack({ 1056,0,14,400 });
	//rope.anim.PushBack({ 1072,0,14,400 });
	//rope.anim.PushBack({ 1089,0,14,400 });
	//rope.anim.PushBack({ 1106,0,14,400 });

	//rope.anim.PushBack({ 1123,0,14,400 });
	//rope.anim.PushBack({ 1140,0,14,400 });
	//rope.anim.PushBack({ 1157,0,14,400 });
	//rope.anim.PushBack({ 1172,0,9,400 });
	//rope.anim.PushBack({ 1181,0,9,400 });
	//rope.anim.PushBack({ 0,0,0,0 });

	//// rope.anim.PushBack({ 1195,0,14,400 }); 


	//	//rope.anim.PushBack({ 1212,0,14,400 });
	//	//rope.anim.PushBack({ 1229,0,14,400 });

//new rope


rope.anim.PushBack({ 0, 175, 9, 34 });
rope.anim.PushBack({ 9, 173, 9, 36 });
rope.anim.PushBack({ 18, 171, 9, 38 });
rope.anim.PushBack({ 27, 169, 9, 40 });
rope.anim.PushBack({ 36, 167, 9, 42 });

rope.anim.PushBack({ 45, 165, 9, 44 });
rope.anim.PushBack({ 54, 163, 9, 46 });
rope.anim.PushBack({ 63, 161, 9, 48 });
rope.anim.PushBack({ 72, 159, 9, 50 });
rope.anim.PushBack({ 81, 157, 9, 52 });

//

rope.anim.PushBack({ 90, 155, 9, 54 });
rope.anim.PushBack({ 99, 153, 9, 56 });
rope.anim.PushBack({ 108, 151, 9, 58 });
rope.anim.PushBack({ 117, 149, 9, 60 });
rope.anim.PushBack({ 126, 147, 9, 62 });

rope.anim.PushBack({ 135, 145, 9, 64 });
rope.anim.PushBack({ 144, 143, 9, 66 });
rope.anim.PushBack({ 153, 141, 9, 68 });
rope.anim.PushBack({ 162, 139, 9, 70 });
rope.anim.PushBack({ 171, 137, 9, 72 });

//

rope.anim.PushBack({ 180, 135, 9, 74 });
rope.anim.PushBack({ 189, 133, 9, 76 });
rope.anim.PushBack({ 198, 131, 9, 78 });
rope.anim.PushBack({ 207, 129, 9, 80 });
rope.anim.PushBack({ 216, 127, 9, 82 });

rope.anim.PushBack({ 225, 125, 9, 84 });
rope.anim.PushBack({ 234, 123, 9, 86 });
rope.anim.PushBack({ 243, 121, 9, 88 });
rope.anim.PushBack({ 252, 119, 9, 90 });
rope.anim.PushBack({ 261, 117, 9, 92 });

//

rope.anim.PushBack({ 270, 115, 9, 94 });
rope.anim.PushBack({ 279, 113, 9, 96 });
rope.anim.PushBack({ 288, 111, 9, 98 });
rope.anim.PushBack({ 297, 109, 9, 100 });
rope.anim.PushBack({ 306, 107, 9, 102 });

rope.anim.PushBack({ 315, 105, 9, 104 });
rope.anim.PushBack({ 324, 103, 9, 106 });
rope.anim.PushBack({ 333, 101, 9, 108 });
rope.anim.PushBack({ 342, 99, 9, 110 });
rope.anim.PushBack({ 351, 97, 9, 112 });

//

rope.anim.PushBack({ 360, 95, 9, 114 });
rope.anim.PushBack({ 369, 93, 9, 116 });
rope.anim.PushBack({ 378, 91, 9, 118 });
rope.anim.PushBack({ 387, 89, 9, 120 });
rope.anim.PushBack({ 396, 87, 9, 122 });

rope.anim.PushBack({ 405, 85, 9, 124 });
rope.anim.PushBack({ 414, 83, 9, 126 });
rope.anim.PushBack({ 423, 81, 9, 128 });
rope.anim.PushBack({ 432, 79, 9, 130 });
rope.anim.PushBack({ 441, 77, 9, 132 });

//

rope.anim.PushBack({ 450, 75, 9, 134 });
rope.anim.PushBack({ 459, 73, 9, 136 });
rope.anim.PushBack({ 468, 71, 9, 138 });
rope.anim.PushBack({ 477, 69, 9, 140 });
rope.anim.PushBack({ 486, 67, 9, 142 });

rope.anim.PushBack({ 495, 65, 9, 144 });
rope.anim.PushBack({ 504, 63, 9, 146 });
rope.anim.PushBack({ 513, 61, 9, 148 });
rope.anim.PushBack({ 522, 59, 9, 150 });
rope.anim.PushBack({ 531, 57, 9, 152 });

//

rope.anim.PushBack({ 540, 55, 9, 154 });
rope.anim.PushBack({ 549, 53, 9, 156 });
rope.anim.PushBack({ 558, 51, 9, 158 });
rope.anim.PushBack({ 567, 49, 9, 160 });
rope.anim.PushBack({ 576, 47, 9, 162 });

rope.anim.PushBack({ 585, 45, 9, 164 });
rope.anim.PushBack({ 594, 43, 9, 166 });
rope.anim.PushBack({ 603, 41, 9, 168 });
rope.anim.PushBack({ 612, 39, 9, 170 });
rope.anim.PushBack({ 621, 37, 9, 172 });

//

rope.anim.PushBack({ 630, 35, 9, 174 });
rope.anim.PushBack({ 639, 33, 9, 176 });
rope.anim.PushBack({ 648, 31, 9, 178 });
rope.anim.PushBack({ 657, 29, 9, 180 });
rope.anim.PushBack({ 666, 27, 9, 182 });

rope.anim.PushBack({ 675, 25, 9, 184 });
rope.anim.PushBack({ 684, 23, 9, 186 });
rope.anim.PushBack({ 693, 21, 9, 188 });
rope.anim.PushBack({ 702, 19, 9, 190 });
rope.anim.PushBack({ 711, 17, 9, 192 });

//

rope.anim.PushBack({ 720, 15, 9, 194 });
rope.anim.PushBack({ 729, 13, 9, 196 });
rope.anim.PushBack({ 738, 11, 9, 198 });
rope.anim.PushBack({ 747, 9, 9, 200 });
rope.anim.PushBack({ 756, 7, 9, 202 });

rope.anim.PushBack({ 765, 5, 9, 204 });
rope.anim.PushBack({ 774, 3, 9, 206 });
rope.anim.PushBack({ 783, 354, 9, 208 });
rope.anim.PushBack({ 792, 352, 9, 210 });
rope.anim.PushBack({ 801, 350, 9, 212 });

		
	rope.anim.pingpong = false;
	rope.anim.loop = false;
	rope.speed.y = -2.85f;
	rope.lifetime = 100;
	rope.isAlive = true;
	rope.anim.speed = 1.0f;

	//Rope Collider

	return true;
}

update_status ModuleRopes::PreUpdate()
{

	LOG("Unloading particles");

	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		if (ropes[i] != nullptr && ropes[i]->pendingToDelete)
		{
			delete ropes[i];
			ropes[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
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
			if (c2->type == Collider::Type::TOP)
			{
				delete ropes[i];
				ropes[i] = nullptr;
				break;
			}
			if (c2->type == Collider::Type::BALL)
			{
				delete ropes[i];
				ropes[i] = nullptr;
				break;
			}
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
			//rope->collider = nullptr;

			//rope->collider = App->collisions->AddCollider(rope->anim.GetCurrentFrame(), Collider::Type::ROPE, this);
			
			
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleRopes::AddRope(const Rope& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Rope* newrope = nullptr;
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		//Finding an empty slot for a new particle
		if (ropes[i] == nullptr)
		{
			App->audio->PlayFx(FiringFx);             // Sound


			Rope* newrope = new Rope(particle);
			newrope->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newrope->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newrope->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE) {
				SDL_Rect ropeCollider = {0,0,9,300};
				
				//newrope->collider = App->collisions->AddCollider(newrope->anim.GetCurrentFrame(), Collider::Type::ROPE, this);
				newrope->collider = App->collisions->AddCollider(ropeCollider, Collider::Type::ROPE, this);


			
			}
				

			ropes[i] = newrope;
			break;
		}
	}
	/*return newrope;*/
}