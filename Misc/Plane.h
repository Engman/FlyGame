#ifndef PLANE_H
#define PLANE_H

#include "stdafx.h"
#include "Shader.h"
#include "Buffer.h"

struct Vertex
{
	D3DXVECTOR4 pos;
	D3DXVECTOR4 normal;
	D3DXVECTOR4 color;
};


class Plane
{
private:
	Buffer*	g_VertexBuffer;
	D3DXMATRIX m_world;
	
	D3DXVECTOR4 getNormal(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2);
	
public:
	Plane();
	~Plane();
	void			Initialize(D3DXMATRIX world,  int height, int widht, ID3D11Device* g_Device, ID3D11DeviceContext* g_DeviceContext );
	
	void            Update(); 
	void			setWorld(D3DXMATRIX world);
	
	void			applyBuffer();
	D3DXMATRIX		getWorld();
};
#endif