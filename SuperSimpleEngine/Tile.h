//Minigolf program by Jason Knox and Shea Mentges 
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Object3D.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "InputManager.h"

using namespace std;

class Tile: public Object3D
{
public:
	void draw(float deltatime);
	Tile(int id, int edges, float vertInfo[], int neighbors[]);
	~Tile(void);
	GLint vertexBuffer;
private:
	int _id;
	int _edges;
	float _vertInfo[12];
	int _neighbors[4];
	static InputManager *im;
};

