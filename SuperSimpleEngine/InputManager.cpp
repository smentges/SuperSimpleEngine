#include "InputManager.h"


InputManager::InputManager(void)
{
	for(int i = 0; i < 3; i++)
	{
		btn[i] = 0;
		translate[i] = 0;
		rotate[i] = 0;
	}
	curr_mode = TRANSLATE;
}


InputManager::~InputManager(void)
{
}
