#ifndef OPENGL_H
#define OPENGL_H

#include "CommonGL.h"

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
};

#endif //OPENGL_H