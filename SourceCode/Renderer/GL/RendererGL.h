#ifndef OPENGL_H
#define OPENGL_H

#include "Common.h"
#include "CommonOpenGL.h"
#include "Camera.h"
#include "math_3d.h"		//courtesy of someone

/*OpenGL Pipeline*/
/*------------------------------------
Vertex Processor	(Vertex Shader)
|
Geometry Processor	(Geometry Shader)
|
Clipper
|
Fragment Processor	(Pixel Shader)
------------------------------------*/

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

class OpenGL
{
private:
	/*Desc*/
	static float screenWidth;
	static float screenHeight;
	static float FOV;
	static float zNear;
	static float zFar;

	/*Buffers*/
	static GLuint vertexBuffer;
	static GLuint indexBuffer;

	/*Shaders*/
	GLuint shaderProgram;
	
	/*Uniform Variables*/
	static Vector3f scaleInfo;
	static Vector3f worldInfo;
	static Vector3f rotateInfo;

	static void setScale(float x, float y, float z);
	static void setRotation(float x, float y, float z);
	static void setWorld(float x, float y, float z);

	static Matrix4f proj;
	static Matrix4f world;
	static Matrix4f scale;
	static Matrix4f rotation;
	static Matrix4f trans;

	static Camera*	camera;
	static Matrix4f	cameraTrans;
	static Matrix4f	cameraRot;

	static GLuint	worldViewProjFX;

	void initializeGLUT(
		int		argc,
		char**	argv);
	void initializeBuffers();
	void initializeVertexBuffer();
	void initializeIndexBuffer();
	void initializeShaders();

	static void updateMatrices();
	static void updateProj();
	static void updateTranslation();
	static void updateScale();
	static void updateRotation();
	static void updateCamera();

	void initializeUniform();

	void addShader(
		GLuint		shaderProgram, 
		const char*	shaderText, 
		GLenum		shaderType);

	static void renderSpec();
	static void specialKeyboardSpec(int key, int x, int y);
	static void keyboardSpec(unsigned char key, int x, int y);
	static void mouseSpec(int x, int y);
protected:
public:
	void initialize(
		int		argc,
		char**	argv);

	OpenGL(
		float screenWidth,
		float screenHeight,
		float FOV,
		float zNear,
		float zFar);
	~OpenGL();
};

#endif //OPENGL_H