#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;

class ShaderManager
{
private:
	char* simpleShaderVertSource;
	char* simpleShaderFragSource;
public:
	static ShaderManager& getInstance()
	{
		static ShaderManager instance; // Guaranteed to be destroyed.
								// Instantiated on first use.
		return instance;
	}
	ShaderManager(void);
	char* getShaderSource(string shaderSource);
	~ShaderManager(void);
	GLuint simpleShaderProgram;
	void InitShaders();
};

