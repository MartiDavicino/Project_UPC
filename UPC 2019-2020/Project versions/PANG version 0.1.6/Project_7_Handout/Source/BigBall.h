#ifndef __BIGBALL_H__
#define __BIGBALL_H__

#include "Ball.h"
#include "Path.h"

class BigBall:public Ball
{
	public:
		// Constructor (x y coordinates in the world)
		// Creates animation and movement data and the collider
		BigBall(int x, int y);

		// The enemy is going to follow the different steps in the path
		// Position will be updated depending on the speed defined at each step
		void Update() override;

		void OnCollision(Collider* c1);
		

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation idle;

	//const float gravity = 600.0f;         // pixels / second^2

	//const float deltaTime = 1.0f / 60.0f; // More or less 60 frames per second

	//int Ball_vy = -150.0f;

	//int Ball_vx = 150.0f;
};

#endif