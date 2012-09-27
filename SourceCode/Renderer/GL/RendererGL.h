#ifndef OPENGL_H
#define OPENGL_H

#include "CommonGL.h"
#include "GraphicsContainerGL.h"
#include "FXManagementGL.h"

#include "../Renderer.h"

#include "../../Common.h"
#include "../../Singleton.h"

#include "../../Messaging/ObserverDirector.h"
#include "../../Messaging/MsgGlutCallback.h"
#include "../../Messaging/MsgCamera.h"

#include "../../Math/PacMath.h"

class RendererGL : public Renderer
{
private:
	static FXManagementGL* fxManagement;

	static MatF4 view;
	static MatF4 proj;
	static MatF4 worldViewProj;

	static GLuint viewFX;
	static GLuint projFX;
	static GLuint worldViewProjFX;
protected:
public:
	RendererGL();
	~RendererGL();

	void init()	;

	void update(double delta);
	void msgRender(Msg* msg);
	void msgCamera(Msg* msg);

	void cleanUp();
	void renderFrame();

	static void renderSpec();
	static void renderGraphicsGL(GraphicsContainerGL* containerGL);
	static void setShader();
};

#endif //OPENGL_H