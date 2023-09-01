
.586p
.mmx
.model flat, stdcall
option casemap:none


include windows.inc
include kernel32.inc
include user32.inc
include shlwapi.inc

include msvcrt.inc

include d3d8.inc
;include d3dx8.inc
D3DX_DEFAULT equ 0FFFFFFFFh
include d3dx8math.inc
include d3dx8tex.inc



Release MACRO object
  .IF object!=NULL
    mcall [object], IUnknown_Release
    mov object, NULL
  .ENDIF
ENDM

FailCheck MACRO
  .IF eax!=D3D_OK
    invoke MessageBox, 0, szCogs, szCogs, MB_ICONSTOP
    ret
  .ENDIF
ENDM


CreateTexture MACRO texture, file, size
  invoke D3DXCreateTextureFromResourceEx, pD3DDevice, NULL, file, size, size, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR, 0, 0, NULL, NULL, ADDR texture
ENDM



IDI_COGSWORTH EQU 101
IDM_MAIN EQU 102
IDM_ABOUT EQU 103
IDM_CLOSE EQU 104
IDD_ABOUT EQU 201
IDC_CREDITS EQU 202
IDOK EQU 1
IDC_STATIC EQU (-1)
D3DFVF_CUSTOMVERTEX EQU (D3DFVF_XYZ OR D3DFVF_DIFFUSE OR D3DFVF_TEX1)

WinMain PROTO :HINSTANCE, :HINSTANCE, :LPSTR, :DWORD


WndProc PROTO :HWND, :UINT, :WPARAM, :LPARAM
DlgProc PROTO :HWND, :UINT, :WPARAM, :LPARAM
D3DInitialize PROTO :HWND
D3DGeometry PROTO

D3DTextures PROTO
D3DUninitialize PROTO
Render PROTO

DrawHand PROTO :LPDIRECT3DTEXTURE8, :FLOAT

CUSTOMVERTEX STRUCT DWORD

  x FLOAT ?
  y FLOAT ?
  z FLOAT ?
  color DWORD ?
  tu FLOAT ?
  tv FLOAT ?

CUSTOMVERTEX ENDS






.data
  szCogs db "Cogsworth", 0
  pD3D LPDIRECT3D8 NULL
  pD3DDevice LPDIRECT3DDEVICE8 NULL
  pVB LPDIRECT3DVERTEXBUFFER8 NULL

  pTXBkg LPDIRECT3DTEXTURE8 NULL
  pTXBelly LPDIRECT3DTEXTURE8 NULL
  pTXCogs LPDIRECT3DTEXTURE8 NULL
  pTXPendulum LPDIRECT3DTEXTURE8 NULL
  pTXMinute LPDIRECT3DTEXTURE8 NULL
  pTXHour LPDIRECT3DTEXTURE8 NULL
  pTXNose LPDIRECT3DTEXTURE8 NULL

  nTemp DWORD 0

  fTemp FLOAT 1.0f
  fNoseX FLOAT 0.075f

  fNoseY FLOAT 0.62f

  fNoseZ FLOAT 0.0f

  mxUni D3DMATRIX < 1.0f, 0.0f, 0.0f, 0.0f,\
                    0.0f, 1.0f, 0.0f, 0.0f,\
                    0.0f, 0.0f, 1.0f, 0.0f,\
                    0.0f, 0.0f, 0.0f, 1.0f>



.data?
  hInst HINSTANCE ?



.code

  cogsworth:

        invoke GetModuleHandle, NULL
        mov hInst, eax

        invoke WinMain, hInst, NULL, NULL, SW_SHOWDEFAULT
        invoke ExitProcess, eax



    WinMain PROC hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nCmdShow:DWORD
        LOCAL wc:WNDCLASSEX
        LOCAL hWnd:HWND
        LOCAL msg:MSG

        mov wc.cbSize, SIZEOF WNDCLASSEX
        mov wc.style, CS_CLASSDC
        mov wc.lpfnWndProc, OFFSET WndProc
        mov wc.cbClsExtra, 0
        mov wc.cbWndExtra, 0
        mov eax, hInst
        mov wc.hInstance, eax
        invoke LoadIcon, hInst, IDI_COGSWORTH
        mov eax, 0
        mov wc.hIcon, eax
        mov wc.hIconSm, eax
        invoke LoadCursor, NULL, IDC_ARROW
        mov wc.hCursor, eax
        mov wc.hbrBackground, NULL
        mov wc.lpszMenuName, NULL
        mov wc.lpszClassName, OFFSET szCogs
        invoke RegisterClassEx, ADDR wc

        invoke GetDesktopWindow
        invoke CreateWindowEx, WS_EX_TOPMOST, ADDR szCogs, ADDR szCogs, WS_POPUP,\
            CW_USEDEFAULT, CW_USEDEFAULT, 256, 256, eax, NULL, hInst, NULL

        mov hWnd, eax
        .IF eax==0
          invoke MessageBox, 0, addr szCogs, addr szCogs, 0
          mov eax, -1
          ret
        .ENDIF

        invoke D3DInitialize, hWnd

        invoke ShowWindow, hWnd, nCmdShow
        invoke UpdateWindow, hWnd
        
      MessageLoop:
        invoke PeekMessage, ADDR msg, NULL, 0, 0, PM_REMOVE
        .IF eax==0

          invoke Render
        .ELSE
          cmp msg.message, WM_QUIT
          jz Terminate

          invoke TranslateMessage, ADDR msg
          invoke DispatchMessage, ADDR msg
        .ENDIF
        jmp MessageLoop

      Terminate:
        invoke D3DUninitialize
        mov eax, msg.wParam
        ret
    WinMain ENDP


    WndProc PROC hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
        LOCAL hMenu:HMENU

        .IF message==WM_COMMAND
          mov eax, wParam
          .IF ax==IDM_CLOSE
            invoke PostQuitMessage, 0
          .ELSEIF ax==IDM_ABOUT
            invoke DialogBoxParam, hInst, IDD_ABOUT, hWnd, (OFFSET DlgProc), NULL
          .ENDIF


        .ELSEIF message==WM_DESTROY
          invoke PostQuitMessage, 0

        .ELSEIF message==WM_PAINT
          invoke Render
          invoke ValidateRect, hWnd, NULL

        .ELSEIF message==WM_KEYDOWN
          .IF wParam==VK_ESCAPE
            invoke PostQuitMessage, 0
          .ENDIF

        .ELSEIF message==WM_NCHITTEST
          invoke DefWindowProc, hWnd, message, wParam, lParam
          .IF eax==HTCLIENT
            mov eax, HTCAPTION
          .ENDIF
          ret

        .ELSEIF message==WM_NCRBUTTONUP
          invoke LoadMenu, hInst, IDM_MAIN
          mov hMenu, eax
          .IF hMenu!=NULL

            invoke GetSubMenu, hMenu, 0
            mov ecx, lParam
            and ecx, 0000ffffh
            mov edx, lParam
            shr edx, 16
            invoke TrackPopupMenu, eax, TPM_LEFTALIGN OR TPM_TOPALIGN OR TPM_RIGHTBUTTON, ecx, edx, 0, hWnd, NULL

            invoke DestroyMenu, hMenu
          .ENDIF

        .ELSE
          invoke DefWindowProc, hWnd, message, wParam, lParam
          ret
        .ENDIF

        mov eax, 0
        ret
    WndProc ENDP


    DlgProc PROC hDlg:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
      .data
        szCredits db 'Programmed by', 13, 10, 'Hani Kaabi', 13, 10, 13, 10,\
                     'Original Character Design', 13, 10, 'Will Finn', 13, 10, 13, 10,\
                     'This program is written in Assembly. It uses DirectX 8 for graphics.',\
                     13, 10, 13, 10, 'Hani Kaabi', 13, 10, 'Winter 2004', 13, 10, 0

      .code
        .IF message==WM_COMMAND
          mov eax, wParam
          .IF ax==IDOK
            invoke EndDialog, hDlg, ax
          .ENDIF

        .ELSEIF message==WM_INITDIALOG
          invoke SetDlgItemText, hDlg, IDC_CREDITS, ADDR szCredits

        .ELSE
          mov eax, FALSE
          ret

        .ENDIF

        mov eax, TRUE
        ret
    DlgProc ENDP


    D3DInitialize PROC hWnd:HWND
        LOCAL d3ddm: D3DDISPLAYMODE
        LOCAL d3dpp: D3DPRESENT_PARAMETERS

        invoke Direct3DCreate8, D3D_SDK_VERSION
        .IF eax!=0
          mov pD3D, eax
        .ELSE
          invoke MessageBox, 0, szCogs, szCogs, MB_ICONSTOP
          ret
        .ENDIF



        mcall [pD3D], IDirect3D8_GetAdapterDisplayMode, D3DADAPTER_DEFAULT, ADDR d3ddm
        FailCheck

        invoke RtlZeroMemory, ADDR d3dpp, SIZEOF D3DPRESENT_PARAMETERS
        mov eax, d3ddm.Format
        mov d3dpp.BackBufferFormat, eax
        mov d3dpp.SwapEffect, D3DSWAPEFFECT_DISCARD
        mov d3dpp.Windowed, TRUE
        mcall [pD3D], IDirect3D8_CreateDevice, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, ADDR d3dpp, ADDR pD3DDevice

        FailCheck

	  mcall [pD3DDevice], IDirect3DDevice8_SetRenderState, D3DRS_CULLMODE, D3DCULL_NONE
	  mcall [pD3DDevice], IDirect3DDevice8_SetRenderState, D3DRS_LIGHTING, FALSE
	  mcall [pD3DDevice], IDirect3DDevice8_SetRenderState, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA
	  mcall [pD3DDevice], IDirect3DDevice8_SetRenderState, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA
	  mcall [pD3DDevice], IDirect3DDevice8_SetRenderState, D3DRS_ALPHABLENDENABLE, TRUE

        invoke D3DGeometry

        invoke D3DTextures

        ret
    D3DInitialize ENDP


    D3DGeometry PROC
        LOCAL pVertices:PTR

        .data
          gVertexData CUSTOMVERTEX < -1.0f,  1.0f, 0.0f, 0ffffffffh, 0.0f, 0.0f>,\
                                   < -1.0f, -1.0f, 0.0f, 0ffffffffh, 0.0f, 1.0f>,\
                                   <  1.0f,  1.0f, 0.0f, 0ffffffffh, 1.0f, 0.0f>,\
                                   <  1.0f, -1.0f, 0.0f, 0ffffffffh, 1.0f, 1.0f>

          CUSTOMVERTEX             < -0.3f,  0.0f, 0.0f, 0ffffffffh, 0.0f, 0.0f>,\
                                   < -0.3f, -0.5f, 0.0f, 0ffffffffh, 0.0f, 1.0f>,\
                                   <  0.2f,  0.0f, 0.0f, 0ffffffffh, 1.0f, 0.0f>,\
                                   <  0.2f, -0.5f, 0.0f, 0ffffffffh, 1.0f, 1.0f>

          CUSTOMVERTEX             <  0.0f,  0.5f, 0.0f, 0ffffffffh, 0.0f, 0.0f>,\
                                   <  0.0f,  0.0f, 0.0f, 0ffffffffh, 0.0f, 1.0f>,\
                                   <  0.5f,  0.5f, 0.0f, 0ffffffffh, 1.0f, 0.0f>,\
                                   <  0.5f,  0.0f, 0.0f, 0ffffffffh, 1.0f, 1.0f>

        .code
        mcall [pD3DDevice], IDirect3DDevice8_CreateVertexBuffer, (3*SIZEOF gVertexData), NULL, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, ADDR pVB
        FailCheck

        mcall [pVB], IDirect3DVertexBuffer8_Lock, 0, SIZEOF gVertexData, ADDR pVertices, NULL
        FailCheck

        invoke crt_memcpy, pVertices, OFFSET gVertexData, (3*SIZEOF gVertexData)
        mcall [pVB], IDirect3DVertexBuffer8_Unlock


        mov nTemp, 0

        fild nTemp
        fld fNoseX
        fsub
        fst fNoseX

        ret
    D3DGeometry ENDP


    D3DTextures PROC
        IDTX_BKG      EQU 301
        IDTX_BELLY    EQU 302
        IDTX_BODY     EQU 303
        IDTX_NOSE     EQU 304
        IDTX_HOUR     EQU 305
        IDTX_MINUTE   EQU 306
        IDTX_PENDULUM EQU 307

        .code
        CreateTexture pTXBkg, IDTX_BKG, 256
        CreateTexture pTXBelly, IDTX_BELLY, 256
        CreateTexture pTXCogs, IDTX_BODY, 256
        CreateTexture pTXPendulum, IDTX_PENDULUM, 128
        CreateTexture pTXMinute, IDTX_MINUTE, 64
        CreateTexture pTXHour, IDTX_HOUR, 64
        CreateTexture pTXNose, IDTX_NOSE, 256

        ret
    D3DTextures ENDP



    D3DUninitialize PROC
        Release pTXBkg
        Release pTXBelly
        Release pTXCogs
        Release pTXPendulum
        Release pTXMinute
        Release pTXHour
        Release pTXNose

        Release pVB
        Release pD3DDevice
        Release pD3D

        ret
    D3DUninitialize ENDP


    Render PROC

        LOCAL mxRot:D3DXMATRIX
        LOCAL tm:SYSTEMTIME

        LOCAL rad:FLOAT


        invoke GetLocalTime, ADDR tm

        mcall [pD3DDevice], IDirect3DDevice8_Clear, 0, NULL, D3DCLEAR_TARGET, 000000ffh, fTemp, 0

        mcall [pD3DDevice], IDirect3DDevice8_BeginScene

        mcall [pD3DDevice], IDirect3DDevice8_SetStreamSource, 0, pVB, SIZEOF CUSTOMVERTEX

        mcall [pD3DDevice], IDirect3DDevice8_SetVertexShader, D3DFVF_CUSTOMVERTEX


        mcall [pD3DDevice], IDirect3DDevice8_SetTransform, 256, ADDR mxUni

        mcall [pD3DDevice], IDirect3DDevice8_SetTexture, 0, pTXBkg

        mcall [pD3DDevice], IDirect3DDevice8_DrawPrimitive, D3DPT_TRIANGLESTRIP, 0, 2


        mcall [pD3DDevice], IDirect3DDevice8_SetTexture, 0, pTXBelly

        mcall [pD3DDevice], IDirect3DDevice8_DrawPrimitive, D3DPT_TRIANGLESTRIP, 0, 2




        ; DrawPendulum
        .IF tm.wMilliseconds>499
          neg tm.wMilliseconds
          add tm.wMilliseconds, 1000

        .ENDIF
        sub tm.wMilliseconds, 250
        fild tm.wMilliseconds
        fldpi
        fmul
        
mov nTemp, 1200
        fild nTemp
        
fdiv
        fst rad
        invoke D3DXMatrixRotationZ, ADDR mxRot, rad


        mcall [pD3DDevice], IDirect3DDevice8_SetTransform, 256, ADDR mxRot
        mcall [pD3DDevice], IDirect3DDevice8_SetTexture, 0, pTXPendulum
        mcall [pD3DDevice], IDirect3DDevice8_DrawPrimitive, D3DPT_TRIANGLESTRIP, 4, 2


        mcall [pD3DDevice], IDirect3DDevice8_SetTransform, 256, ADDR mxUni
        mcall [pD3DDevice], IDirect3DDevice8_SetTexture, 0, pTXCogs

        mcall [pD3DDevice], IDirect3DDevice8_DrawPrimitive, D3DPT_TRIANGLESTRIP, 0, 2



        ; Draw Hands
        fild tm.wSecond
        mov nTemp, 60
        fild nTemp
        fdiv
        fild tm.wMinute
        fadd
        fst rad
        invoke DrawHand, pTXHour, rad


        fild tm.wSecond
        fst rad

        invoke DrawHand, pTXMinute, rad



        mcall [pD3DDevice], IDirect3DDevice8_SetTransform, 256, ADDR mxUni

        mcall [pD3DDevice], IDirect3DDevice8_SetTexture, 0, pTXNose

        mcall [pD3DDevice], IDirect3DDevice8_DrawPrimitive, D3DPT_TRIANGLESTRIP, 0, 2



        mcall [pD3DDevice], IDirect3DDevice8_EndScene
        mcall [pD3DDevice], IDirect3DDevice8_Present, NULL, NULL, NULL, NULL
        ret
    Render ENDP



    DrawHand PROC pTX:LPDIRECT3DTEXTURE8, minute:FLOAT
        LOCAL mxRot:D3DXMATRIX
        LOCAL mxTr:D3DXMATRIX
        LOCAL mxC:D3DXMATRIX
        LOCAL rad:FLOAT

        fld minute
        fldpi
        fmul
        mov nTemp, -30
        fild nTemp
        fdiv
        fst rad
        invoke D3DXMatrixRotationZ, ADDR mxRot, rad

        
invoke D3DXMatrixTranslation, ADDR mxTr, fNoseX, fNoseY, fNoseZ
        invoke D3DXMatrixMultiply, ADDR mxC, ADDR mxRot, ADDR mxTr

        mcall [pD3DDevice], IDirect3DDevice8_SetTransform, 256, ADDR mxC
        mcall [pD3DDevice], IDirect3DDevice8_SetTexture, 0, pTX

        mcall [pD3DDevice], IDirect3DDevice8_DrawPrimitive, D3DPT_TRIANGLESTRIP, 8, 2



        ret

    DrawHand ENDP

  end cogsworth
