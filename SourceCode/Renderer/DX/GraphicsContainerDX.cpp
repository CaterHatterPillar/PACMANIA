#include "GraphicsContainerDX.h"

GraphicsContainerDX::GraphicsContainerDX(ShaderId vertexShaderId,
										 ShaderId pixelShaderId,
										 std::vector<PosNormTex>* vertices,
										 std::vector<unsigned int>* indices,
										 unsigned int numVertices, 
										 unsigned int numIndices) : GraphicsContainer(vertexShaderId, pixelShaderId,
																					  vertices, indices,
																					  numVertices, numIndices)
{

}

GraphicsContainerDX::~GraphicsContainerDX()
{

}