#include "GraphicsContainerGL.h"

void GraphicsContainerGL::createVB()
{
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(PosNormTex) * vertices->size(),
		&(vertices->at(0)), 
		GL_STATIC_DRAW);

	/*
	VecF3 vertices[4];
	vertices[0] = VecF3(-1.0f, -1.0f, 0.0f);
	vertices[1] = VecF3(0.0f, -1.0f, 1.0f);
	vertices[2] = VecF3(1.0f, -1.0f, 0.0f);
	vertices[3] = VecF3(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	*/
}
void GraphicsContainerGL::createIB()
{
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, 
		sizeof(unsigned int) * indices->size(), 
		&(indices->at(0)), 
		GL_STATIC_DRAW);

	/*
	unsigned int indices[] = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 2, 1};

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	*/
}

GraphicsContainerGL::GraphicsContainerGL(
	ShaderId vertexShaderId,
	ShaderId pixelShaderId,

	std::vector<PosNormTex>*	vertices,
	std::vector<unsigned int>*	indices,

	unsigned int numVertices, 
	unsigned int numIndices,
	unsigned int numFaces,
	unsigned int stride,
	unsigned int offset) : GraphicsContainer(
		vertexShaderId,
		pixelShaderId,

		vertices,
		indices,

		numVertices, 
		numIndices,
		numFaces,
		stride,
		offset)
{
	outdatedVB = true;
	outdatedIB = true;
}
GraphicsContainerGL::~GraphicsContainerGL()
{
	if(vertices)
		delete vertices;
	if(indices)
		delete indices;
}