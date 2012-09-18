#ifndef FXGL_H
#define FXGL_H

#include "CommonGL.h"

enum ID_FX { BASIC };

class FXGL
{
private:
	ID_FX	idFX;
	GLuint	programFX;
protected:
public:
	GLuint	ProgramFX()	{ return programFX;	}
	ID_FX	IDFX()		{ return idFX;		}

	FXGL(ID_FX idFX, GLuint programFX);
	~FXGL();
};

#endif //FXGL_H