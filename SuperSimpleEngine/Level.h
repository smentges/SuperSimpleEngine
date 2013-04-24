#pragma once
#include <vector>
#include "Tile.h"
#include "Object3D.h"
using namespace std;

class Level
{
public:
	vector<Object3D> LevelObjects;
	Level(void);
	~Level(void);
};

