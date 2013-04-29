//Minigolf program by Jason Knox and Shea Mentges
#include "GameManager.h"
#include "FileIO.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include "InputManager.h"
#include "Shader.h"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_access.hpp>

using namespace std;
using namespace glm;
void GameManager::Run(int argc, char **argv) {
	Initialize(argc, argv);
}

void GameManager::Initialize(int argc, char **argv) {
	cout << endl << "Initializing Game...";

	initGL(argc, argv);
	setupShaders();
	CurrentLevel = FileIO::getInstance().LoadLevel("hole.00.db");

	cout << endl << "Game initialized!";
	cout << endl << "Entering main loop...";

	glutMainLoop();
}

void GameManager::initGL(int argc, char **argv) {
	InputManager *im = &InputManager::getInstance();
	cout << endl << "Initializing GLEW and FREEGLUT...";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Minigolf");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(handle_motion);
	glutMouseFunc(handle_mouse);
	glutIdleFunc(idle);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	camera = glm::lookAt(glm::vec3(10,10,10), glm::vec3(0,0,0), glm::vec3(0,0,1));

    projection = glm::perspective(
            glm::float_t(45),
            glm::float_t(512) / glm::float_t(512),
            glm::float_t(0.1),
            glm::float_t(1000.0)
    );

	// GLEWINIT MUST BE CALLED AFTER MAKING A WINDOW, I DON'T KNOW WHY...
	string glewError = (char*)glewGetErrorString(glewInit());
	cout << endl << "GLEW ERROR: " + glewError;

	cout << endl << "GLEW and FREEGLUT initialized!";
}

void GameManager::setupShaders() {
	Shader *shader = &Shader::getInstance();
	*shader = Shader("gles.vert", "gles.frag");

	shader->modelViewLoc = glGetUniformLocation(shader->program, "M");
    shader->projectionLoc = glGetUniformLocation(shader->program, "P");

	shader->vertexLoc = glGetAttribLocation(shader->program, "pos");
}


void display() {
	GameManager *gm = &GameManager::getInstance();
	glViewport(0,0,512,512);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gm->modelView = glm::mat4();
    gm->modelView = gm->modelView * gm->mTrans;
	gm->camera = lookAt(vec3(10,10,10), vec3(0, 0, 0), vec3(0, 0, 1));
	mat4 modelCam = gm->camera * gm->modelView;
	
	Shader *shader = &Shader::getInstance();

	glUseProgram(shader->program);

	glUniformMatrix4fv(
		shader->modelViewLoc, 1, GL_FALSE, value_ptr(modelCam));

	glUniformMatrix4fv(
		shader->projectionLoc, 1, GL_FALSE, value_ptr(gm->projection));

	
	// Call draw function on all drawable objects in level.
	for(unsigned int i = 0; i < gm->CurrentLevel.LevelObjects.size(); i++) { 
		gm->CurrentLevel.LevelObjects[i]->draw(0.0);
	}

	
	glutPostRedisplay();
};

void GameManager::keyboard(unsigned char key, int y, int z) 
{
	InputManager *im = &InputManager::getInstance();

	switch(key)
	{
	case 27:
		exit(0);
		break;
	case 'q':
		im->curr_mode = TRANSLATE_X;
		cout << "translating via x" << endl;
		break;
	case 'w':
		im->curr_mode = TRANSLATE_Y;
		cout << "translating via y" << endl;
		break;
	case 'e':
		im->curr_mode = TRANSLATE_Z;
		cout << "translating via z" << endl;
		break;
	case 'r':
		im->curr_mode = ROTATE_X;
		cout << "rotating via x" << endl;
		break;
	case 't':
		im->curr_mode = ROTATE_Y;
		cout << "rotating via y" << endl;
		break;
	case 'y':
		im->curr_mode = ROTATE_Z;
		cout << "rotating via z" << endl;
		break;
	}
};

void GameManager::handle_mouse(int b, int s, int x, int y)
{
	InputManager *im = &InputManager::getInstance();
	if ( s == GLUT_DOWN ) {		// Store button state if mouse down
		im->btn[ b ] = 1;
		cout << "clicked" << endl;
	} else {
		im->btn[ b ] = 0;
	}

	im->mouse_x = x;
	im->mouse_y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
}

void GameManager::handle_motion( int x, int y )
{
	InputManager *im = &InputManager::getInstance();
	GameManager *gm = &GameManager::getInstance();

	im->new_mouse_x = x;
	im->new_mouse_y = y;
	im->mouseDiffX = im->new_mouse_x - im->mouse_x;
	im->mouseDiffY = im->new_mouse_y - im->mouse_y;
	im->mouse_x = im->new_mouse_x;
	im->mouse_y = im->new_mouse_y;

	gm->modelView = glm::mat4();

	if ( !im->btn[ 0 ] ) {			// Left button not depressed?
		return;
	}


	switch( im->curr_mode ) {
	case TRANSLATE_X:			// X translation
		gm->mTrans = glm::translate(gm->mTrans, glm::vec3((static_cast<float>(im->mouseDiffX) / -10),0,0));
		cout << "translating" << endl;
		break;
	case TRANSLATE_Y:			// Y translation
		gm->mTrans = glm::translate(gm->mTrans, glm::vec3(0,(static_cast<float>(im->mouseDiffX) / 10),0));
		cout << "translating" << endl;
		break;
	case TRANSLATE_Z:			// Z translation
		gm->mTrans = glm::translate(gm->mTrans, glm::vec3(0,0,(static_cast<float>(im->mouseDiffX) / -10)));
		cout << "translating" << endl;
	case ROTATE_X:			// X rotation
		gm->mTrans = glm::rotate(gm->mTrans, static_cast<float>(im->mouseDiffX), glm::vec3(1,0,0));
		cout << "rotating" << endl;
		break;
	case ROTATE_Y:			// Y rotation
		gm->mTrans = glm::rotate(gm->mTrans, static_cast<float>(im->mouseDiffX), glm::vec3(0,1,0));
		cout << "rotating" << endl;
		break;
	case ROTATE_Z:			// Z rotation
		gm->mTrans = glm::rotate(gm->mTrans, static_cast<float>(im->mouseDiffX), glm::vec3(0,0,1));
		cout << "rotating" << endl;
		break;
	}

	gm->modelView = gm->modelView * gm->mTrans;
}

void GameManager::idle() {
	glutPostRedisplay();
}

GameManager::GameManager(void) {}

GameManager::~GameManager(void) {}


