#pragma once
#include "Level.h"
#include <vector>
class GameManager
{
private:

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
	void initGL(int argi, char** argv);
	// For some reason I had to make these static in order to pass them into the display and keyboard funcs.
	static void display();
	static void keyboard(unsigned char x, int y, int z);
};

