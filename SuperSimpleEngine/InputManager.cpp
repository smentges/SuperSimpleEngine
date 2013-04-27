//Minigolf program by Jason Knox and Shea Mentges
#include "InputManager.h"


InputManager::InputManager(void)
{
	for(int i = 0; i < 3; i++)
	{
		btn[i] = 0;
		translate[i] = 0;
		rotate[i] = 0;
	}
	curr_mode = TRANSLATE_X;
}


InputManager::~InputManager(void)
{
}
