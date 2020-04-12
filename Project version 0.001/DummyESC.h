#include "Module.h"

//Override del Preupdate de ModuleDummy

class ModuleDummyESC :public Module {

public:
	update_status PreUpdate() override;

};
