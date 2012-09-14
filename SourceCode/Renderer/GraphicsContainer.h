#ifndef GRAPHICSCONTAINER_H
#define GRAPHICSCONTAINER_H

//make abstract
class GraphicsContainer
{
private:
	unsigned int noVertices;
	unsigned int noIndices;
protected:
public:
	GraphicsContainer(
		unsigned int noVertices,
		unsigned int noIndices);
	~GraphicsContainer();
};

#endif //GRAPHICSCONTAINER_H