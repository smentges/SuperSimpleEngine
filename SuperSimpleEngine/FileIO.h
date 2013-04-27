//Minigolf program by Jason Knox and Shea Mentges
#pragma once
#include "Level.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class FileIO
{
	public:
		static FileIO& getInstance()
		{
			static FileIO instance; // Guaranteed to be destroyed.
									// Instantiated on first use.
			return instance;
		}
		Level LoadLevel(string fname);
		
		~FileIO(void);
	private:
		FileIO() {};                   // Constructor? (the {} brackets) are needed here.
		// Dont forget to declare these two. You want to make sure they
		// are unaccessable otherwise you may accidently get copies of
		// your singleton appearing.
		FileIO(FileIO const&);              // Don't Implement
		void operator=(FileIO const&); // Don't implement
		vector<string> splitVals(string line);
		Object3D *loadLevelObject(vector<string> line);
};

