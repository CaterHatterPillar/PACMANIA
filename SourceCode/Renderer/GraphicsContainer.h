#ifndef GRAPHICSCONTAINER_H
#define GRAPHICSCONTAINER_H

#include "../Common.h"
#include "Vertices/PosNormTex.h"

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

	MatF4 worldMatrix;
public:
	GraphicsContainer(
		ShaderId vertexShaderId,
		ShaderId pixelShaderId,

		std::vector<PosNormTex>* vertices,
		std::vector<unsigned int>* indices,

		unsigned int numVertices, 
		unsigned int numIndices,
		unsigned int numFaces,
		unsigned int stride,
		unsigned int offset
		)
	{
		this->vertexShaderId	= vertexShaderId;
		this->pixelShaderId		= pixelShaderId;

		this->vertices	= vertices;
		this->indices	= indices;

		this->numVertices	= numVertices;
		this->numIndices	= numIndices;
		this->numFaces		= numFaces;
		this->stride		= stride;
		this->offset		= offset;

		worldMatrix.identity();
	}
	virtual ~GraphicsContainer() {}
	
	ShaderId getVertexShaderId()	{ return vertexShaderId;	}
	ShaderId getPixelShaderId()		{ return pixelShaderId;		}

	unsigned int getNumVertices()	{ return numVertices;	}
	unsigned int getNumIndices()	{ return numIndices;	}
	unsigned int getNumFaces()		{ return numFaces;		}
	unsigned int getStride()		{ return stride;		}
	unsigned int getOffset()		{ return offset;		}

	MatF4 getWorldMatrix() { return worldMatrix; }
	void setWorldMatrix(MatF4 worldMatrix) { this->worldMatrix = worldMatrix; }
};

#endif //GRAPHICSCONTAINER_H