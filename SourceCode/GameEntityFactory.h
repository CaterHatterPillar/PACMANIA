#ifndef GAMEENTITYFACTORY_H
#define GAMEENTITYFACTORY_H

#include <vector>

#include "GameEntity.h"
#include "Renderer/Vertices/PosNormTex.h"

using namespace std;

class GameEntityFactory
{
private:
protected:
	vector<PosNormTex>* createVerticesPlane();
	vector<unsigned int>* createIndicesPlane();
public:
	GameEntityFactory();
	~GameEntityFactory();

	virtual GameEntity* createPacman();
	virtual GameEntity* createGhost();
	virtual GameEntity* createPill();
	virtual GameEntity* createBloodyPill();
};

#endif //GAMEENTITYFACTORY