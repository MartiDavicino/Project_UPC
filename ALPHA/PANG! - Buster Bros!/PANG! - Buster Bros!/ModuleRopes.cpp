#include "ModuleRopes.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "Application.h"
#include "ModulePlayer.h"

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
	texture = App->textures->Load("Assets/particles.png");
	FiringFx = App->audio->LoadFx("Assets/[FX]- firing sound.wav");
	HookedFX = App->audio->LoadFx("Assets/wire hooked.wav");

	

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

	shot.anim.PushBack({ 317,367,6,12 });
	shot.anim.PushBack({ 330,367,10,12 });
	shot.anim.PushBack({ 348,367,14,12 });
	//loop
	shot.anim.PushBack({ 360,367,20,12 });
	shot.anim.PushBack({ 386,367,20,12 });
	//loop
	shot.anim.PushBack({ 360,367,20,12 });
	shot.anim.PushBack({ 386,367,20,12 });
	//loop
	shot.anim.PushBack({ 360,367,20,12 });
	shot.anim.PushBack({ 386,367,20,12 });
	//loop
	shot.anim.PushBack({ 360,367,20,12 });
	//loop
	shot.anim.PushBack({ 360,367,20,12 });
	//loop
	shot.anim.PushBack({ 360,367,20,12 });
	shot.anim.PushBack({ 386,367,20,12 });
	//loop
	shot.anim.PushBack({ 360,367,20,12 });
	shot.anim.PushBack({ 386,367,20,12 });
	shot.anim.PushBack({ 386,367,20,12 });
	shot.anim.PushBack({ 386,367,20,12 });
	shot.anim.loop = true;
	shot.speed.y = -2.85f;

	//hook

	hook.anim.PushBack({ 800, 175, 9, 34 });
	hook.anim.PushBack({ 809, 173, 9, 36 });
	hook.anim.PushBack({ 818, 171, 9, 38 });
	hook.anim.PushBack({ 827, 169, 9, 40 });
	hook.anim.PushBack({ 836, 167, 9, 42 });

	hook.anim.PushBack({ 845, 165, 9, 44 });
	hook.anim.PushBack({ 854, 163, 9, 46 });
	hook.anim.PushBack({ 863, 161, 9, 48 });
	hook.anim.PushBack({ 872, 159, 9, 50 });
	hook.anim.PushBack({ 881, 157, 9, 52 });

	//

	hook.anim.PushBack({ 890, 155, 9, 54 });
	hook.anim.PushBack({ 899, 153, 9, 56 });
	hook.anim.PushBack({ 908, 151, 9, 58 });
	hook.anim.PushBack({ 917, 149, 9, 60 });
	hook.anim.PushBack({ 926, 147, 9, 62 });

	hook.anim.PushBack({ 935, 145, 9, 64 });
	hook.anim.PushBack({ 944, 143, 9, 66 });
	hook.anim.PushBack({ 953, 141, 9, 68 });
	hook.anim.PushBack({ 962, 139, 9, 70 });
	hook.anim.PushBack({ 971, 137, 9, 72 });

	//

	hook.anim.PushBack({ 980, 135, 9, 74 });
	hook.anim.PushBack({ 989, 133, 9, 76 });
	hook.anim.PushBack({ 998, 131, 9, 78 });
	hook.anim.PushBack({ 1007, 129, 9, 80 });
	hook.anim.PushBack({ 1016, 127, 9, 82 });

	hook.anim.PushBack({ 1025, 125, 9, 84 });
	hook.anim.PushBack({ 1034, 123, 9, 86 });
	hook.anim.PushBack({ 1043, 121, 9, 88 });
	hook.anim.PushBack({ 1052, 119, 9, 90 });
	hook.anim.PushBack({ 1061, 117, 9, 92 });

	//

	hook.anim.PushBack({ 1070, 115, 9, 94 });
	hook.anim.PushBack({ 1079, 113, 9, 96 });
	hook.anim.PushBack({ 1088, 111, 9, 98 });
	hook.anim.PushBack({ 1097, 109, 9, 100 });
	hook.anim.PushBack({ 1106, 107, 9, 102 });

	hook.anim.PushBack({ 1115, 105, 9, 104 });
	hook.anim.PushBack({ 1124, 103, 9, 106 });
	hook.anim.PushBack({ 1133, 101, 9, 108 });
	hook.anim.PushBack({ 1142, 99, 9, 110 });
	hook.anim.PushBack({ 1151, 97, 9, 112 });

	//

	hook.anim.PushBack({ 1160, 95, 9, 114 });
	hook.anim.PushBack({ 1169, 93, 9, 116 });
	hook.anim.PushBack({ 1178, 91, 9, 118 });
	hook.anim.PushBack({ 1187, 89, 9, 120 });
	hook.anim.PushBack({ 1196, 87, 9, 122 });

	hook.anim.PushBack({ 1205, 85, 9, 124 });
	hook.anim.PushBack({ 1214, 83, 9, 126 });
	hook.anim.PushBack({ 1223, 81, 9, 128 });
	hook.anim.PushBack({ 1232, 79, 9, 130 });
	hook.anim.PushBack({ 1241, 77, 9, 132 });

	//

	hook.anim.PushBack({ 1250, 75, 9, 134 });
	hook.anim.PushBack({ 1259, 73, 9, 136 });
	hook.anim.PushBack({ 1268, 71, 9, 138 });
	hook.anim.PushBack({ 1277, 69, 9, 140 });
	hook.anim.PushBack({ 1286, 67, 9, 142 });

	hook.anim.PushBack({ 1295, 65, 9, 144 });
	hook.anim.PushBack({ 1304, 63, 9, 146 });
	hook.anim.PushBack({ 1313, 61, 9, 148 });
	hook.anim.PushBack({ 1322, 59, 9, 150 });
	hook.anim.PushBack({ 1331, 57, 9, 152 });

	//

	hook.anim.PushBack({ 1340, 55, 9, 154 });
	hook.anim.PushBack({ 1349, 53, 9, 156 });
	hook.anim.PushBack({ 1358, 51, 9, 158 });
	hook.anim.PushBack({ 1367, 49, 9, 160 });
	hook.anim.PushBack({ 1376, 47, 9, 162 });

	hook.anim.PushBack({ 1385, 45, 9, 164 });
	hook.anim.PushBack({ 1394, 43, 9, 166 });
	hook.anim.PushBack({ 1403, 41, 9, 168 });
	hook.anim.PushBack({ 1412, 39, 9, 170 });
	hook.anim.PushBack({ 1421, 37, 9, 172 });

	//

	hook.anim.PushBack({ 1430, 35, 9, 174 });
	hook.anim.PushBack({ 1439, 33, 9, 176 });
	hook.anim.PushBack({ 1448, 31, 9, 178 });
	hook.anim.PushBack({ 1457, 29, 9, 180 });
	hook.anim.PushBack({ 1466, 27, 9, 182 });

	hook.anim.PushBack({ 1475, 25, 9, 184 });
	hook.anim.PushBack({ 1484, 23, 9, 186 });
	hook.anim.PushBack({ 1493, 21, 9, 188 });
	hook.anim.PushBack({ 1502, 19, 9, 190 });
	hook.anim.PushBack({ 1511, 17, 9, 192 });

	//

	hook.anim.PushBack({ 1520, 15, 9, 194 });
	hook.anim.PushBack({ 1529, 13, 9, 196 });
	hook.anim.PushBack({ 1538, 11, 9, 198 });
	hook.anim.PushBack({ 1547, 9, 9, 200 });
	hook.anim.PushBack({ 1556, 7, 9, 202 });

	hook.anim.PushBack({ 1565, 5, 9, 204 });
	hook.anim.PushBack({ 1574, 3, 9, 206 });
	hook.anim.PushBack({ 1583, 354, 9, 208 });
	hook.anim.PushBack({ 1592, 352, 9, 210 });
	hook.anim.PushBack({ 1601, 350, 9, 212 });


	hook.anim.pingpong = false;
	hook.anim.loop = false;
	hook.speed.y = -2.85f;
	//hook.lifetime = 100;
	hook.isAlive = true;
	hook.anim.speed = 1.0f;

	//static hok coords
	staticHook.anim.PushBack({ 1592, 352, 9, 210 });
	staticHook.anim.loop = true;
	staticHook.isAlive = true;
	staticHook.speed.y = -5.85f;

	//Rope Collider

	rope.type = ROPE_TYPE::ROPE;
	hook.type = ROPE_TYPE::HOOK;
	shot.type = ROPE_TYPE::SHOT;
	staticHook.type = ROPE_TYPE::STATIC_HOOK;

	return true;
}

update_status ModuleRopes::PreUpdate()
{

	//LOG("Unloading particles");

	 //Remove all particles scheduled for deletion
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
//	LOG("Unloading particles");

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
				if (ropes[i]->type == ROPE_TYPE::HOOK)
				{
					LOG("Rope hooked");
					//App->ropes->AddRope(App->ropes->staticHook, 230,30, Collider::Type::ROPE, ROPE_TYPE::STATIC_HOOK);

					//App->ropes->AddRope(App->ropes->rope, App->player->position.x,App->player->position.y + 10,  Collider::Type::ROPE, ROPE_TYPE::STATIC_HOOK);

 					App->ropes->AddHook(App->player->position.x, App->player->position.y + 10);

					App->ropes->AddHook(hookX,hookY);

				}

				if (ropes[i]->type != ROPE_TYPE::STATIC_HOOK)
				{
					delete ropes[i];
					ropes[i] = nullptr;
					break;
				}
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

void ModuleRopes::AddRope(const Rope& particle, int x, int y, Collider::Type colliderType,ROPE_TYPE newType)
{
	Rope* newrope = nullptr;
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		//Finding an empty slot for a new particle
		if (ropes[i] == nullptr)
		{
			App->audio->PlayFx(FiringFx);             // Sound


			Rope* newrope = new Rope(particle);
			
			newrope->type = newType;
			newrope->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newrope->position.y = y;

			//Adding the particle's collider
			if (particle.type == ROPE_TYPE::SHOT)
			{
				SDL_Rect shotCollider = { 0,0,19,7 };

				newrope->collider = App->collisions->AddCollider(shotCollider, Collider::Type::ROPE, this);
				newrope->collider->SetPos(App->player->position.x, App->player->position.y);
				

				App->particles->AddParticle(App->particles->shotParticle, App->player->position.x + 9, App->player->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::NONE);
			}
			
			else  {
				SDL_Rect ropeCollider = { 0,0,9,300 };
			
				newrope->collider = App->collisions->AddCollider(ropeCollider, Collider::Type::ROPE, this);
			}
			
			if (particle.type == ROPE_TYPE::EXPLOSION)
			{
				 //hookX = newrope->position.x;   hookY = newrope->position.y;

				 hookX = x;   hookY = y;

			}

			ropes[i] = newrope;
			break;
		}
	}
	/*return newrope;*/
}

void ModuleRopes::AddHook(int x, int y)
{
	Rope* newrope = nullptr;
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		//Finding an empty slot for a new particle
		if (ropes[i] == nullptr)
		{
			App->audio->PlayFx(HookedFX);


			Rope* newrope = new Rope(staticHook);

		newrope->type = ROPE_TYPE::STATIC_HOOK;
		newrope->position.x = x;						
		newrope->position.y = y;

		
			

			
		SDL_Rect ropeCollider = { 0,0,9,300 };

		newrope->collider = App->collisions->AddCollider(ropeCollider, Collider::Type::ROPE, this);
		newrope->collider->SetPos(x, y);

		ropes[i] = newrope;
		break;
		}
	}
}