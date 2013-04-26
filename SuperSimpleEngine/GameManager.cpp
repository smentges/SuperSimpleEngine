#include "GameManager.h"
#include "FileIO.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ShaderManager.h"
#include <string.h>
using namespace std;

GameManager::GameManager(void)
{
}


GameManager::~GameManager(void)
{
}

void GameManager::Run(int argc, char **argv) {
	Initialize(argc, argv);
}

void GameManager::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
};

void GameManager::keyboard(unsigned char x, int y, int z) {};



void GameManager::Initialize(int argc, char **argv)
{
	cout << endl << "Initializing Game...";
	CurrentLevel = FileIO::getInstance().LoadLevel("hole.00.db");	
	initGL(argc, argv);
	ShaderManager::getInstance().InitShaders();
	cout << endl << "Game initialized!";
	glutMainLoop();
}

void GameManager::initGL(int argc, char **argv) {
	cout << endl << "Initializing GLEW and FREEGLUT...";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Minigolf");
	glutInitWindowSize(512, 512);
	// GLEWINIT MUST BE CALLED AFTER MAKING A WINDOW, I DON'T KNOW WHY...
	string glewError = (char*)glewGetErrorString(glewInit());
	cout << endl << "GLEW ERROR: " + glewError;
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	cout << endl << "GLEW and FREEGLUT initialized!";
}
