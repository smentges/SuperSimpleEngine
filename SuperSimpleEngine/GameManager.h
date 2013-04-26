#pragma once
#include "Level.h"
#include <vector>
#include "InputManager.h"

void display();
void keyboard(unsigned char x, int y, int z);

class GameManager
{
private:
	void initGL(int argi, char** argv);
public:
	static GameManager& getInstance()
	{
		static GameManager instance; // Guaranteed to be destroyed.
								// Instantiated on first use.
		return instance;
	}

	GameManager(void);
	~GameManager(void);

	void Run(int argi, char** argv); //initialize, call game loop
	void Tick(void); //update, draw
	void Initialize(int argc, char **argv);

	vector<Level> Course;
	Level CurrentLevel;
	//Camera camera;
	static InputManager *im;
	static void keyboard(unsigned char key, int y, int z);
	static void handle_mouse(int b, int s, int x, int y);
	static void handle_motion( int x, int y );
};

