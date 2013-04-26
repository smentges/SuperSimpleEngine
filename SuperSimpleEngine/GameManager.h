#pragma once
#include "Level.h"
#include <vector>
class GameManager
{
private:
	void initOpenGL(int argi, char** argv);
public:
	GameManager(void);
	~GameManager(void);
	void Run(int argi, char** argv); //initialize, call game loop
	void Tick(void); //update, draw
	void Initialize(int argc, char **argv);
	vector<Level> Course;
	Level CurrentLevel;
	//Camera camera;

	// For some reason I had to make these static in order to pass them into the display and keyboard funcs.
	static void display();
	static void keyboard(unsigned char x, int y, int z);
};

