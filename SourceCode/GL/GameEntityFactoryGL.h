#ifndef GAMEENTITYFACTORYGL_H
#define GAMEENTITYFACTORYGL_H

#include "GraphicsContainerGL.h"
#include "../GameEntityFactory.h"

class GameEntityFactoryGL : public GameEntityFactory
{
private:
protected:
	GraphicsContainer* createGraphicsContainer(ShaderId vertexShaderId,
										 ShaderId pixelShaderId,
										 TextureId textureId,
										 std::vector<PosNormTex>* vertices,
										 std::vector<unsigned int>* indices,
										 unsigned int numVertices, 
										 unsigned int numIndices,
										 unsigned int numFaces,
										 unsigned int stride,
										 unsigned int offset)
	{
		return new GraphicsContainerGL(	vertexShaderId,
			pixelShaderId,
			textureId,
			vertices,
			indices,
			numVertices,
			numIndices,
			numFaces,
			stride,
			offset);
	}
public:
	GameEntity* createGhost(VecF3 position);
	GameEntity* createPill(VecF3 position);
	GameEntity* createBloodyPill(VecF3 position);
	GameEntity* createWall(VecF3 position);

	GameEntityFactoryGL();
	virtual ~GameEntityFactoryGL();
};

#endif //GAMEENTITYFACTORYGL_H