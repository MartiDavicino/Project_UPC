#ifndef __INTERFACE_ELEMENT_H__
#define __INTERFACE_ELEMENT_H__

#include "Animation.h"
#include "p2Point.h"


enum class INTERFACE_ELEMENT_TYPE {
	UI,
	EQUIPPED
};

struct InterfaceElement
{
public:
	// Constructor
	InterfaceElement();

	// Copy constructor
	InterfaceElement(const InterfaceElement& p);

	// Destructor
	~InterfaceElement();

	// Called in ModuleParticles' Update
	// Handles the logic of the particle
	// Returns false when the particle reaches its lifetime
	bool Update();



public:
	// Defines the position in the screen
	INTERFACE_ELEMENT_TYPE type;

	iPoint position;
	iPoint speed;
	

	SDL_Rect frame;

	// A set of rectangle sprites


	//Animation* currentAnim;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool display = true;

	int equipped;
	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	uint lifetime = 0;

	Animation anim;

	/*void Display(const SDL_Rect& rect)
	{
		frame = rect;
	}*/


};

#endif 


