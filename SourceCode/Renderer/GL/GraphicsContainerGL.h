#ifndef GRAPHICSCONTAINERGL_H
#define GRAPHICSCONTAINERGL_H

#include "CommonGL.h"
#include "../GraphicsContainer.h"

class GraphicsContainerGL : public GraphicsContainer
{
private:
protected:
public:
	GLuint vertexBuffer;
	GLuint indexBuffer;

	GraphicsContainerGL(unsigned int noVertices, unsigned int noIndices);
	~GraphicsContainerGL();
};

#endif //GRAPHICSCONTAINERGL_H