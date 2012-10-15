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

public:
	GameEntityFactory();
	~GameEntityFactory();

	virtual GameEntity* createPacman(VecF3 position)		= 0;
	virtual GameEntity* createGhost(VecF3 position)			= 0;
	virtual GameEntity* createPill(VecF3 position)			= 0;
	virtual GameEntity* createBloodyPill(VecF3 position)	= 0;
	virtual GameEntity* createWall(VecF3 position)			= 0;
};

#endif //GAMEENTITYFACTORY