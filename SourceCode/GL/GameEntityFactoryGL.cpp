#include "GameEntityFactoryGL.h"

GameEntity* GameEntityFactoryGL::createPacman(VecF3 position)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);
	
	std::vector<PosNormTex>*	vertices	= createVerticesCube();
	std::vector<unsigned int>*	indices		= createIndicesCube();

	ShaderId vsID	= VERTEX_SHADER_DEFAULT;
	ShaderId fsID	= PIXEL_SHADER_DEFAULT;
	TextureId texID	= TEXTURE_PLACEHOLDER;
	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= 12;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = new GraphicsContainerGL( 
		vsID, 
		fsID, 
		texID,
		vertices, 
		indices, 
		numVertices, 
		numIndices, 
		numFaces, 
		stride, 
		offset);
	entity->setGraphicsContainer(graphicsContainer);

	MoveBehaviour* moveBehaviour = new MoveBehaviourPlayer();
	moveBehaviour->init();
	entity->setMoveBehaviour(moveBehaviour);

	return entity;
}
GameEntity* GameEntityFactoryGL::createGhost(VecF3 position)
{
	return NULL;
}
GameEntity* GameEntityFactoryGL::createPill(VecF3 position)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);
	
	std::vector<PosNormTex>*	vertices	= createVerticesCube();
	std::vector<unsigned int>*	indices		= createIndicesCube();

	ShaderId vsID	= VERTEX_SHADER_DEFAULT;
	ShaderId fsID	= PIXEL_SHADER_DEFAULT;
	TextureId texID	= TEXTURE_PILL;
	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= 12;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = new GraphicsContainerGL( 
		vsID, 
		fsID, 
		texID,
		vertices, 
		indices, 
		numVertices, 
		numIndices, 
		numFaces, 
		stride, 
		offset);
	entity->setGraphicsContainer(graphicsContainer);

	return entity;
}
GameEntity* GameEntityFactoryGL::createBloodyPill(VecF3 position)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);
	
	std::vector<PosNormTex>*	vertices	= createVerticesCube();
	std::vector<unsigned int>*	indices		= createIndicesCube();

	ShaderId vsID	= VERTEX_SHADER_DEFAULT;
	ShaderId fsID	= PIXEL_SHADER_DEFAULT;
	TextureId texID	= TEXTURE_PILL_BLOODY;
	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= 12;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = new GraphicsContainerGL( 
		vsID, 
		fsID, 
		texID,
		vertices, 
		indices, 
		numVertices, 
		numIndices, 
		numFaces, 
		stride, 
		offset);
	entity->setGraphicsContainer(graphicsContainer);

	return entity;
}
GameEntity* GameEntityFactoryGL::createWall(VecF3 position)
{
	GameEntity* entity = new GameEntity();
	entity->setPosition(position);
	
	std::vector<PosNormTex>*	vertices	= createVerticesCube();
	std::vector<unsigned int>*	indices		= createIndicesCube();

	ShaderId vsID	= VERTEX_SHADER_DEFAULT;
	ShaderId fsID	= PIXEL_SHADER_DEFAULT;
	TextureId texID	= TEXTURE_WALL;
	unsigned int numVertices	= vertices->size();
	unsigned int numIndices		= indices->size();
	unsigned int numFaces		= 12;
	unsigned int stride			= sizeof(PosNormTex);
	unsigned int offset			= 0;

	GraphicsContainer* graphicsContainer = new GraphicsContainerGL( 
		vsID, 
		fsID, 
		texID,
		vertices, 
		indices, 
		numVertices, 
		numIndices, 
		numFaces, 
		stride, 
		offset);
	entity->setGraphicsContainer(graphicsContainer);

	return entity;
}

GameEntityFactoryGL::GameEntityFactoryGL() : GameEntityFactory()
{
}
GameEntityFactoryGL::~GameEntityFactoryGL()
{
}