//Minigolf program by Jason Knox and Shea Mentges
#include "Tile.h"
#include "Shader.h"

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

	Shader *shader = &Shader::getInstance();

    //Create buffers for the vertex and normal attribute arrays
    GLuint bufs[1];
    glGenBuffers(1, bufs);

    shader->vertexBuffer = bufs[0];

    //This is where we pass the vertex/normal data to the GPU.
    //In genereal, the procedure for working with buffers is:
    //  1. Tell OpenGL which buffer we're using (glBindBuffer)
    //  2. Tell OpenGL what to do with the buffer (e.g. fill buffer, use the
    //     in the buffer, etc).
    //
    //Here we are filling the buffers (glBufferData). The last parameter
    //(GL_STATIC_DRAW), says that our intention is to not change the values in
    //these buffers. If we were going to be modifying these positions frequently
    //at runtime, we might want to make this GL_DYNAMIC_DRAW instead. For right
    //now, it's not too important which you choose.

    glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer);
    glBufferData(
            GL_ARRAY_BUFFER, //what kind of buffer (an array)
            12 * sizeof(float), //size of the buffer in bytes
            &_vertInfo[0], //pointer to data we want to fill the buffer with
            GL_STATIC_DRAW //how we intend to use the buffer
            );

	cout << endl;
}


Tile::~Tile(void)
{

}

void Tile::draw(float deltatime) {
	//cout << "DRAWING TILE";
	Shader *shader = &Shader::getInstance();
	glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer); //which buffer we want
	//to use
	glEnableVertexAttribArray(shader->vertexLoc); //enable the attribute
	glVertexAttribPointer(
			shader->vertexLoc, //handle to variable in shader program
			3, //vector size (e.g. for texture coordinates this could be 2).
			GL_FLOAT, //what type of data is (e.g. GL_FLOAT, GL_INT, etc.)
			GL_FALSE, //normalize the data?
			0, //stride of data (e.g. offset in bytes). Most of the time leaving
			//this at 0 (assumes data is in one, contiguous array) is fine
			//unless we're doing something really complex.
			NULL //since our stride will be 0 in general, leaving this NULL is
			//also fine in general
	);

	glDrawArrays(GL_TRIANGLES, 0, 4);
	glutSwapBuffers();

	//cout << "TILE DRAWN";
}