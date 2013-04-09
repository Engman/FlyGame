#include "Plane.h"

Plane::Plane()
{
	g_VertexBuffer = NULL;
}
Plane::~Plane()
{
	DELETE_PTR(g_VertexBuffer);
	//SAFE_DELETE(g_VertexBuffer);
}
void Plane::Initialize(D3DXMATRIX world,  float height, float widht, ID3D11Device* g_Device, ID3D11DeviceContext* g_DeviceContext )
{
	D3DXVECTOR3 n1=getNormal(D3DXVECTOR3(0,-1,0), D3DXVECTOR3(0,0,0), D3DXVECTOR3(1,0,0));
	D3DXVECTOR3 n2=getNormal(D3DXVECTOR3(0,-1,0), D3DXVECTOR3(1,0,0), D3DXVECTOR3(1,-1,0));	

	Vertex mesh []={
		{D3DXVECTOR4(0,height,0, 1 )		,n1, D3DXVECTOR4(200,200, 200 ,0)},
		{D3DXVECTOR4(0,0,0,1)	, n1, D3DXVECTOR4(200,200, 200 ,0)},
		{D3DXVECTOR4(widht,0,0,1)	, n1, D3DXVECTOR4(200,200, 200 ,0)},

		{D3DXVECTOR4(0, height,0, 1)		, n2, D3DXVECTOR4(200,200, 200 ,0)},
		{D3DXVECTOR4(widht,0,0, 1)	, n2, D3DXVECTOR4(200,200, 200 ,0)},
		{D3DXVECTOR4(widht,height,0,1)	, n2, D3DXVECTOR4(200,200, 200 ,0)}

	};

	BaseBuffer::BUFFER_INIT_DESC bufferDesc;

	bufferDesc.elementSize = sizeof(Vertex);
	bufferDesc.data = mesh;
	bufferDesc.nrOfElements = 6;
	bufferDesc.type = BUFFER_FLAG::TYPE_VERTEX_BUFFER;
	bufferDesc.usage = BUFFER_FLAG::USAGE_DEFAULT;

	g_VertexBuffer = new BaseBuffer();
	if(FAILED(g_VertexBuffer->Initialize(bufferDesc)))
	{
		MessageBox(0, L"Could not initialize planeBuffer! Plane.cpp - Initialize", L"Error", MB_OK);
	}
	m_world= world;
}


void Plane::Update()
{

}


void Plane::setWorld(D3DXMATRIX world)
{
	m_world= world;
}
D3DXMATRIX Plane::getWorld()
{
	return m_world;
}

void Plane::applyBuffer()
{
	IShader::DRAW_DATA draw_data;
	draw_data.buffers.push_back(g_VertexBuffer);
	draw_data.worldMatrix = &m_world;

}
D3DXVECTOR3 Plane::getNormal(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2)
{
	D3DXVECTOR3 v1= p1-p0;
	D3DXVECTOR3 v2= p2-p0;

	D3DXVECTOR3 normal, n;

	D3DXVec3Cross(&normal, &v1, &v2);
	D3DXVec3Normalize(&n, &normal);

	return n;
} 