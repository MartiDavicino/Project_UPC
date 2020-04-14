#include "BigBall.h"

#include "Ball.h"
#include "Path.h"

#include "Application.h"
#include "ModuleCollisions.h"

BigBall::BigBall(int x, int y) : Ball(x, y)
{
	idle.PushBack({ 1,6,48,40 });

	idle.loop = true;
	idle.speed = 0.1f;
	currentAnim = &idle;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void BigBall::Update()
{
	/*waveRatio += waveRatioSpeed;

	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	position.x -= 1;*/

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Ball::Update();
}
