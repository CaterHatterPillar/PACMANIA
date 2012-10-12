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
		//Setting as active texture
		glBindTexture(GL_TEXTURE_2D, texture.texID);

		//Load texture into memory
		glTexImage2D(
			GL_TEXTURE_2D, 
			0, 
			tex.bpp / 8, 
			tex.width, 
			tex.height, 
			0, 
			tex.type, 
			GL_UNSIGNED_BYTE, 
			tex.imageData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);

		if(tex.imageData)
			free(tex.imageData); //Free raw image data
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
	DELETE_NULL(vertices);
	DELETE_NULL(indices);
}