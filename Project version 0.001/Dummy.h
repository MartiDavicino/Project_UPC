#include "Module.h"

class ModuleDummy : public Module
{
public:

	bool Init();

	update_status PreUpdate();

	update_status Update();

	update_status PostUpdate();

	bool CleanUp();
};
