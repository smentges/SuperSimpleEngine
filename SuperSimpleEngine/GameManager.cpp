#include "GameManager.h"
#include "FileIO.h"
#include <GL/freeglut.h>

GameManager::GameManager(void)
{
}


GameManager::~GameManager(void)
{
}

void GameManager::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
};

void GameManager::keyboard(unsigned char x, int y, int z) {};



void GameManager::Initialize(int argc, char **argv)
{
	CurrentLevel = FileIO::getInstance().LoadLevel("hole.00.db");	
	initOpenGL(argc, argv);
}

void GameManager::initOpenGL(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Minigolf");
	glutInitWindowSize(512, 512);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}
