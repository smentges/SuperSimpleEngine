//Minigolf program by Jason Knox and Shea Mentges
#include <iostream>
#include "FileIO.h"
#include "GameManager.h"
#include "Shader.h"
using namespace std;



int main(int argc, char **argv) {
	GameManager *gm = &GameManager::getInstance();
	gm->Run(argc, argv);
}
