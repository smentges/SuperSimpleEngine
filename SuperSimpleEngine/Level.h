#pragma once
#include <vector>
#include "Tile.h"
using namespace std;

class Level
{
public:
	vector<Tile> Tiles;
	Level(void);
	~Level(void);
};

