#include "Ball.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Ball::Ball(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Ball::~Ball()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Ball::GetCollider() const
{
	return collider;
}

void Ball::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Ball::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Ball::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);
}