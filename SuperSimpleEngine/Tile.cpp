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

	//Here's where we setup handles to each variable that is used in the shader
    //program. See the shader source code for more detail on what the difference
    //is between uniform and vertex attribute variables.
    shader->modelViewLoc = glGetUniformLocation(shader->program, "M");
    shader->projectionLoc = glGetUniformLocation(shader->program, "P");
    shader->normalMatrixLoc = glGetUniformLocation(shader->program, "M_n");
    shader->timeLoc = glGetUniformLocation(shader->program, "time");

    //notice that, since the vertex attribute norm is not used in the shader
    //program, shader->normalLoc = -1. If we access norm in the shader program,
    //then this value will be >= 0.
    shader->vertexLoc = glGetAttribLocation(shader->program, "pos");
    shader->normalLoc = glGetAttribLocation(shader->program, "norm");

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

	//cout << "TILE DRAWN";
}