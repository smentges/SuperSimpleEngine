#include "GameManager.h"
#include "FileIO.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ShaderManager.h"
#include <string.h>

using namespace std;

void GameManager::Run(int argc, char **argv) {
	Initialize(argc, argv);
}

void GameManager::Initialize(int argc, char **argv) {
	cout << endl << "Initializing Game...";

	initGL(argc, argv);

	ShaderManager *sm = &ShaderManager::getInstance();
	sm->InitShaders();

	CurrentLevel = FileIO::getInstance().LoadLevel("hole.00.db");	

	cout << endl << "Game initialized!";
	cout << endl << "Entering main loop...";

	glutMainLoop();
}

void GameManager::initGL(int argc, char **argv) {
	cout << endl << "Initializing GLEW and FREEGLUT...";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Minigolf");

	// GLEWINIT MUST BE CALLED AFTER MAKING A WINDOW, I DON'T KNOW WHY...
	string glewError = (char*)glewGetErrorString(glewInit());
	cout << endl << "GLEW ERROR: " + glewError;

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	cout << endl << "GLEW and FREEGLUT initialized!";
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Think of VBOs as slaves to VAOs. Think of each VBO as an element of a VAO.
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);	//This is the VAO we are talking about now.

	// Call draw function on all drawable objects in level.
	GameManager *gm = &GameManager::getInstance();
	for(unsigned int i = 0; i < gm->CurrentLevel.LevelObjects.size(); i++) { 
		gm->CurrentLevel.LevelObjects[i]->draw(0.0);
	}

	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glutSwapBuffers();
	glutPostRedisplay();
};

void keyboard(unsigned char x, int y, int z) {};

GameManager::GameManager(void) {}

GameManager::~GameManager(void) {}


