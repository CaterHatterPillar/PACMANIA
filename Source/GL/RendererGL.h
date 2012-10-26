#ifndef OPENGL_H
#define OPENGL_H

#include "CommonGL.h"
#include "GraphicsContainerGL.h"
#include "FXManagementGL.h"
#include "TexManagementGL.h"
#include "Texture.h"

#include "../Renderer.h"

#include "../Common.h"
#include "../Singleton.h"

#include "../Messaging/ObserverDirector.h"
#include "../Messaging/MsgGlutCallback.h"
#include "../Messaging/MsgCamera.h"
#include "../Messaging/MsgLight.h"

#include "../Math/PacMath.h"

#include "../Light.h"

class RendererGL : public Renderer
{
private:
	static FXManagementGL*	fxManagement;
	static TexManagementGL*	texManagement;

	static MatF4 view;
	static MatF4 proj;
	static MatF4 worldViewProj;
	VecF3	camPos;

	static GLuint worldFX;
	static GLuint worldViewProjFX;

	static GLuint sampler;

	static GraphicsContainerGL* prevGC;

	/*Lighting*/
	unsigned int curLight;
	static Light lights[10];
protected:
public:
	RendererGL();
	virtual ~RendererGL();

	void init();
	void initFX();

	void update(double delta);
	void msgRender(Msg* msg);
	void msgCamera(Msg* msg);
	void msgLight(Msg* msg);

	void cleanUp();
	void renderFrame();

	static void renderSpec();
	static void prepareRender();
	static void renderGraphicsGL(
		GraphicsContainerGL* containerGL,
		MatF4 translation,
		MatF4 rotation,
		MatF4 scaling);

	static void setUniform(
		MatF4 translation,
		MatF4 rotation,
		MatF4 scaling);
	static void setBuffers(GraphicsContainerGL* containerGL);
	static void setTextures(GraphicsContainerGL* containerGL);
	static void deBindGraphicsGL();

	
};

#endif //OPENGL_H