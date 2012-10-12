#ifndef GRAPHICSCONTAINER_H
#define GRAPHICSCONTAINER_H

#include "Common.h"
#include "Vertices/PosNormTex.h"

enum ShaderId
{
	VERTEX_SHADER_DEFAULT,
	PIXEL_SHADER_DEFAULT
};

enum TextureId
{
	TEXTURE_PACMAN,
	TEXTURE_PILL,
	TEXTURE_PILL_BLOODY,
	TEXTURE_GHOST
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

	MatF4 translationMatrix;
	MatF4 rotationMatrix;
	MatF4 scalingMatrix;
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

		translationMatrix.identity();
		rotationMatrix.identity();
		scalingMatrix.identity();
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

	MatF4 getTranslationMatrix() { return translationMatrix; }
	MatF4 getRotationMatrix() { return rotationMatrix; }
	MatF4 getScalingMatrix() { return scalingMatrix; } 
	void setTranslationMatrix(MatF4 translationMatrix) { this->translationMatrix = translationMatrix; }
	void setRotationMatrix(MatF4 rotationMatrix) { this->rotationMatrix = rotationMatrix; }
	void setScalingMatrix(MatF4 scalingMatrix) { this->scalingMatrix = scalingMatrix; }
	void setMatrices( MatF4 translationMatrix, MatF4 rotationMatrix, MatF4 scalingMatrix)
	{
		this->translationMatrix = translationMatrix;
		this->rotationMatrix = rotationMatrix;
		this->scalingMatrix = scalingMatrix;
	}
};

#endif //GRAPHICSCONTAINER_H