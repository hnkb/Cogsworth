D3DX_DEFAULT equ 0FFFFFFFFh


D3DXMATRIX struct
    _11			FLOAT		?
    _12			FLOAT		?
    _13			FLOAT		?
    _14			FLOAT		?
    _21			FLOAT		?
    _22			FLOAT		?
    _23			FLOAT		?
    _24			FLOAT		?
    _31			FLOAT		?
    _32			FLOAT		?
    _33			FLOAT		?
    _34			FLOAT		?
    _41			FLOAT		?
    _42			FLOAT		?
    _43			FLOAT		?
    _44			FLOAT		?
D3DXMATRIX ends

D3DXMatrixRotationZ   PROTO :Dword, :FLOAT
D3DXMatrixTranslation PROTO :DWORD, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixMultiply    PROTO :DWORD, :DWORD, :DWORD


D3DX_FILTER_NONE		equ	1
D3DX_FILTER_POINT		equ	2
D3DX_FILTER_LINEAR		equ	3
D3DX_FILTER_TRIANGLE		equ	4
D3DX_FILTER_BOX			equ	5

D3DXCreateTextureFromFileExA     PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
D3DXCreateTextureFromResourceExA PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
D3DXCreateTextureFromFileEx   	equ	D3DXCreateTextureFromFileExA
D3DXCreateTextureFromResourceEx   	equ	D3DXCreateTextureFromResourceExA
