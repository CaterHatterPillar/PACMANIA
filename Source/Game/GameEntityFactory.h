#ifndef GAMEENTITYFACTORY_H
#define GAMEENTITYFACTORY_H

#include "../Common.h"

#include "GameEntity.h"
#include "../Behaviours/MoveBehaviourMazePlayer.h"
#include "../Vertices/PosNormTex.h"

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


	virtual GraphicsContainer* createGraphicsContainer(
		ShaderId vertexShaderId,
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

	GameEntity* createPacman(VecF3 position, Maze* maze);
	GameEntity* createGhost(VecI2 position, Maze* maze);
	GameEntity* createPill(VecF3 position);
	GameEntity* createBloodyPill(VecF3 position);
	GameEntity* createWall(VecF3 position);
	Maze* createMaze();
};

#endif //GAMEENTITYFACTORY