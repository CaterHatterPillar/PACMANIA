#ifndef GRAPHICSCONTAINER_H
#define GRAPHICSCONTAINER_H

//Make abstract
class GraphicsContainer
{
private:
protected:
	unsigned int noVertices;
	unsigned int noIndices;
public:
	GraphicsContainer(
		unsigned int noVertices,
		unsigned int noIndices)
	{
		this->noVertices = noVertices;
		this->noIndices = noIndices;
	}
	virtual ~GraphicsContainer() {}
};

#endif //GRAPHICSCONTAINER_H