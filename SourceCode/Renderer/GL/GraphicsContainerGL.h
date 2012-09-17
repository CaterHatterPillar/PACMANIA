#ifndef GRAPHICSCONTAINERGL_H
#define GRAPHICSCONTAINERGL_H

#include "CommonGL.h"

class GraphicsContainerGL
{
private:
	GLuint vertexBuffer;
	GLuint indexBuffer;
protected:
public:
	GraphicsContainerGL();
	~GraphicsContainerGL();
};

#endif //GRAPHICSCONTAINERGL_H