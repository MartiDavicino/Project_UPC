#include "mainH.h"

enum class main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

// Report memory leaks sirve para ver si se escapa en alguna parte memoria dinámica.

// Los LOGS son para que en la pestaña depurar saldran que es cada cosa y que estan haciendo.

//El sistema de Modulos y Dummies actual es un poco un ejemplo para ver como funcionan y estan tal cual como en los todos.
//Se pueden cambiar a nuesto antojo.


int main(int argc, char* argv[]) {
	ReportMemoryLeaks();

	int main_return = EXIT_FAILURE;
	main_states state = main_states::MAIN_CREATION;

	while (state != main_states::MAIN_EXIT)
	{
		switch (state)
		{

		//Crea la App

		case main_states::MAIN_CREATION:
		{
			LOG("Application Creation --------------\n");
			App = new Application();
			state = main_states::MAIN_START;
		}	break;

		//Inicia la App

		case main_states::MAIN_START:
		{
			LOG("Application Start --------------\n");
			if (App->Init() == false)
			{
				LOG("Application Init exits with error -----\n");
				state = main_states::MAIN_EXIT;
			}
			else
			{
				state = main_states::MAIN_UPDATE;
			}
		}	break;

		//Hace los updates de la App

		case main_states::MAIN_UPDATE:
		{
			update_status status = App->Update();

			if (status == update_status::UPDATE_ERROR)
			{
				LOG("Application Update exits with error -----\n");
				state = main_states::MAIN_EXIT;
			}
			else if (status == update_status::UPDATE_STOP)
			{
				state = main_states::MAIN_FINISH;
			}
		}	break;

		//Finaliza el App

		case main_states::MAIN_FINISH:
		{
			LOG("Application Finish --------------\n");
			if (App->Init() == false)
			{
				LOG("Application Init exits with error -----\n");
				state = main_states::MAIN_EXIT;
			}
			else
			{
				LOG("Application CleanUp exits with error -----\n");
				state = main_states::MAIN_EXIT;
			}
		}	break;
		}
	}

	LOG("\nBye :)\n");

	// Elimina la memoria de App
	delete App;

	return main_return;
}