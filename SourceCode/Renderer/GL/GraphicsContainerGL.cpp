#include "GraphicsContainerGL.h"

GraphicsContainerGL::GraphicsContainerGL(
	void* verticesRaw,
	void* indicesRaw,

	unsigned int numVertices,
	unsigned int numIndices) : GraphicsContainer(numVertices, numIndices)
{
}
GraphicsContainerGL::~GraphicsContainerGL()
{

}