#ifndef GRAPHICSCONTAINERGL_H
#define GRAPHICSCONTAINERGL_H

#include "CommonGL.h"
#include "../GraphicsContainer.h"
#include "Texture.h"

class GraphicsContainerGL : public GraphicsContainer
{
private:
	GLuint vb;
	GLuint ib;
	Texture* tex;

	bool outdatedVB;
	bool outdatedIB;
	bool outdatedTex;
protected:
public:
	void createVB();
	void createIB();
	void createTex(Texture* tex);

	GraphicsContainerGL(
		ShaderId vertexShaderId,
		ShaderId pixelShaderId,

		TextureId textureId,

		std::vector<PosNormTex>* vertices,
		std::vector<unsigned int>* indices,

		unsigned int numVertices, 
		unsigned int numIndices,
		unsigned int numFaces,
		unsigned int stride,
		unsigned int offset);
	~GraphicsContainerGL();

	bool OutdatedVB()	{ return outdatedVB;	}
	bool OutdatedIB()	{ return outdatedIB;	}
	bool OutdatedTex()	{ return outdatedTex;	};
	void OutdatedVB(bool outdatedVB)	{ this->outdatedVB	= outdatedVB;	}
	void OutdatedIB(bool outdatedIB)	{ this->outdatedIB	= outdatedIB;	}
	void OutdatedTex(bool outdatedTex)	{ this->outdatedTex	= outdatedTex;	}

	GLuint		VB()	{ return vb;	}
	GLuint		IB()	{ return ib;	}
	Texture*	Tex()	{ return tex;	}
};

#endif //GRAPHICSCONTAINERGL_H
