#include <iostream>
#include "FileIO.h"
using namespace std;

int main() {
	FileIO::getInstance().LoadLevel("hole.00.db");

	cin.get();
}