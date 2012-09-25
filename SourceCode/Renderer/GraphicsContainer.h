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
	Shader vertexShaderId;
	Shader pixelShaderId;
public:
	GraphicsContainer(unsigned int numVertices, unsigned int numIndices)
	{
		this->numVertices = numVertices;
		this->numIndices = numIndices;
	}
	virtual ~GraphicsContainer() {}
	
	Shader getVertexShaderId(){ return vertexShaderId;}
	Shader getPixelShaderId(){ return pixelShaderId;}
};

#endif //GRAPHICSCONTAINER_H