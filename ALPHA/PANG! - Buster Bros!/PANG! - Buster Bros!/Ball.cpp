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
	LOG("Ball Destroyed\n");

	//Must play different animations depending of ball size
	//App->particles->AddParticle(App->particles->bigExplosion, position.x, position.y);



	App->audio->PlayFx(destroyedFx);


	SetToDelete();
}

void Ball::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

BALL_TYPE Ball::GetType() {
	return this->type;
}