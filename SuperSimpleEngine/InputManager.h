//Minigolf program by Jason Knox and Shea Mentges
#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

typedef enum {
  TRANSLATE_X,
  TRANSLATE_Y,
  TRANSLATE_Z,
  ROTATE_X,
  ROTATE_Y,
  ROTATE_Z
} mode;

class InputManager
{
public:
	static InputManager& getInstance()
	{
		static InputManager instance; // Guaranteed to be destroyed.
								// Instantiated on first use.
		return instance;
	}
	InputManager(void);
	~InputManager(void);
	int btn[ 3 ];		// Current button state
	mode   curr_mode;		// Current mouse mode
	float  translate[ 3 ];		// Current translation values
	float  rotate[ 3 ];		// Current rotation values
	int    mouse_x, mouse_y;		// Current mouse position
	int new_mouse_x, new_mouse_y;
	int mouseDiffX, mouseDiffY;
};

