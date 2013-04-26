#include "GameManager.h"
#include "FileIO.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ShaderManager.h"
#include <string.h>
#include "InputManager.h"

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
	InputManager im = InputManager::getInstance();
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
	glutMotionFunc(handle_motion);
	glutMouseFunc(handle_mouse);

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

void GameManager::keyboard(unsigned char key, int y, int z) 
{
	InputManager im = InputManager::getInstance();

	switch(key)
	{
	case 27:
		exit(0);
		break;
	case 't':
		im.curr_mode = TRANSLATE;
		break;
	case 'x':
		im.curr_mode = ROTATE_X;
		break;
	case 'y':
		im.curr_mode = ROTATE_Y;
		break;
	case 'z':
		im.curr_mode = ROTATE_Z;
		break;
	}
};

void GameManager::handle_mouse(int b, int s, int x, int y)
{
	InputManager im = InputManager::getInstance();
	if ( s == GLUT_DOWN ) {		// Store button state if mouse down
		im.btn[ b ] = 1;
	} else {
		im.btn[ b ] = 0;
	}

	im.mouse_x = x;
	im.mouse_y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
}

void GameManager::handle_motion( int x, int y )
{
	InputManager im = InputManager::getInstance();

	float	 x_ratchet;			// X ratchet value
	float	 y_ratchet;			// Y ratchet value


	if ( !im.btn[ 0 ] ) {			// Left button not depressed?
		return;
	}

	x_ratchet = glutGet( GLUT_WINDOW_WIDTH ) / 10.0;
	y_ratchet = glutGet( GLUT_WINDOW_HEIGHT ) / 10.0;

	//  Windows XP has y = 0 at top, GL has y = 0 at bottom, so reverse y

	y = glutGet( GLUT_WINDOW_HEIGHT ) - y;

	switch( im.curr_mode ) {
	case TRANSLATE:			// XY translation
		im.translate[ 0 ] += (float) ( x - im.mouse_x ) / x_ratchet;
		im.translate[ 1 ] += (float) ( y - im.mouse_y ) / y_ratchet;
		break;
	case ROTATE_X:			// X rotation
		x_ratchet /= 10.0;
		im.rotate[ 0 ] += (float) ( x - im.mouse_x ) / x_ratchet;
		break;
	case ROTATE_Y:			// Y rotation
		x_ratchet /= 10.0;
		im.rotate[ 1 ] += (float) ( x - im.mouse_x ) / x_ratchet;
		break;
	case ROTATE_Z:			// Z rotation
		x_ratchet /= 10.0;
		im.rotate[ 2 ] += (float) ( x - im.mouse_x ) / x_ratchet;
		break;
	}

	im.mouse_x = x;				// Update cursor position
	im.mouse_y = y;

	glutPostRedisplay();
}

GameManager::GameManager(void) {}

GameManager::~GameManager(void) {}


