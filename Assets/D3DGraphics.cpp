/******************************************************************************************
*	Warplanes                                   										  *
*	Copyright 2016 - Barna Birtók - PcSpaceGeep									   		  *
*	Created with the use of Chili DirectX Framework Version 11.12.17					  *
*																						  *
*	Warplanes is free software: you can redistribute it and/or modify	                  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
*	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
*	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
*	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
*	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
*	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.									      *
*																						  *
*	Dependencies: Requires the DXSDK to run.											  *
******************************************************************************************/
#include "D3DGraphics.h"
#include "math.h"

D3DGraphics::D3DGraphics( HWND hWnd )
{
	backRect.pBits = NULL;
	
	pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp,sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,&d3dpp,&pDevice );

	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
}

D3DGraphics::~D3DGraphics()
{
	if( pDevice )
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if( pDirect3D )
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}
	if (pBackBuffer)
	{
		pBackBuffer->Release();
		pBackBuffer = NULL;
	}
}

void D3DGraphics::PutPixel( int x,int y,int r,int g,int b )
{
	((D3DCOLOR*)backRect.pBits)[ x + (backRect.Pitch >> 2) * y ] = D3DCOLOR_XRGB( r,g,b );
}

void D3DGraphics::BeginFrame()
{
	pDevice->Clear( 0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),0.0f,0 );
	pBackBuffer->LockRect(&backRect, NULL, NULL);
}

void D3DGraphics::EndFrame()
{
	pBackBuffer->UnlockRect();
	pDevice->Present( NULL,NULL,NULL,NULL );
}

void D3DGraphics::drawLine(int x1, int x2, int y1, int y2, int r, int g, int bl)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (abs(dy) > abs(dx))
	{
		if (y1 > y2)
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
			temp = x2;
			x2 = x1;
			x1 = temp;
		}
		float m = (float)dx / (float)dy;
		float b = x1 - m*y1;
		for (int y = y1;y <= y2;y++)
		{
			int x = m*y + b + 0.5f;
			PutPixel(x, y, r, g, bl);
		}
	}
	else
	{
		if (x1 > x2)
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
			temp = x2;
			x2 = x1;
			x1 = temp;
		}
		float m = (float)dy / (float)dx;
		float b = y1 - m*x1;
		for (int x = x1;x <= x2;x++)
		{
			int y = m*x + b + 0.5f;
			PutPixel(x, y, r, g, bl);
		}
	}
}

void D3DGraphics::drawRectangle(int x1, int x2, int y1, int y2, int r, int g, int b)
{
	for (int i = x1;i <= x2;i++)
	{
		for (int j = y1;j <= y2;j++)
		{
			PutPixel(i, j, r, g, b);
		}
	}
}

void D3DGraphics::drawCircle(int cx, int cy, int rad, int r, int g, int b)
{
	float sqrRad = rad * rad;
	int x0 = 0.7071068f * rad;
	for (int x = 0; x <= x0;x++)
	{
		int y = sqrt(sqrRad - x*x);
		PutPixel(cx + x, cy + y, r, g, b);
		PutPixel(cx + y, cy + x, r, g, b);
		PutPixel(cx - x, cy + y, r, g, b);
		PutPixel(cx - y, cy + x, r, g, b);
		PutPixel(cx + x, cy - y, r, g, b);
		PutPixel(cx + y, cy - x, r, g, b);
		PutPixel(cx - x, cy - y, r, g, b);
		PutPixel(cx - y, cy - x, r, g, b);
	}
}