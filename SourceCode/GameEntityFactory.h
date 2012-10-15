#ifndef GAMEENTITYFACTORY_H
#define GAMEENTITYFACTORY_H

#include "Common.h"

#include "Game/GameEntity.h"

#include "Behaviours/MoveBehaviourPlayer.h"

#include "Vertices/PosNormTex.h"

#include <string>
#include <fstream>

using namespace std;

class GameEntityFactory
{
private:

	vector<VecF3> positions;
	vector<VecF3> normals;
	vector<VecF2> texcoords;

	vector<PosNormTex> privateVertices;

	void parsePosition(fstream& infile);
	void parseNormal(fstream& infile);
	void parseTexcoord(fstream& infile);
	void parseFace(fstream& infile);
protected:
	vector<PosNormTex>* createVerticesPlane();
	vector<unsigned int>* createIndicesPlane();

	vector<PosNormTex>* createVerticesCube();
	vector<unsigned int>* createIndicesCube();

	vector<PosNormTex>* createVerticesObj(string filename);
	vector<unsigned int>* createIndicesObj(vector<PosNormTex>* vertices);


	virtual GraphicsContainer* createGraphicsContainer(ShaderId vertexShaderId,
										 ShaderId pixelShaderId,
										 TextureId textureId,
										 std::vector<PosNormTex>* vertices,
										 std::vector<unsigned int>* indices,
										 unsigned int numVertices, 
										 unsigned int numIndices,
										 unsigned int numFaces,
										 unsigned int stride,
										 unsigned int offset) = 0;

public:
	GameEntityFactory();
	~GameEntityFactory();

	GameEntity* createPacman(VecF3 position, Maze* maze)
	{
		GameEntity* entity = new GameEntity();
		entity->setPosition(position);

		vector<PosNormTex>* vertices	= createVerticesObj("root/Models/Pacman.obj");
		vector<unsigned int>* indices	= createIndicesObj(vertices);

		ShaderId vertexShaderId = VERTEX_SHADER_DEFAULT;
		ShaderId pixelShaderId	= PIXEL_SHADER_DEFAULT;
		TextureId textureId		= TEXTURE_PLACEHOLDER;

		unsigned int numVertices	= vertices->size();
		unsigned int numIndices		= indices->size();
		unsigned int numFaces		= indices->size() / 3;
		unsigned int stride			= sizeof(PosNormTex);
		unsigned int offset			= 0;

		GraphicsContainer* graphicsContainer = createGraphicsContainer(	vertexShaderId,
			pixelShaderId,
			textureId,
			vertices,
			indices,
			numVertices,
			numIndices,
			numFaces,
			stride,
			offset);

		MoveBehaviour* moveBehaviour = new MoveBehaviourPlayer(maze);
		moveBehaviour->init();

		entity->setGraphicsContainer(graphicsContainer);
		entity->setMoveBehaviour(moveBehaviour);

		entity->setRotation(VecF3(0.0f, 0.0f, -90.0f));
		entity->setScale(VecF3(0.5f,0.5f,0.5f));
		return entity;
	}
	virtual GameEntity* createGhost(VecF3 position)			= 0;
	virtual GameEntity* createPill(VecF3 position)			= 0;
	virtual GameEntity* createBloodyPill(VecF3 position)	= 0;
	virtual GameEntity* createWall(VecF3 position)			= 0;
	Maze* createMaze()
	{
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

		GraphicsContainer* graphicsContainer = createGraphicsContainer(	vertexShaderId,
			pixelShaderId,
			textureId,
			vertices,
			indices,
			numVertices,
			numIndices,
			numFaces,
			stride,
			offset);

		Maze* maze = new Maze(graphicsContainer);

		return maze;
	}
};

#endif //GAMEENTITYFACTORY