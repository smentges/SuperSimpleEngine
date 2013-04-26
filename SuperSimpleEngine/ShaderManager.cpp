#include "ShaderManager.h"
#include <iostream>
#include <fstream>

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
	simpleShaderProgram = glCreateProgramObjectARB();

	// Make shaders
	tempVertShaderObj = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	tempFragShaderObj = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	// Load Shader Sources
	glShaderSourceARB(tempVertShaderObj, 1, &simpleShaderVertSource, NULL);
	glShaderSourceARB(tempFragShaderObj, 1, &simpleShaderFragSource, NULL);

	// Compile Shaders
	glCompileShaderARB(tempVertShaderObj);
	glCompileShaderARB(tempFragShaderObj);

	// Attach Shaders
	glAttachObjectARB(simpleShaderProgram, tempVertShaderObj);

	// Use program (anything drawn after this will go through the program) THIS WILL BE REMOVED FROM HERE LATER ON SINCE IT BELONGS SOMEWHERE ELSE
	glUseProgramObjectARB(simpleShaderProgram);

	cout << endl <<  "Shaders initialized!";
}

ShaderManager::~ShaderManager(void)
{
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
