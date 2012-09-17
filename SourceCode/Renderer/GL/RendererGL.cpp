#include "RendererGL.h"

RendererGL::RendererGL() : Renderer()
{

}
RendererGL::~RendererGL()
{

}
void RendererGL::cleanUp()
{

}

void RendererGL::init()
{
	/*Send initial callback-specs to GLUT*/
	MsgGlutCallback* callbackMsg = new MsgGlutCallback(renderSpec);
	Singleton<ObserverDirector>::get().push(callbackMsg);
}
void RendererGL::update(double delta)
{

}
void RendererGL::renderFrame()
{

}

/*GLUT callbacks*/
void RendererGL::renderSpec()
{
	/*Clear backbuffer*/
	glClear(GL_COLOR_BUFFER_BIT);
}