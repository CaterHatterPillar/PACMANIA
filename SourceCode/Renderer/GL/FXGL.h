#ifndef FXGL_H
#define FXGL_H

#include "../../Common.h"
#include "CommonGL.h"
#include "UniformGL.h"

enum ID_FX { BASIC };

class FXGL
{
private:
	ID_FX	idFX;
	GLuint	programFX;
	std::vector<UniformGL*>* uniforms;
protected:
public:
	void loadUniform(std::string handle, UNIFORM_TYPE type);

	FXGL(ID_FX idFX, GLuint programFX);
	~FXGL();

	GLuint	ProgramFX()	{ return programFX;	}
	ID_FX	IDFX()		{ return idFX;		}
	std::vector<UniformGL*>* Uniforms() { return uniforms; }
};

#endif //FXGL_H