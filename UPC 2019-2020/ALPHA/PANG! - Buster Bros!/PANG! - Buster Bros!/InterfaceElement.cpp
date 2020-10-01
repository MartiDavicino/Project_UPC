#include "InterfaceElement.h"
#include "ModuleInterface.h"
#include "Application.h"

InterfaceElement::InterfaceElement()
{
	

}

InterfaceElement::InterfaceElement(const InterfaceElement& p) : anim(p.anim), position(p.position)
{
	
}

InterfaceElement::~InterfaceElement()
{

}

bool InterfaceElement::Update()
{
	
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!display && frameCount >= 0)
		display = true;

	if (display)
	{
		//if(this->type != INTERFACE_ELEMENT_TYPE::EQUIPPED)
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
			{
				//LOG("lifetime reached");
				//App->interfaceElements->Equip(App->interfaceElements->none);

				if (this->type == INTERFACE_ELEMENT_TYPE::EQUIPPED)
				{
					//lifetime = 200;
					LOG("lifetime reached");
					this->type = INTERFACE_ELEMENT_TYPE::UNEQUIPPED;
				}
				else
					ret = false;
			}

		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
		{ret = false;
		}
		// Update the position in the screen


		/*if (collider != nullptr)
			collider->SetPos(position.x, position.y);*/
	}

	

	return ret;
}