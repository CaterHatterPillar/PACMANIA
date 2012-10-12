#ifndef GAMEENTITYFACTORY_H
#define GAMEENTITYFACTORY_H

#include <vector>

#include "Game/GameEntity.h"
#include "Renderer/Vertices/PosNormTex.h"

using namespace std;

class GameEntityFactory
{
private:
protected:
	vector<PosNormTex>* createVerticesPlane();
	vector<unsigned int>* createIndicesPlane();

	vector<PosNormTex>* createVerticesCube();
	vector<unsigned int>* createIndicesCube();
public:
	GameEntityFactory();
	~GameEntityFactory();

	virtual GameEntity* createPacman() = 0;
	virtual GameEntity* createGhost() = 0;
	virtual GameEntity* createPill() = 0;
	virtual GameEntity* createBloodyPill() = 0;
};

#endif //GAMEENTITYFACTORY