//Minigolf program by Jason Knox and Shea Mentges
#pragma once
#include "Level.h"
#include <vector>
#include "InputManager.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL\GL.h>

#define GLM_SWIZZLE
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_access.hpp>


void display();

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
	InputManager *im;
	static void keyboard(unsigned char key, int y, int z);
	static void handle_mouse(int b, int s, int x, int y);
	static void handle_motion( int x, int y );
	glm::mat4 modelView, projection, camera;
	glm::mat4 modelTrans, mTrans, crTrans, csTrans, ctTrans;
};

