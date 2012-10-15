#ifndef GAMEENTITYFACTORYDX_H
#define GAMEENTITYFACTORYDX_H

#include "../GameEntityFactory.h"
#include "GraphicsContainerDX.h"

class GameEntityFactoryDX : public GameEntityFactory
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
		return new GraphicsContainerDX(	vertexShaderId,
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
	GameEntityFactoryDX();
	~GameEntityFactoryDX();

	virtual GameEntity* createGhost(VecF3 position);
	virtual GameEntity* createPill(VecF3 position);
	virtual GameEntity* createBloodyPill(VecF3 position);
	virtual GameEntity* createWall(VecF3 position);

};

#endif