#ifndef GRAPHICSCONTAINER_H
#define GRAPHICSCONTAINER_H

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
	unsigned int numVertices;
	unsigned int numIndices;
	ShaderId vertexShaderId;
	ShaderId pixelShaderId;
public:
	GraphicsContainer()
	{
		numVertices = 0;
		numIndices	= 0;
	}
	GraphicsContainer(unsigned int numVertices, unsigned int numIndices)
	{
		this->numVertices = numVertices;
		this->numIndices = numIndices;
	}
	virtual ~GraphicsContainer() {}
	
	ShaderId getVertexShaderId(){ return vertexShaderId;}
	ShaderId getPixelShaderId(){ return pixelShaderId;}
};

#endif //GRAPHICSCONTAINER_H