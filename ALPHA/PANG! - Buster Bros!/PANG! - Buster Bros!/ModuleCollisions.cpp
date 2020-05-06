#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL_A][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL_A][Collider::Type::BALL] = true;
	matrix[Collider::Type::WALL_A][Collider::Type::ROPE] = true;
	matrix[Collider::Type::WALL_A][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::DROP] = false;


	matrix[Collider::Type::PLAYER][Collider::Type::WALL_A] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL_D] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ROPE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DROP] = false;

	matrix[Collider::Type::BALL][Collider::Type::WALL_A] = true;
	matrix[Collider::Type::BALL][Collider::Type::WALL_D] = true;
	matrix[Collider::Type::BALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BALL][Collider::Type::BALL] = false;
	matrix[Collider::Type::BALL][Collider::Type::ROPE] = true;
	matrix[Collider::Type::BALL][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::BALL][Collider::Type::DROP] = false;

	matrix[Collider::Type::ROPE][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::ROPE][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::ROPE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ROPE][Collider::Type::BALL] = true;
	matrix[Collider::Type::ROPE][Collider::Type::ROPE] = false;
	matrix[Collider::Type::ROPE][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::ROPE][Collider::Type::DROP] = false;


	matrix[Collider::Type::FLOOR][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::BALL] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::ROPE] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::DROP] = false;

	matrix[Collider::Type::WALL_D][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL_D][Collider::Type::BALL] = true;
	matrix[Collider::Type::WALL_D][Collider::Type::ROPE] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::DROP] = false;

	matrix[Collider::Type::DROP][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::DROP][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::DROP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DROP][Collider::Type::BALL] = false;
	matrix[Collider::Type::DROP][Collider::Type::ROPE] = false;
	matrix[Collider::Type::DROP][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::DROP][Collider::Type::DROP] = false;

	
}


update_status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
			
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return update_status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::WALL_A: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::WALL_D: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 230, 255, alpha);
			break;
			case Collider::Type::FLOOR: // purple
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 230, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::BALL: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::ROPE: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::DROP: //purple
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 230, alpha);
		
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{

			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

Collider* ModuleCollisions::AddDynamicCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			for (int total = 0; total < 210; total++) {
				rect.y = 210 - total;
				total += 2;
			}

			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}


void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}