#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Tile
{
public:
	Tile(int id, int edges, float vertInfo[], int neighbors[]);
	~Tile(void);
private:
	int _id;
	int _edges;
	float _vertInfo[12];
	int _neighbors[4];
};

