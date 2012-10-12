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

	virtual GameEntity* createPacman(VecF3 position) = 0;
	virtual GameEntity* createGhost(VecF3 position) = 0;
	virtual GameEntity* createPill(VecF3 position) = 0;
	virtual GameEntity* createBloodyPill(VecF3 position) = 0;
};

#endif //GAMEENTITYFACTORY