#ifndef CUBE_H
#define CUBE_H

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include <Windows.h>
#include <WindowsX.h>

#include <vector>

using namespace std;

const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);

struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXCOLOR color;

	Vertex()
	{
		position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		color = WHITE;
	}

	Vertex(D3DXVECTOR3 position, D3DXVECTOR3 normal, D3DXCOLOR color)
	{
		this->position = position;
		this->normal = normal;
		this->color = color;
	}
};

class Cube
{
private:
	ID3D11Device* device;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	D3DXVECTOR3 position;
	D3DXMATRIX world;

	vector<DWORD> indices;
	vector<Vertex> vertices;

	void createVertices();
	void createVertexBuffer();

	void createIndices();
	void createIndexBuffer();

public:
	Cube(ID3D11Device* device);
	~Cube();

	void initialize();

	ID3D11Buffer* getIndexBuffer();
	ID3D11Buffer* getVertexBuffer();
	D3DXMATRIX getWorldMatrix();

	int getNumIndices();
};

#endif 