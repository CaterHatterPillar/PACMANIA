#include "SimpleGeometry.h"

void SimpleGeometry::init()
{
	/*Init temp buffers*/
	VecF3 vertices[4];
	vertices[0] = VecF3(-10.0f, -10.0f, 0.0f);
	vertices[1] = VecF3(0.0f, -10.0f, 10.0f);
	vertices[2] = VecF3(10.0f, -10.0f, 0.0f);
	vertices[3] = VecF3(0.0f, 10.0f, 0.0f);

	GLuint VB;
	GLuint IB;

	/*Create buffer using glGen-function*/
	glGenBuffers(1, &VB);
	/*Specify usage of buffer*/
	glBindBuffer(GL_ARRAY_BUFFER, VB); //GL_ARRAY_BUFFER specifies that the buffer will contain an array of vertices
	/*Fill buffer with data*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //contents won't be changed, so flag STATIC is specified

	unsigned int indices[] = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 2, 1};

		/*Create buffer using glGen-function*/
		glGenBuffers(1, &IB);
		/*Specify usage of buffer*/
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
		/*Fill buffer with data*/
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	graphicsContainer->vertexBuffer = VB;
	graphicsContainer->indexBuffer = IB;
}
void SimpleGeometry::update(double delta)
{
	/*Simple geometry wishes to be rendered each frame*/
	MsgRender* msgRender = new MsgRender(graphicsContainer);
	Singleton<ObserverDirector>::get().push(msgRender);
}

SimpleGeometry::SimpleGeometry()
{
	graphicsContainer = new GraphicsContainerGL(0, 0);
}
SimpleGeometry::~SimpleGeometry()
{
	if(graphicsContainer)
		delete graphicsContainer;
}