#include <iostream>
#include "FileIO.h"
#include "GameManager.h"
#include "ShaderManager.h"
using namespace std;

int main(int argc, char **argv) {
	GameManager gm = GameManager::getInstance();
	gm.Run(argc, argv);

	cin.get();
}
