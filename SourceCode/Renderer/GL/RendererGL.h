#ifndef OPENGL_H
#define OPENGL_H

#include "CommonGL.h"

#include "../../Common.h"
#include "../Renderer.h"
#include "GraphicsContainerGL.h"
#include "FXManagementGL.h"

#include "../../Singleton.h"
#include "../../Messaging/ObserverDirector.h"
#include "../../Messaging/MsgGlutCallback.h"

#include "../../Math/PacMath.h"

class RendererGL : public Renderer
{
private:
	static FXManagementGL* fxManagement;
protected:
public:
	RendererGL();
	~RendererGL();

	void init()	;
	void update(double delta);
	void msgRender(Msg* msg);

	void cleanUp();
	void renderFrame();

	/*Callback*/
	static void renderSpec();
	static void setShader();
};

#endif //OPENGL_H