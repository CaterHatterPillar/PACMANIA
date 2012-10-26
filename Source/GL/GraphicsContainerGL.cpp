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
void GraphicsContainerGL::createTex(Texture* tex)
{
	this->tex = tex;
}

GraphicsContainerGL::GraphicsContainerGL(
	ShaderId vertexShaderId,
	ShaderId pixelShaderId,
	TextureId textureId,

	std::vector<PosNormTex>*	vertices,
	std::vector<unsigned int>*	indices,

	unsigned int numVertices, 
	unsigned int numIndices,
	unsigned int numFaces,
	unsigned int stride,
	unsigned int offset) : GraphicsContainer(
		vertexShaderId,
		pixelShaderId,

		textureId,

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