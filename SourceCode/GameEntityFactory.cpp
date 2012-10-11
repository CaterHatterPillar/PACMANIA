#include "GameEntityFactory.h"

GameEntityFactory::GameEntityFactory()
{
}

GameEntityFactory::~GameEntityFactory()
{
}

vector<PosNormTex>* GameEntityFactory::createVerticesPlane()
{
	vector<PosNormTex>* vertices = new vector<PosNormTex>;
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 0.0f)));   
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, 1.0f),		VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 1.0f)));

	return vertices;
}

vector<unsigned int>* GameEntityFactory::createIndicesPlane()
{
	vector<unsigned int>* indices;

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(3);

	return indices;
}