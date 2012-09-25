#ifndef GRAPHICSCONTAINERGL_H
#define GRAPHICSCONTAINERGL_H

#include "CommonGL.h"
#include "../GraphicsContainer.h"
#include "../../VarStatus.h"

class GraphicsContainerGL : public GraphicsContainer
{
private:
	GLuint vertexBuffer;
	GLuint indexBuffer;

	bool outdatedVB;
	bool outdatedIB;

	void* verticesRaw;
	void* indicesRaw;
protected:
public:
	GraphicsContainerGL(
		unsigned int noVertices,
		unsigned int noIndices);
	~GraphicsContainerGL();

	GLuint VertexBuffer()	{ return vertexBuffer;	}
	GLuint IndexBuffer()	{ return indexBuffer;	}
	bool OutdatedVB() { return outdatedVB; }
	bool OutdatedIB() { return outdatedIB; }
};

#endif //GRAPHICSCONTAINERGL_H