#ifndef GRAPHICSCONTAINER_H
#define GRAPHICSCONTAINER_H

#include "Vertices/PosNormTex.h"

#include <vector>

enum ShaderId
{
	VERTEX_SHADER_DEFAULT,
	PIXEL_SHADER_DEFAULT
};

//Make abstract
class GraphicsContainer
{
private:
protected:
	ShaderId vertexShaderId;
	ShaderId pixelShaderId;

	std::vector<PosNormTex>*	vertices;
	std::vector<unsigned int>*	indices;

	unsigned int numVertices;
	unsigned int numIndices;
	unsigned int numFaces;
	unsigned int stride;
	unsigned int offset;
public:
	GraphicsContainer(
		ShaderId vertexShaderId,
		ShaderId pixelShaderId,

		std::vector<PosNormTex>* vertices,
		std::vector<unsigned int>* indices,
		unsigned int numVertices, 
		unsigned int numIndices
		)
	{
		this->numVertices		= numVertices;
		this->numIndices		= numIndices;
		this->vertexShaderId	= vertexShaderId;
		this->pixelShaderId		= pixelShaderId;
	}
	virtual ~GraphicsContainer() {}
	
	ShaderId getVertexShaderId(){ return vertexShaderId;}
	ShaderId getPixelShaderId(){ return pixelShaderId;}
};

#endif //GRAPHICSCONTAINER_H