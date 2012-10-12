#ifndef OPENGL_H
#define OPENGL_H

#include "CommonGL.h"
#include "GraphicsContainerGL.h"
#include "FXManagementGL.h"
#include "Texture.h"

#include "../Renderer.h"

#include "../Common.h"
#include "../Singleton.h"

#include "../Messaging/ObserverDirector.h"
#include "../Messaging/MsgGlutCallback.h"
#include "../Messaging/MsgCamera.h"

#include "../Math/PacMath.h"

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

	static GLuint sampler;
protected:
public:
	RendererGL();
	~RendererGL();

	void init();
	void initShaders();
	bool loadTGATexture(const char* szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);

	void update(double delta);
	void msgRender(Msg* msg);
	void msgCamera(Msg* msg);

	void cleanUp();
	void renderFrame();

	static void renderSpec();
	static void prepareRender();
	static void renderGraphicsGL(GraphicsContainerGL* containerGL);
	static void setShader(ShaderId vertexShader, ShaderId fragmentShader, GraphicsContainerGL* containerGL);
	static void setBuffers(GLuint vb, GLuint ib);
	static void setTextures(Texture& tex);
	static void deBindGraphicsGL();

	static std::string fetchTexPath(TextureId texId);
};

#endif //OPENGL_H