#include "FXGL.h"

void FXGL::loadUniform(
	std::string		handle, 
	UNIFORM_TYPE	type)
{
	if(programFX)
	{
		GLuint uniform = glGetUniformLocation(programFX, "transform");//handle);
		assert(uniform != 0xFFFFFFFF);

		UniformGL* uniformGL = new UniformGL(uniform, type);
		uniforms->push_back(uniformGL);
	}
	else
		throw 0; //fix
}

FXGL::FXGL(
	ShaderId	vertexShader,
	ShaderId	fragmentShader,
	GLuint		programFX)
{
	this->vertexShader		= vertexShader;
	this->fragmentShader	= fragmentShader;

	this->programFX	= programFX;

	uniforms = new std::vector<UniformGL*>();
}
FXGL::~FXGL()
{
	if(uniforms)
	{
		for(unsigned int i = 0; i < uniforms->size(); i++)
			if(uniforms->at(i))
				delete uniforms->at(i);
		delete uniforms;
	}
}