
#include "GraphicsContainerDX.h"


GraphicsContainerDX::GraphicsContainerDX(ShaderId vertexShaderId,
										 ShaderId pixelShaderId,
										 TextureId textureId,
										 std::vector<PosNormTex>* vertices,
										 std::vector<unsigned int>* indices,
										 unsigned int numVertices, 
										 unsigned int numIndices,
										 unsigned int numFaces,
										 unsigned int stride,
										 unsigned int offset) : GraphicsContainer(vertexShaderId, pixelShaderId, textureId,
																					  vertices, indices,
																					  numVertices, numIndices,
																					  numFaces, stride, offset)
{
	vertexBuffer = NULL;
	indexBuffer = NULL;
	texture = NULL;
}

GraphicsContainerDX::~GraphicsContainerDX()
{
	if(vertexBuffer)
		vertexBuffer->Release();
	if(indexBuffer)
		indexBuffer->Release();
	if(texture)
		texture->Release();
}

void GraphicsContainerDX::createVertexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(PosNormTex) * vertices->size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices->at(0);
	device->CreateBuffer(&vbd, &vinitData, &vertexBuffer);
}

void GraphicsContainerDX::createIndexBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(unsigned int)*indices->size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices->at(0);
	device->CreateBuffer(&ibd, &iinitData, &indexBuffer);
}

void GraphicsContainerDX::setTexture(ID3D11ShaderResourceView* texture)
{
	this->texture = texture;
}

ID3D11Buffer* GraphicsContainerDX::getVertexBuffer()
{
	return vertexBuffer;
}

ID3D11Buffer* GraphicsContainerDX::getIndexBuffer()
{
	return indexBuffer;
}

ID3D11ShaderResourceView* GraphicsContainerDX::getTexture()
{
	return texture;
}
