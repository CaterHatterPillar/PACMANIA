#ifndef GRAPHICSCONTAINER_H
#define GRAPHICSCONTAINER_H

//Make abstract
class GraphicsContainer
{
private:
protected:
	unsigned int numVertices;
	unsigned int numIndices;
public:
	GraphicsContainer(unsigned int numVertices, unsigned int numIndices)
	{
		this->numVertices = numVertices;
		this->numIndices = numIndices;
	}
	virtual ~GraphicsContainer() {}
};

#endif //GRAPHICSCONTAINER_H