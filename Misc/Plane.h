#ifndef PLANE_H
#define PLANE_H

#include <D3DX11\D3D11.h>
#include <D3DX11\D3DX11.h>

#include "..\Core\stdafx.h"
#include "..\Core\D3DShell.h"
#include "..\Core\misc.h"
#include "..\Core\BaseBuffer.h"
#include "..\Core\IShader.h"

struct Vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 color;
};


class Plane
{
private:
	BaseBuffer*	g_VertexBuffer;
	D3DXMATRIX m_world;
	
	D3DXVECTOR3 getNormal(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2);
	
public:
	Plane();
	~Plane();
	void			Initialize(D3DXMATRIX world,  float height, float widht, ID3D11Device* g_Device, ID3D11DeviceContext* g_DeviceContext );
	
	void            Update(); 
	void			setWorld(D3DXMATRIX world);
	
	void			applyBuffer();
	D3DXMATRIX		getWorld();
};
#endif