#ifndef OPENGL_H
#define OPENGL_H

#include "CommonGL.h"
#include "GraphicsContainerGL.h"
//#include "FXManagementGL.h"

#include "../Renderer.h"

#include "../../Common.h"
#include "../../Singleton.h"

#include "../../Messaging/ObserverDirector.h"
#include "../../Messaging/MsgGlutCallback.h"
#include "../../Messaging/MsgCamera.h"

#include "../../Math/PacMath.h"

/*Vertex Shader*/
static const char* VS = "							\n\
						#version 330										\n\
						\n\
						layout (location = 0) in vec3 Position;				\n\
						\n\
						uniform mat4 wvp;									\n\
						\n\
						out vec4 Color;										\n\
						\n\
						void main()											\n\
						{													\n\
						gl_Position = wvp * vec4(Position, 1.0f);		\n\
						Color = vec4(clamp(Position, 0.0, 1.0), 1.0);	\n\
						}";

/*
#version 330							- OpenGL target
layout (location = 0) in vec3 Position;	- Similar to DX-semantics. 'At locality 0 in the buffer is a 3D vector, this will hence be referred to as 'Position''
void main()								- One main()-func for each Shader-stage
gl_position								- Built in variable that ought to contain homogeneous vertex position
*/

/*Pixel Shader*/
static const char* PS = "						\n\
						#version 330									\n\
						\n\
						in vec4 Color;									\n\
						\n\
						out vec4 fragColor;								\n\
						\n\
						void main()										\n\
						{												\n\
						fragColor = Color;							\n\
						}";

class RendererGL : public Renderer
{
private:
	//static FXManagementGL* fxManagement;

	/*Buffers*/
	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint shaderProgram;
	static GLuint worldViewProjFX;

	static MatF4 view;
	static MatF4 proj;

	static MatF4 trans;
protected:
public:
	RendererGL();
	~RendererGL();

	void init()	;
	void initShaders();
	void update(double delta);
	void msgRender(Msg* msg);
	void msgCamera(Msg* msg);

	void cleanUp();
	void renderFrame();

	/*Callback*/
	static void renderSpec();
	//static void setShader();

	//temp
	void addShader(
		GLuint		shaderProgram, 
		const char*	shaderText, 
		GLenum		shaderType);
};


#endif //OPENGL_H