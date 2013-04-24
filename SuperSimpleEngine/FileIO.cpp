#include "FileIO.h"

Level FileIO::LoadLevel(string fname) {
	cout << "Reading level from file..." << endl;
	ifstream file;
	string line = "";
	file.open(fname);
	
	if(!file) {
		cout << "Unable to open file" << endl;
		exit(-1);
	}
	
	while(!file.eof()) {
		vector<string> lineElements;
		getline(file, line);
		if(line != "") {
			lineElements = splitVals(line);
			loadLevelObject(lineElements);
		}
	}
	
	cout << "Level loaded from file!" << endl << endl;
	return Level();
}

void FileIO::loadLevelObject(vector<string> line) {
	if(line[0] == "tile") {
		cout << "Reading in a tile from file..." << endl;
		int id = atoi(line[1].c_str());
		int edges = atoi(line[2].c_str());
		float vertInfo[12];
		int neighbors[4];

		for(int i = 0; i < 12; i++)
			vertInfo[i] = atof(line[i+3].c_str());

		for(int i = 0; i < 4; i++)
			neighbors[i] = atof(line[i+15].c_str());
	}
	else {
		cout << "Keyword: " + line[0] + " not reckognized." << endl;
	}
}

vector<string> FileIO::splitVals(string line) {
	string buf; // Have a buffer string
    stringstream ss(line); // Insert the string into a stream

    vector<string> tokens; // Create vector to hold our words

    while (ss >> buf)
        tokens.push_back(buf);

	return tokens;
}


FileIO::~FileIO(void)
{
}