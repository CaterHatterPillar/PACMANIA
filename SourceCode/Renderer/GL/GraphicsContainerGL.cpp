#include "GraphicsContainerGL.h"

void GraphicsContainerGL::createVB()
{
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, ib);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(PosNormTex) * vertices->size(),
		&(vertices->at(0)), 
		GL_STATIC_DRAW);
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

}