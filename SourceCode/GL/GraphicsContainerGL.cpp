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
void GraphicsContainerGL::createTex(std::string pathTex)
{
	bool textureLoaded = LoadTGA(&tex, pathTex.c_str());
	if(textureLoaded)
	{
		//Creates a texture and put it's ID in the given integer variable
		glGenTextures(1, &tex.texID);
	}
	else
		throw 0;
}

GraphicsContainerGL::GraphicsContainerGL(
	ShaderId vertexShaderId,
	ShaderId pixelShaderId,
	TextureId texture,

	std::vector<PosNormTex>*	vertices,
	std::vector<unsigned int>*	indices,

	unsigned int numVertices, 
	unsigned int numIndices,
	unsigned int numFaces,
	unsigned int stride,
	unsigned int offset) : GraphicsContainer(
		vertexShaderId,
		pixelShaderId,

		texture,

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
	if(tex.imageData)
		free(tex.imageData); //Free raw image data

	DELETE_NULL(vertices);
	DELETE_NULL(indices);
}