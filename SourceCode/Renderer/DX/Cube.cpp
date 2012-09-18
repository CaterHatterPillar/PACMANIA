#include "Cube.h"


Cube::Cube(ID3D11Device* device)
{
	this->device = device;
}

Cube::~Cube()
{
	device->Release();
	vertexBuffer->Release();
	indexBuffer->Release();
}

void Cube::createVertices()
{
	 // side 1
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, -1.0f, 1.0f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	RED		));   
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, -1.0f, 1.0f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	GREEN	));
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, 1.0f, 1.0f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	YELLOW	));
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, 1.0f, 1.0f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	BLUE	));
										
	// side 2																				 
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, -1.0f, -1.0f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	RED		));    
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, 1.0f, -1.0f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f), GREEN	));
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, -1.0f, -1.0f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f), YELLOW	));
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, 1.0f, -1.0f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	BLUE	));
										
	// side 3																			 	 
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, 1.0f, -1.0f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	RED		));    
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, 1.0f, 1.0f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	GREEN	));
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, 1.0f, -1.0f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	YELLOW	));
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, 1.0f, 1.0f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	BLUE	));
									
	// side 4																				 	 
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, -1.0f, -1.0f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	RED		));    
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, -1.0f, -1.0f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f), GREEN	));
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, -1.0f, 1.0f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f), YELLOW	));
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, -1.0f, 1.0f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	BLUE	));
								
	// side 5																						 
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, -1.0f, -1.0f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	RED		));    
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, 1.0f, -1.0f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	GREEN	));
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, -1.0f, 1.0f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	YELLOW	));
	vertices.push_back(Vertex(D3DXVECTOR3(1.0f, 1.0f, 1.0f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	BLUE	));
	
	// side 6
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, -1.0f, -1.0f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	RED		));    
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, -1.0f, 1.0f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f), GREEN	));
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, 1.0f, -1.0f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f), YELLOW	));
	vertices.push_back(Vertex(D3DXVECTOR3(-1.0f, 1.0f, 1.0f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	BLUE	));
}

void Cube::createVertexBuffer()
{
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(Vertex) * vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	device->CreateBuffer(&vbd, &vinitData, &vertexBuffer);
}

void Cube::createIndices()
{
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(6);
	indices.push_back(5);
	indices.push_back(7);

	indices.push_back(8);
	indices.push_back(9);
	indices.push_back(10);

	indices.push_back(10);
	indices.push_back(9);
	indices.push_back(11);

	indices.push_back(12);
	indices.push_back(13);
	indices.push_back(14);

	indices.push_back(14);
	indices.push_back(13);
	indices.push_back(15);

	indices.push_back(16);
	indices.push_back(17);
	indices.push_back(18);

	indices.push_back(18);
	indices.push_back(17);
	indices.push_back(19);

	indices.push_back(20);
	indices.push_back(21);
	indices.push_back(22);

	indices.push_back(22);
	indices.push_back(21);
	indices.push_back(23);
}

void Cube::createIndexBuffer()
{
	int numFaces = 6*2;

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(DWORD)*numFaces*3;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	device->CreateBuffer(&ibd, &iinitData, &indexBuffer);
}

void Cube::initialize()
{
	createVertices();
	createVertexBuffer();

	createIndices();
	createIndexBuffer();
}

ID3D11Buffer* Cube::getIndexBuffer()
{
	return indexBuffer;
}

ID3D11Buffer* Cube::getVertexBuffer()
{
	return vertexBuffer;
}