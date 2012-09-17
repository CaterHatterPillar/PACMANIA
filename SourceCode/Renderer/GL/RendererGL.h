#ifndef OPENGL_H
#define OPENGL_H

/*OpenGL*/
#include <Windows.h> //obs, tmep
#include <gl/GL.h>
#include <gl/GLU.h>

#include "../../Common.h"
#include "../Renderer.h"
#include "../GraphicsContainer.h"

#include "../../Singleton.h"
#include "../../Messaging/ObserverDirector.h"
#include "../../Messaging/MsgGlutCallback.h"

class RendererGL : public Renderer
{
private:
protected:
public:
	RendererGL();
	~RendererGL();

	void init()	;
	void update(double delta);

	void cleanUp();
	void renderFrame();

	/*Callback*/
	static void renderSpec();

	/*
	extern void APIENTRY glutDisplayFunc(void (*)(void));
	*/
};

#endif //OPENGL_H