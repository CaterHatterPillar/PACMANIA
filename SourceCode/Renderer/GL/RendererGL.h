#ifndef OPENGL_H
#define OPENGL_H

#ifndef WINDOWS

#include "../../Common.h"
#include "../Renderer.h"
#include "../GraphicsContainer.h"

class RendererGL : public Renderer
{
private:
protected:
public:
	RendererGL();
	~RendererGL();

	void init()	;
	void update(double delta);

	/*Callback*/
	static void renderSpec();

	/*
	extern void APIENTRY glutDisplayFunc(void (*)(void));
	*/
};

#endif //WINDOWS

#endif //OPENGL_H