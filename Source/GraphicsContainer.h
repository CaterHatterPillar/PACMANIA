#ifndef GRAPHICSCONTAINER_H
#define GRAPHICSCONTAINER_H

#include "Common.h"
#include "TextureId.h"
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

	TextureId textureId;

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
		TextureId textureId,

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

		this->textureId = textureId;

		this->vertices	= vertices;
		this->indices	= indices;

		this->numVertices	= numVertices;
		this->numIndices	= numIndices;
		this->numFaces		= numFaces;
		this->stride		= stride;
		this->offset		= offset;
	}
	virtual ~GraphicsContainer() {}
	
	ShaderId getVertexShaderId()	{ return vertexShaderId;	}
	ShaderId getPixelShaderId()		{ return pixelShaderId;		}

	TextureId getTextureId()		{ return textureId; }

	unsigned int getNumVertices()	{ return numVertices;	}
	unsigned int getNumIndices()	{ return numIndices;	}
	unsigned int getNumFaces()		{ return numFaces;		}
	unsigned int getStride()		{ return stride;		}
	unsigned int getOffset()		{ return offset;		}
};

#endif //GRAPHICSCONTAINER_H