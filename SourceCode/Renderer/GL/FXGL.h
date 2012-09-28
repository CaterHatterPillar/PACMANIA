#ifndef FXGL_H
#define FXGL_H

#include "CommonGL.h"
#include "UniformGL.h"
#include "../GraphicsContainer.h"
#include "../../Common.h"

class FXGL
{
private:
	ShaderId vertexShader;
	ShaderId fragmentShader;

	GLuint	programFX;
	std::vector<UniformGL*>* uniforms;
protected:
public:
	void loadUniform(std::string handle, UNIFORM_TYPE type);

	FXGL(
		ShaderId	vertexShader,
		ShaderId	fragmentShader,
		GLuint		programFX);
	~FXGL();

	GLuint	ProgramFX()	{ return programFX;	}

	ShaderId VertexShader()		{ return vertexShader;		}
	ShaderId FragmentShader()	{ return fragmentShader;	}

	std::vector<UniformGL*>* Uniforms() { return uniforms; }
};

#endif //FXGL_H