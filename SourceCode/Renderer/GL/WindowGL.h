#ifndef WINDOWGL_H
#define WINDOWGL_H

#ifndef WINDOWS

#include "../../Common.h"

#include "../Window.h"

#include <Windows.h>

/*OpenGL Utility*/
#include <glew.h>
#include <glut.h>

/*OpenGL*/
#include <gl/GL.h>
#include <gl/GLU.h>

class WindowGL : public Window
{
private:
	int		argc;
	char**	argv;
public:
	WindowGL(int argc, char** argv);
	~WindowGL();

	virtual void init();
	virtual void update(double delta);
};

#endif //WINDOWS

#endif //WINDOWGL_H