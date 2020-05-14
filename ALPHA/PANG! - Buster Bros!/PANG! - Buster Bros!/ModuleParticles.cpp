#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/particles.png");
	FiringFx = App->audio->LoadFx("Assets/[FX]- firing sound.wav");

	// Explosion particle
	/*explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;*/

	dieRightAnim.anim.PushBack({ 6,375 ,34,24 });
	dieLeftAnim.anim.PushBack({ 40,375,34,24 });
	dieRightAnim.speed.y = dieLeftAnim.speed.y = 2;
	dieRightAnim.speed.x = 2;
	dieLeftAnim.speed.x = -dieRightAnim.speed.x;


	bigExplosion.anim.PushBack({ 120,231,51,42 });
	bigExplosion.anim.PushBack({ 175,232,46,42 });
	bigExplosion.anim.PushBack({ 223,231, 44,40 });
	bigExplosion.anim.PushBack({ 268,225,52,48});
	bigExplosion.anim.loop = false;

	mediumExplosion.anim.PushBack({ 325,238,33,27 });
	mediumExplosion.anim.PushBack({ 359,236,38,27 });
	mediumExplosion.anim.PushBack({ 402,233,36,36 });
	mediumExplosion.anim.PushBack({ 442,236,36,34 });
	mediumExplosion.anim.loop = false;

	smallExplosion.anim.PushBack({ 495,245,23,18 });
	smallExplosion.anim.PushBack({ 516,246,18,21 });
	smallExplosion.anim.PushBack({ 540,246,22,20 });
	smallExplosion.anim.loop = false;

	blink.anim.PushBack({ 0,405,400,208 });
	blink.anim.loop = false;
	blink.lifetime = 30.0f;
	blink.frameCount = 1;


	// w: 34 h: 40
	inmune.anim.PushBack({ 165,362,34,40 });
	inmune.anim.PushBack({ 165,365,34,40 });
	inmune.anim.loop = true;
	inmune.anim.speed = 0.4f;
	inmune.speed.x = -2;

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
	hook.lifetime = 100;
	hook.isAlive = true;
	hook.anim.speed = 1.0f;

	//shot

	shotParticle.anim.PushBack({ 214,368,8,8 });
	shotParticle.anim.PushBack({ 229,362,10,11 });
	shotParticle.anim.PushBack({ 246,362,20,20 });
	shotParticle.anim.PushBack({ 261,364,20,20 });
	shotParticle.anim.loop = false;
	
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


	//Types of each particle
	shot.type = PARTICLE_TYPE::SHOT;
	rope.type = PARTICLE_TYPE::ROPE;
	hook.type = PARTICLE_TYPE::HOOK;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			if (c2->type == Collider::Type::TOP)
			{
				delete particles[i];
				particles[i] = nullptr;
				break;
			}
			if (c2->type == Collider::Type::BALL)
			{
				delete particles[i];
				particles[i] = nullptr;
				break;
			}
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	dieLeftAnim.speed.y = dieLeftAnim.speed.y + (gravity * deltaTime);

	dieLeftAnim.position.y = dieLeftAnim.position.y + (dieLeftAnim.speed.y * deltaTime) + (gravity * (deltaTime * deltaTime));
	dieLeftAnim.position.x = dieLeftAnim.position.x + (dieLeftAnim.speed.x * deltaTime);

	dieRightAnim.speed.y = dieRightAnim.speed.y + (gravity * deltaTime);

	dieRightAnim.position.y = dieRightAnim.position.y + (dieRightAnim.speed.y * deltaTime) + (gravity * (deltaTime * deltaTime));
	dieRightAnim.position.x = dieRightAnim.position.x + (dieRightAnim.speed.x * deltaTime);


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));


			if (particle->type == PARTICLE_TYPE::INMUNE)
			{
				particle->speed.x = App->player->isMovingAt.x;
				//particle->position.x += particle->speed.x;
				//particle->position.x++;
				////particle->position.SetTo(App->player->position.x, App->player->position.y);
				//particle->SetPos(App->player->position.x, App->player->position.y);
				//
			}
		}
		
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay,PARTICLE_TYPE type)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;


			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
			if (type != PARTICLE_TYPE::NONE)
				p->type = type;

			particles[i] = p;
			break;
		}
	}
}

void ModuleParticles::AddRope(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newrope = nullptr;
	for (uint i = 0; i < MAX_ACTIVE_ROPES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			App->audio->PlayFx(FiringFx);             // Sound


			Particle* newrope = new Particle(particle);
			newrope->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newrope->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newrope->position.y = y;

			//Adding the particle's collider
	     if(particle.type==PARTICLE_TYPE::SHOT)
		 { 
			 newrope->collider = App->collisions->AddCollider(newrope->anim.GetCurrentFrame(), Collider::Type::ROPE, this);
		 }
			
		 else if(particle.type==PARTICLE_TYPE::HOOK || particle.type==PARTICLE_TYPE::ROPE)
		 {
				SDL_Rect ropeCollider = { 0,0,9,300 };

				//newrope->collider = App->collisions->AddCollider(newrope->anim.GetCurrentFrame(), Collider::Type::ROPE, this);
				newrope->collider = App->collisions->AddCollider(ropeCollider, Collider::Type::ROPE, this);



			}


			particles[i] = newrope;
			break;
		}
	}
	/*return newrope;*/
}