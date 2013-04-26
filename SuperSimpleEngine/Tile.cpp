#include "Tile.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

Tile::Tile(int id, int edges, float vertInfo[], int neighbors[])
{
	_id = id;
	_edges = edges;
	for(int i = 0; i < 12; i++){
		_vertInfo[i] = vertInfo[i];
	}
	for(int j = 0; j < 4; j++){
		_neighbors[j] = neighbors[j];
	}
	cout << "Tile created with id " << _id << ", edges " << _edges << "," << endl;
	cout << "vertices ";
	for(int i = 0; i < 12; i++){
		cout << _vertInfo[i] << " ";
	}
	cout << "," << endl;
	cout << "edges ";
	for(int j = 0; j < 4; j++){
		cout << _neighbors[j] << " ";
	}
	cout << endl;

	GLuint buffer;


}


Tile::~Tile(void)
{
}
