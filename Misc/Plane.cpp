#include "Plane.h"
Plane::Plane()
{
	g_VertexBuffer = NULL;
}
Plane::~Plane()
{
	SAFE_DELETE(g_VertexBuffer);
}
void Plane::Initialize(D3DXMATRIX world,  int height, int widht, ID3D11Device* g_Device, ID3D11DeviceContext* g_DeviceContext )
{
	D3DXVECTOR3 n1=getNormal(D3DXVECTOR3(0,-1,0), D3DXVECTOR3(0,0,0), D3DXVECTOR3(1,0,0));
	D3DXVECTOR3 n2=getNormal(D3DXVECTOR3(0,-1,0), D3DXVECTOR3(1,0,0), D3DXVECTOR3(1,-1,0));	


	Vertex mesh []={
		{D3DXVECTOR3(0,-size,0)		,n1, D3DXVECTOR4(200,200, 200 ,0)},
		{D3DXVECTOR3(0,0,0)	, n1, D3DXVECTOR4(200,200, 200 ,0)},
		{D3DXVECTOR3(size,0,0)	, n1, D3DXVECTOR4(200,200, 200 ,0)},

		{D3DXVECTOR3(0, -size,0)		, n2, D3DXVECTOR4(200,200, 200 ,0)},
		{D3DXVECTOR3(size,0,0)	, n2, D3DXVECTOR4(200,200, 200 ,0)},
		{D3DXVECTOR3(size,-size,0)	, n2, D3DXVECTOR4(200,200, 200 ,0)}

	};

	BUFFER_INIT_DESC bufferDesc;
	bufferDesc.ElementSize = sizeof(Vertex);
	bufferDesc.InitData = mesh;
	bufferDesc.NumElements = 6;
	bufferDesc.Type = VERTEX_BUFFER;
	bufferDesc.Usage = BUFFER_DEFAULT;

	g_VertexBuffer = new Buffer();
	if(FAILED(g_VertexBuffer->Init(g_Device, g_DeviceContext, bufferDesc)))
	{
		MessageBox(0, "Could not initialize plane!", "Error", MB_OK);
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
	g_VertexBuffer->Apply();
}
D3DXVECTOR Plane::getNormal(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2)
{
	D3DXVECTOR3 v1= p1-p0;
	D3DXVECTOR3 v2= p2-p0;

	D3DXVECTOR3 normal, n;

	D3DXVec3Cross(&normal, &v1, &v2);
	D3DXVec3Normalize(&n, &normal);

	return n;
} 