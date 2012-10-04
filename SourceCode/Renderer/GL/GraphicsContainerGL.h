#ifndef GRAPHICSCONTAINERGL_H
#define GRAPHICSCONTAINERGL_H

#include "CommonGL.h"
#include "../GraphicsContainer.h"

class GraphicsContainerGL : public GraphicsContainer
{
private:
	GLuint vb;
	GLuint ib;

	bool outdatedVB;
	bool outdatedIB;
protected:
public:
	void createVB();
	void createIB();

	GraphicsContainerGL(
		ShaderId vertexShaderId,
		ShaderId pixelShaderId,

		std::vector<PosNormTex>* vertices,
		std::vector<unsigned int>* indices,

		unsigned int numVertices, 
		unsigned int numIndices,
		unsigned int numFaces,
		unsigned int stride,
		unsigned int offset);
	~GraphicsContainerGL();

	bool OutdatedVB() { return outdatedVB; }
	bool OutdatedIB() { return outdatedIB; }
	void OutdatedVB(bool outdatedVB) { this->outdatedVB = outdatedVB; }
	void OutdatedIB(bool outdatedIB) { this->outdatedIB = outdatedIB; }

	GLuint VB() { return vb; }
	GLuint IB() { return ib; }
};

#endif //GRAPHICSCONTAINERGL_H
