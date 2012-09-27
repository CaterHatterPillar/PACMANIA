#include "SimpleGeometry.h"

void SimpleGeometry::init()
{
	/*
	std::vector<PosNormTex>* vertices = new std::vector<PosNormTex>();
	
	PosNormTex vertex;
	vertex.pos = VecF3(-1.0f, -1.0f, 0.0f);
	vertices->push_back(vertex);

	vertex.pos = VecF3(0.0f, -10.0f, 10.0f);
	vertices->push_back(vertex);

	vertex.pos = VecF3(10.0f, -10.0f, 0.0f);
	vertices->push_back(vertex);

	vertex.pos = VecF3(0.0f, 10.0f, 0.0f);
	vertices->push_back(vertex);

	std::vector<unsigned int>* indices = new std::vector<unsigned int>();
	indices->push_back(0);
	indices->push_back(3);
	indices->push_back(1);
	
	indices->push_back(1);
	indices->push_back(3);
	indices->push_back(2);

	indices->push_back(2);
	indices->push_back(3);
	indices->push_back(0);

	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(1);

	unsigned int numVertices = 4;
	unsigned int numIndices = 12;
	unsigned int numFaces = 4;

	unsigned int stride = sizeof(PosNormTex);
	unsigned int offset = 0;
	*/

	unsigned int numVertices = 4;
	unsigned int numIndices = 12;
	unsigned int numFaces = 4;
	unsigned int stride = 0;
	unsigned int offset = 0;

	graphicsContainer = new GraphicsContainerGL(
		VERTEX_SHADER_DEFAULT,
		PIXEL_SHADER_DEFAULT,
		nullptr, //vertices,
		nullptr, //indices,
		numVertices,
		numIndices,
		numFaces,
		stride,
		offset);
}
void SimpleGeometry::update(double delta)
{
	/*Simple geometry wishes to be rendered each frame*/
	MsgRender* msgRender = new MsgRender(graphicsContainer);
	Singleton<ObserverDirector>::get().push(msgRender);
}

SimpleGeometry::SimpleGeometry()
{
	graphicsContainer = nullptr;
}
SimpleGeometry::~SimpleGeometry()
{
	if(graphicsContainer)
		delete graphicsContainer;
}