#pragma once
#include "Globals.h"

//Crea la Clase Module

class Module
{
public:
	//se llama al principio de la ejecuci�n de la aplicacion
	virtual bool Init();

	//se llama al principio del loop de la aplicacion
	virtual update_status PreUpdate();

	//se llama en medio del loop de la aplicacion
	virtual update_status Update();

	//se llama al final del loop de la aplicacion
	virtual update_status PostUpdate();

	//Se llama a esta funci�n al final de la applicacion
	virtual bool CleanUp();
};
