#include "RendererGL.h"

GLuint RendererGL::tempVB;
GLuint RendererGL::tempIB;

RendererGL::RendererGL() : Renderer()
{
	fxManagement = new FXManagementGL();
}
RendererGL::~RendererGL()
{
	if(fxManagement)
		delete fxManagement;
}
void RendererGL::cleanUp()
{

}

void RendererGL::init()
{
	/*Send initial callback-specs to GLUT*/
	MsgGlutCallback* callbackMsg = new MsgGlutCallback(renderSpec);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	/*Initialize shaders*/
	fxManagement->init();

	/*Init temp buffers*/
	VecF3 vertices[4];
	vertices[0] = VecF3(-1.0f, -1.0f, 0.0f);
	vertices[1] = VecF3(0.0f, -1.0f, 1.0f);
	vertices[2] = VecF3(1.0f, -1.0f, 0.0f);
	vertices[3] = VecF3(0.0f, 1.0f, 0.0f);

	/*Create buffer using glGen-function*/
	glGenBuffers(1, &tempVB);
	/*Specify usage of buffer*/
	glBindBuffer(GL_ARRAY_BUFFER, tempVB); //GL_ARRAY_BUFFER specifies that the buffer will contain an array of vertices
	/*Fill buffer with data*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //contents won't be changed, so flag STATIC is specified

	unsigned int indices[] = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 2, 1};

	/*Create buffer using glGen-function*/
	glGenBuffers(1, &tempIB);
	/*Specify usage of buffer*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempIB);
	/*Fill buffer with data*/
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, tempVB);
	glVertexAttribPointer(
		0,			//Index of attribute
		3,			//Number of components in attribute (x, y, z)
		GL_FLOAT,	//Data type of each component
		GL_FALSE,	//Specifies if we want attribute to be normalized
		0,			//Stride
		0);			//Offset
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempIB);
	glDrawElements(
		GL_TRIANGLES,		//Type to render
		12,					//Number of indices
		GL_UNSIGNED_INT,	//Index-type (for size)
		0);					//Offset
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}