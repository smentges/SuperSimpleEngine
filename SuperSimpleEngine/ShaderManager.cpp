#include "ShaderManager.h"
#include <iostream>
#include <fstream>
using namespace std;

// http://nehe.gamedev.net/article/glsl_an_introduction/25007/
ShaderManager::ShaderManager(void)
{
}

void ShaderManager::InitShaders() {
	cout << endl << "Initializing shaders...";

	GLenum tempVertShaderObj, tempFragShaderObj;

	//Make the paths private variables later
	simpleShaderVertSource = getShaderSource("Shaders/SimpleShaders/simpleVert.txt");
	simpleShaderFragSource = getShaderSource("Shaders/SimpleShaders/simpleFrag.txt");

	// Make program
	simpleShaderProgram = glCreateProgram();

	// Make shaders
	tempVertShaderObj = glCreateShader(GL_VERTEX_SHADER);
	tempFragShaderObj = glCreateShader(GL_FRAGMENT_SHADER);

	// Load Shader Sources
	glShaderSource(tempVertShaderObj, 1, (const GLchar**) &simpleShaderVertSource, NULL);
	glShaderSource(tempFragShaderObj, 1, (const GLchar**) &simpleShaderFragSource, NULL);

	// Compile Shaders
	glCompileShader(tempVertShaderObj);
	glCompileShader(tempFragShaderObj);

	// Attach Shaders
	glAttachShader(simpleShaderProgram, tempVertShaderObj);
	glAttachShader(simpleShaderProgram, tempFragShaderObj);

	// Link program
	glLinkProgram(simpleShaderProgram);

	// Use program THIS WILL BE REMOVED FROM HERE LATER ON SINCE IT BELONGS SOMEWHERE ELSE
	glUseProgram(simpleShaderProgram);

	cout << endl <<  "Shaders initialized!";
}

ShaderManager::~ShaderManager(void) {
}

//http://www.cplusplus.com/reference/istream/istream/read/
//Is there a memleak here since buffer isn't deleted?
char*  ShaderManager::getShaderSource(string shaderSource) {
	ifstream is(shaderSource);

	if (is) {
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		char * buffer = new char[length];
		
		is.read(buffer, length);

		if (!is)
			cout << endl << "All characters from " + shaderSource + " read successfully.";
		 else
			cout << endl << "error: only " << is.gcount() << " could be read";
		
		is.close();

		return buffer;
	}
	else {
		cout << endl << "error: in getShaderSource. file: " + shaderSource + " not found! returning null";
		return NULL;
	}
}
