#include "Tile.h"

using namespace std;
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
		_vertInfo[i] *= 5.0;
		cout << _vertInfo[i] << " ";
	}
	cout << "," << endl;
	cout << "edges ";
	for(int j = 0; j < 4; j++){
		cout << _neighbors[j] << " ";
	}
	cout << endl;



}


Tile::~Tile(void)
{

}

void Tile::draw(float deltatime) {
	cout << "DRAWING TILE";

	ShaderManager *sm = &ShaderManager::getInstance();
	GLuint vPosition = glGetAttribLocation(sm->simpleShaderProgram, "vPosition");
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // Think of this procedure as making the following procedures apply to buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertInfo), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_vertInfo), _vertInfo);
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	cout << "TILE DRAWN";
}