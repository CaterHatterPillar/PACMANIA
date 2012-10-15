#include "GameEntityFactoryDX.h"

GameEntityFactoryDX::GameEntityFactoryDX()
{
}

GameEntityFactoryDX::~GameEntityFactoryDX()
{
}

GameEntity* GameEntityFactoryDX::createPacman(VecF3 position)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);

	vector<PosNormTex>* vertices	= createVerticesCube();
	vector<unsigned int>* indices	= createIndicesCube();

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_PACMAN;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = new GraphicsContainerDX(	vertexShaderId,
																	pixelShaderId,
																	textureId,
																	vertices,
																	indices,
																	numVertices,
																	numIndices,
																	numFaces,
																	stride,
																	offset);

	MoveBehaviour* moveBehaviour = new MoveBehaviourPlayer();
	moveBehaviour->init();

	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(moveBehaviour);

	return entity;
}

GameEntity* GameEntityFactoryDX::createGhost(VecF3 positoin)
{
	return NULL;
}

GameEntity* GameEntityFactoryDX::createPill(VecF3 position)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);

	vector<PosNormTex>* vertices	= createVerticesCube();
	vector<unsigned int>* indices	= createIndicesCube();

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_PILL;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = new GraphicsContainerDX(	vertexShaderId,
																	pixelShaderId,
																	textureId,
																	vertices,
																	indices,
																	numVertices,
																	numIndices,
																	numFaces,
																	stride,
																	offset);

	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(NULL);

	return entity;
}

GameEntity* GameEntityFactoryDX::createBloodyPill(VecF3 position)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);

	vector<PosNormTex>* vertices	= createVerticesCube();
	vector<unsigned int>* indices	= createIndicesCube();

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_PILL_BLOODY;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = new GraphicsContainerDX(	vertexShaderId,
																	pixelShaderId,
																	textureId,
																	vertices,
																	indices,
																	numVertices,
																	numIndices,
																	numFaces,
																	stride,
																	offset);

	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(NULL);

	return entity;
}

GameEntity* GameEntityFactoryDX::createWall(VecF3 position)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);

	vector<PosNormTex>* vertices	= createVerticesCube();
	vector<unsigned int>* indices	= createIndicesCube();

	ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
	ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
	TextureId textureId		= TEXTURE_WALL;

	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= indices->size() / 3;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = new GraphicsContainerDX(	vertexShaderId,
																	pixelShaderId,
																	textureId,
																	vertices,
																	indices,
																	numVertices,
																	numIndices,
																	numFaces,
																	stride,
																	offset);

	entity->setGraphicsContainer(graphicsContainer);
	entity->setMoveBehaviour(NULL);

	return entity;
}