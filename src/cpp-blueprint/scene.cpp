
#include "scene.h"

#include <d3d8.h>
#include <d3dx8.h>


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
struct CUSTOMVERTEX
{
    FLOAT x, y, z;	// The position.
    DWORD color;	// The color.
    FLOAT tu, tv;	// The texture coordinates.
};



IDirect3D8* pD3D;
IDirect3DDevice8* pD3DDevice;
IDirect3DVertexBuffer8* pVB;

IDirect3DTexture8* pTXBelly;
IDirect3DTexture8* pTXCogs;
IDirect3DTexture8* pTXPendulum;
IDirect3DTexture8* pTXMinute;
IDirect3DTexture8* pTXHour;
IDirect3DTexture8* pTXNose;

TCHAR szAppPath[MAX_PATH];


D3DMATRIX mxUniform = {
	1.0f,	0.0f,	0.0f,	0.0f,
	0.0f,	1.0f,	0.0f,	0.0f,
	0.0f,	0.0f,	1.0f,	0.0f,
	0.0f,	0.0f,	0.0f,	1.0f,
};


BOOL GeometryInitialize()
{
	TCHAR szFile[MAX_PATH];
	lstrcpy(szFile, szAppPath);
	PathAppend(szFile, "data\\belly.png");
	D3DXCreateTextureFromFileEx(pD3DDevice, szFile, 256, 256, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR/*POINT*/, 0, 0, NULL, NULL, &pTXBelly);

	lstrcpy(szFile, szAppPath);
	PathAppend(szFile, "data\\pendulum.png");
	D3DXCreateTextureFromFileEx(pD3DDevice, szFile, 128, 128, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR/*POINT*/, 0, 0, NULL, NULL, &pTXPendulum);

	lstrcpy(szFile, szAppPath);
	PathAppend(szFile, "data\\cogsworth.png");
	D3DXCreateTextureFromFileEx(pD3DDevice, szFile, 256, 256, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR/*POINT*/, 0, 0, NULL, NULL, &pTXCogs);

	lstrcpy(szFile, szAppPath);
	PathAppend(szFile, "data\\minute hand.png");
	D3DXCreateTextureFromFileEx(pD3DDevice, szFile, 64, 64, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER, 0, 0, NULL, NULL, &pTXMinute);

	lstrcpy(szFile, szAppPath);
	PathAppend(szFile, "data\\hour hand.png");
	D3DXCreateTextureFromFileEx(pD3DDevice, szFile, 64, 64, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER, 0, 0, NULL, NULL, &pTXHour);

	lstrcpy(szFile, szAppPath);
	PathAppend(szFile, "data\\nose.png");
	D3DXCreateTextureFromFileEx(pD3DDevice, szFile, 256, 256, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER, 0, 0, NULL, NULL, &pTXNose);


	CUSTOMVERTEX pVertices[] = {
		{ -1.0f,  1.0f, 0.0f, 0xffffffff, 0.0f, 0.0f}, // x, y, z, color, tu, tv
		{ -1.0f, -1.0f, 0.0f, 0xffffffff, 0.0f, 1.0f},
		{  1.0f,  1.0f, 0.0f, 0xffffffff, 1.0f, 0.0f},
		{  1.0f, -1.0f, 0.0f, 0xffffffff, 1.0f, 1.0f},

		{ -0.3f,  0.0f, 0.0f, 0xffffffff, 0.0f, 0.0f}, // for the pendulum
		{ -0.3f, -0.5f, 0.0f, 0xffffffff, 0.0f, 1.0f},
		{  0.2f,  0.0f, 0.0f, 0xffffffff, 1.0f, 0.0f},
		{  0.2f, -0.5f, 0.0f, 0xffffffff, 1.0f, 1.0f},

		{  0.0f,  0.5f, 0.0f, 0xffffffff, 0.0f, 0.0f}, // for the hands
		{  0.0f,  0.0f, 0.0f, 0xffffffff, 0.0f, 1.0f},
		{  0.5f,  0.5f, 0.0f, 0xffffffff, 1.0f, 0.0f},
		{  0.5f,  0.0f, 0.0f, 0xffffffff, 1.0f, 1.0f},
	};

	if (FAILED(pD3DDevice->CreateVertexBuffer(sizeof(pVertices), NULL, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB)))
		return FALSE;

	BYTE* pVertexData;
	if (FAILED(pVB->Lock(0, sizeof(pVertices), &pVertexData, NULL)))
		return FALSE;
	memcpy(pVertexData, pVertices, sizeof(pVertices));
	pVB->Unlock();

	return TRUE;
}


BOOL D3DInitialize(HWND hWnd)
{
	pD3D = Direct3DCreate8(D3D_SDK_VERSION);
	if (!pD3D)
	{
		MessageBox(GetDesktopWindow(), TEXT("Error creating object"), TEXT("Direct3D"), MB_OK);
		return FALSE;
	}

	D3DDISPLAYMODE d3ddm;
	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		MessageBox(GetDesktopWindow(), TEXT("Unable to retrieve display info."), TEXT("Direct3D"), MB_OK);
		return FALSE;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat=d3ddm.Format;
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed=TRUE;
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice)))
	{
		MessageBox(GetDesktopWindow(), TEXT("Unable to create device"), TEXT("Direct3D"), MB_OK);
		return FALSE;
	}
	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	return GeometryInitialize();
}


void D3DUnInitialize()
{
	if (pTXNose)
		pTXNose->Release();
	if (pTXHour)
		pTXHour->Release();
	if (pTXMinute)
		pTXMinute->Release();
	if (pTXCogs)
		pTXCogs->Release();
	if (pTXPendulum)
		pTXPendulum->Release();
	if (pTXBelly)
		pTXBelly->Release();

	if (pVB)
		pVB->Release();

	if (pD3DDevice)
		pD3DDevice->Release();

	if (pD3D)
		pD3D->Release();
}




void SetupMatrices()
{
	D3DXMATRIX matView;
	/*
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 3.0f,-5.0f ),
                              &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                              &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
							  */
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 0.0f, -5.0f ),
                              &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                              &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
	
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}



void DrawHand(float rad, IDirect3DTexture8* pTexture, WORD minute)
{
	D3DXMATRIX mxRot, mxTr, mxC;
	D3DXMatrixRotationZ(&mxRot, rad);
	if (minute<15)
	{
		D3DXMatrixScaling(&mxC, 0.65f + 0.35f*minute/15, 0.75f + 0.25f*minute/15, 0.0f);
		D3DXMatrixMultiply(&mxC, &mxC, &mxRot);
	}
	else if (minute>30)
	{
		D3DXMatrixScaling(&mxC, 0.30f + abs(minute-50)*0.035f, 0.50f + abs(minute-50)*0.025f, 0.0f);
		D3DXMatrixMultiply(&mxC, &mxC, &mxRot);
	}
	else
		mxC=mxRot;
	D3DXMatrixTranslation(&mxTr, -0.075f, 0.62f, 0.0f);
	D3DXMatrixMultiply(&mxC, &mxC, &mxTr);
	pD3DDevice->SetTransform(D3DTS_WORLD, &mxC);
	pD3DDevice->SetTexture(0, pTexture);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);
}

void Render(HWND hWnd)
{
	//SetupMatrices();
	SYSTEMTIME tm;
	GetLocalTime(&tm);

	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	pD3DDevice->BeginScene();
	
	pD3DDevice->SetStreamSource(0, pVB, sizeof(CUSTOMVERTEX));
	pD3DDevice->SetVertexShader(D3DFVF_CUSTOMVERTEX);
	

	pD3DDevice->SetTransform(D3DTS_WORLD, &mxUniform);
	pD3DDevice->SetTexture(0, pTXBelly);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	// Draw Pendulum
	if (tm.wMilliseconds>499)
		tm.wMilliseconds=1000-tm.wMilliseconds;
	FLOAT rad=(FLOAT)tm.wMilliseconds-250;
	rad=D3DX_PI*rad/1200;
	D3DXMATRIX mxRot;
	D3DXMatrixRotationZ(&mxRot, rad);
	pD3DDevice->SetTransform(D3DTS_WORLD, &mxRot);
	pD3DDevice->SetTexture(0, pTXPendulum);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	
	pD3DDevice->SetTransform(D3DTS_WORLD, &mxUniform);
	pD3DDevice->SetTexture(0, pTXCogs);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	DrawHand(-D3DX_PI*(tm.wMinute+tm.wSecond/60.0f)/30, pTXHour, tm.wMinute);
	DrawHand(-D3DX_PI*tm.wSecond/30, pTXMinute, tm.wSecond);

	pD3DDevice->SetTransform(D3DTS_WORLD, &mxUniform);
	pD3DDevice->SetTexture(0, pTXNose);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


	pD3DDevice->EndScene();
	pD3DDevice->Present(NULL, NULL, NULL, NULL);

	static int fps=0;
	static DWORD lastupdate=0;
	fps++;
	if (GetTickCount()-lastupdate>1000)
	{
		lastupdate=GetTickCount();
		TCHAR sz[100];
		wsprintf(sz, "COGSWORTH :: %d fps", fps);
		SetWindowText(hWnd, sz);
		fps=0;
	}
}