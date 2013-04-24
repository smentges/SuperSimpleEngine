#pragma once
#include "Level.h"
#include <vector>
class GameManager
{
public:
	GameManager(void);
	~GameManager(void);
	void Run(int argi, char** argv); //initialize, call game loop
	void Tick(void); //update, draw
	void Initialize();
	vector<Level> Course;
	Level CurrentLevel;
	//Camera camera;
};

