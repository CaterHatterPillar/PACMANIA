#ifndef GAMEENTITYFACTORYGL_H
#define GAMEENTITYFACTORYGL_H

#include "../GameEntityFactory.h"
#include "GraphicsContainerGL.h"

class GameEntityFactoryGL : public GameEntityFactory
{
private:
protected:
	GraphicsContainer* createGraphicsContainer(
		ShaderId vertexShaderId,
		ShaderId pixelShaderId,
		TextureId textureId,
		std::vector<PosNormTex>* vertices,
		std::vector<unsigned int>* indices,
		unsigned int numVertices, 
		unsigned int numIndices,
		unsigned int numFaces,
		unsigned int stride,
		unsigned int offset)
	{
		return new GraphicsContainerGL(
			vertexShaderId,
			pixelShaderId,
			textureId,
			vertices,
			indices,
			numVertices,
			numIndices,
			numFaces,
			stride,
			offset);
	}
};

#endif