
include dx_objbase.def

D3D_SDK_VERSION     EQU 120


DECLARE_INTERFACE <IDirect3D8_>
;{
    ;/*** IUnknown methods ***/
    INHERIT_IUnknown
    ;STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    ;STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    ;STDMETHOD_(ULONG,Release)(THIS) PURE;

    ;/*** IDirect3D8 methods ***/
    STDMETHOD <RegisterSoftwareDevice>,:DWORD                                   ;,(THIS_ void* pInitializeFunction) PURE;
    STDMETHOD <GetAdapterCount>                                                 ;(THIS) PURE;
    STDMETHOD <GetAdapterIdentifier>,:DWORD,:DWORD,:DWORD                       ;(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER8* pIdentifier) PURE;
    STDMETHOD <GetAdapterModeCount>,:DWORD                                      ;(THIS_ UINT Adapter) PURE;
    STDMETHOD <EnumAdapterModes>,:DWORD,:DWORD,:DWORD                           ;(THIS_ UINT Adapter,UINT Mode,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD <GetAdapterDisplayMode>,:DWORD,:DWORD                             ;(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD <CheckDeviceType>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD              ;(THIS_ UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed) PURE;
    STDMETHOD <CheckDeviceFormat>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD     ;(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) PURE;
    STDMETHOD <CheckDeviceMultiSampleType>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD   ;(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType) PURE;
    STDMETHOD <CheckDepthStencilMatch>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD       ;(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) PURE;
    STDMETHOD <GetDeviceCaps>,:DWORD,:DWORD,:DWORD                              ;(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS8* pCaps) PURE;
    STDMETHOD <GetAdapterMonitor>,:DWORD                                        ;(THIS_ UINT Adapter) PURE;
    STDMETHOD <CreateDevice>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD          ;(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice8** ppReturnedDeviceInterface) PURE;
;};

LPDIRECT3D8 typedef PTR
PDIRECT3D8 typedef PTR



DECLARE_INTERFACE <IDirect3DDevice8_>
;{
    ;/*** IUnknown methods ***/
    INHERIT_IUnknown
    ;STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    ;STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    ;STDMETHOD_(ULONG,Release)(THIS) PURE;

    ;/*** IDirect3DDevice8 methods ***/
    STDMETHOD <TestCooperativeLevel>                                                            ;(THIS) PURE;
    STDMETHOD <GetAvailableTextureMem>                                                          ;(THIS) PURE;
    STDMETHOD <ResourceManagerDiscardBytes>,:DWORD                                              ;(THIS_ DWORD Bytes) PURE;
    STDMETHOD <GetDirect3D>,:DWORD                                                              ;(THIS_ IDirect3D8** ppD3D8) PURE;
    STDMETHOD <GetDeviceCaps>,:DWORD                                                            ;(THIS_ D3DCAPS8* pCaps) PURE;
    STDMETHOD <GetDisplayMode>,:DWORD                                                           ;(THIS_ D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD <GetCreationParameters>,:DWORD                                                    ;(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters) PURE;
    STDMETHOD <SetCursorProperties>,:DWORD,:DWORD,:DWORD                                        ;(THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface8* pCursorBitmap) PURE;
    STDMETHOD <SetCursorPosition>,:DWORD,:DWORD,:DWORD                                          ;(THIS_ UINT XScreenSpace,UINT YScreenSpace,DWORD Flags) PURE;
    STDMETHOD <ShowCursor>,:DWORD                                                               ;(THIS_ BOOL bShow) PURE;
    STDMETHOD <CreateAdditionalSwapChain>,:DWORD,:DWORD                                         ;(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain8** pSwapChain) PURE;
    STDMETHOD <Reset>,:DWORD                                                                    ;(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) PURE;
    STDMETHOD <Present>,:DWORD,:DWORD,:DWORD,:DWORD                                             ;(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) PURE;
    STDMETHOD <GetBackBuffer>,:DWORD,:DWORD,:DWORD                                              ;(THIS_ UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer) PURE;
    STDMETHOD <GetRasterStatus>,:DWORD                                                          ;(THIS_ D3DRASTER_STATUS* pRasterStatus) PURE;
    STDMETHOD <SetGammaRamp>,:DWORD,:DWORD                                                      ;(THIS_ DWORD Flags,CONST D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD <GetGammaRamp>,:DWORD                                                             ;(THIS_ D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD <CreateTexture>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                  ;(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture8** ppTexture) PURE;
    STDMETHOD <CreateVolumeTexture>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD     ;(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture8** ppVolumeTexture) PURE;
    STDMETHOD <CreateCubeTexture>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                     ;(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture8** ppCubeTexture) PURE;
    STDMETHOD <CreateVertexBuffer>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                           ;(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer8** ppVertexBuffer) PURE;
    STDMETHOD <CreateIndexBuffer>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                            ;(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer8** ppIndexBuffer) PURE;
    STDMETHOD <CreateRenderTarget>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                    ;(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,BOOL Lockable,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD <CreateDepthStencilSurface>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                    ;(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD <CreateImageSurface>,:DWORD,:DWORD,:DWORD,:DWORD                                  ;(THIS_ UINT Width,UINT Height,D3DFORMAT Format,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD <CopyRects>,:DWORD                                                                ;(THIS_ IDirect3DSurface8* pSourceSurface,CONST RECT* pSourceRectsArray,UINT cRects,IDirect3DSurface8* pDestinationSurface,CONST POINT* pDestPointsArray) PURE;
    STDMETHOD <UpdateTexture>,:DWORD                                                            ;(THIS_ IDirect3DBaseTexture8* pSourceTexture,IDirect3DBaseTexture8* pDestinationTexture) PURE;
    STDMETHOD <GetFrontBuffer>,:DWORD                                                           ;(THIS_ IDirect3DSurface8* pDestSurface) PURE;
    STDMETHOD <SetRenderTarget>,:DWORD ,:DWORD                                                         ;(THIS_ IDirect3DSurface8* pRenderTarget,IDirect3DSurface8* pNewZStencil) PURE;
    STDMETHOD <GetRenderTarget>,:DWORD                                                          ;(THIS_ IDirect3DSurface8** ppRenderTarget) PURE;
    STDMETHOD <GetDepthStencilSurface>,:DWORD                                                   ;(THIS_ IDirect3DSurface8** ppZStencilSurface) PURE;
    STDMETHOD <BeginScene>                                                                      ;(THIS) PURE;
    STDMETHOD <EndScene>                                                                        ;(THIS) PURE;
    STDMETHOD <Clear>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                                 ;(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) PURE;
    STDMETHOD <SetTransform>,:DWORD,:DWORD                                                      ;(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) PURE;
    STDMETHOD <GetTransform>,:DWORD,:DWORD                                                      ;(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) PURE;
    STDMETHOD <MultiplyTransform>,:DWORD,:DWORD                                                 ;(THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*) PURE;
    STDMETHOD <SetViewport>,:DWORD                                                              ;(THIS_ CONST D3DVIEWPORT8* pViewport) PURE;
    STDMETHOD <GetViewport>,:DWORD                                                              ;(THIS_ D3DVIEWPORT8* pViewport) PURE;
    STDMETHOD <SetMaterial>,:DWORD                                                              ;(THIS_ CONST D3DMATERIAL8* pMaterial) PURE;
    STDMETHOD <GetMaterial>,:DWORD                                                              ;(THIS_ D3DMATERIAL8* pMaterial) PURE;
    STDMETHOD <SetLight>,:DWORD,:DWORD                                                          ;(THIS_ DWORD Index,CONST D3DLIGHT8*) PURE;
    STDMETHOD <GetLight>,:DWORD,:DWORD                                                          ;(THIS_ DWORD Index,D3DLIGHT8*) PURE;
    STDMETHOD <LightEnable>,:DWORD,:DWORD                                                       ;(THIS_ DWORD Index,BOOL Enable) PURE;
    STDMETHOD <GetLightEnable>,:DWORD,:DWORD                                                    ;(THIS_ DWORD Index,BOOL* pEnable) PURE;
    STDMETHOD <SetClipPlane>,:DWORD,:DWORD                                                      ;(THIS_ DWORD Index,CONST float* pPlane) PURE;
    STDMETHOD <GetClipPlane>,:DWORD,:DWORD                                                      ;(THIS_ DWORD Index,float* pPlane) PURE;
    STDMETHOD <SetRenderState>,:DWORD,:DWORD                                                    ;(THIS_ D3DRENDERSTATETYPE State,DWORD Value) PURE;
    STDMETHOD <GetRenderState>,:DWORD,:DWORD                                                    ;(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue) PURE;
    STDMETHOD <BeginStateBlock>                                                                 ;(THIS) PURE;
    STDMETHOD <EndStateBlock>,:DWORD                                                            ;(THIS_ DWORD* pToken) PURE;
    STDMETHOD <ApplyStateBlock>,:DWORD                                                          ;(THIS_ DWORD Token) PURE;
    STDMETHOD <CaptureStateBlock>,:DWORD                                                        ;(THIS_ DWORD Token) PURE;
    STDMETHOD <DeleteStateBlock>,:DWORD                                                         ;(THIS_ DWORD Token) PURE;
    STDMETHOD <CreateStateBlock>,:DWORD,:DWORD                                                  ;(THIS_ D3DSTATEBLOCKTYPE Type,DWORD* pToken) PURE;
    STDMETHOD <SetClipStatus>,:DWORD                                                             ; <THIS_ CONST D3DCLIPSTATUS8* pClipStatus) PURE;
    STDMETHOD <GetClipStatus>,:DWORD                                                             ; <THIS_ D3DCLIPSTATUS8* pClipStatus) PURE;
    STDMETHOD <GetTexture>,:DWORD,:DWORD                                                         ; <THIS_ DWORD Stage,IDirect3DBaseTexture8** ppTexture) PURE;
    STDMETHOD <SetTexture>,:DWORD,:DWORD                                                         ; <THIS_ DWORD Stage,IDirect3DBaseTexture8* pTexture) PURE;
    STDMETHOD <GetTextureStageState>,:DWORD,:DWORD,:DWORD                                        ; <THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) PURE;
    STDMETHOD <SetTextureStageState>,:DWORD,:DWORD,:DWORD                                        ; <THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) PURE;
    STDMETHOD <ValidateDevice>,:DWORD                                                            ; <THIS_ DWORD* pNumPasses) PURE;
    STDMETHOD <GetInfo>,:DWORD,:DWORD,:DWORD                                                     ; <THIS_ DWORD DevInfoID,void* pDevInfoStruct,DWORD DevInfoStructSize) PURE;
    STDMETHOD <SetPaletteEntries>,:DWORD,:DWORD                                                  ; <THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries) PURE;
    STDMETHOD <GetPaletteEntries>,:DWORD,:DWORD                                                  ; <THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries) PURE;
    STDMETHOD <SetCurrentTexturePalette>,:DWORD                                                  ; <THIS_ UINT PaletteNumber) PURE;
    STDMETHOD <GetCurrentTexturePalette>,:DWORD                                                  ; <THIS_ UINT *PaletteNumber) PURE;
    STDMETHOD <DrawPrimitive>,:DWORD,:DWORD,:DWORD                                               ; <THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) PURE;
    STDMETHOD <DrawIndexedPrimitive>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                          ; <THIS_ D3DPRIMITIVETYPE,UINT minIndex,UINT NumVertices,UINT startIndex,UINT primCount) PURE;
    STDMETHOD <DrawPrimitiveUP>,:DWORD,:DWORD,:DWORD,:DWORD                                      ; <THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD <DrawIndexedPrimitiveUP>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD   
        ; <THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertexIndices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD <ProcessVertices>,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD                               ; <THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer8* pDestBuffer,DWORD Flags) PURE;
    STDMETHOD <CreateVertexShader>,:DWORD,:DWORD,:DWORD,:DWORD                                   ; <THIS_ CONST DWORD* pDeclaration,CONST DWORD* pFunction,DWORD* pHandle,DWORD Usage) PURE;
    STDMETHOD <SetVertexShader>,:DWORD                                                           ; <THIS_ DWORD Handle) PURE;
    STDMETHOD <GetVertexShader>,:DWORD                                                           ; <THIS_ DWORD* pHandle) PURE;
    STDMETHOD <DeleteVertexShader>,:DWORD                                                        ; <THIS_ DWORD Handle) PURE;
    STDMETHOD <SetVertexShaderConstant>,:DWORD,:DWORD,:DWORD                                     ; <THIS_ DWORD Register,CONST void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD <GetVertexShaderConstant>,:DWORD,:DWORD,:DWORD                                     ; <THIS_ DWORD Register,void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD <GetVertexShaderDeclaration>,:DWORD,:DWORD,:DWORD                                  ; <THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD <GetVertexShaderFunction>,:DWORD,:DWORD,:DWORD                                     ; <THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD <SetStreamSource>,:DWORD,:DWORD,:DWORD                                             ; <THIS_ UINT StreamNumber,IDirect3DVertexBuffer8* pStreamData,UINT Stride) PURE;
    STDMETHOD <GetStreamSource>,:DWORD,:DWORD,:DWORD                                             ; <THIS_ UINT StreamNumber,IDirect3DVertexBuffer8** ppStreamData,UINT* pStride) PURE;
    STDMETHOD <SetIndices>,:DWORD,:DWORD                                                         ; <THIS_ IDirect3DIndexBuffer8* pIndexData,UINT BaseVertexIndex) PURE;
    STDMETHOD <GetIndices>,:DWORD,:DWORD                                                         ; <THIS_ IDirect3DIndexBuffer8** ppIndexData,UINT* pBaseVertexIndex) PURE;
    STDMETHOD <CreatePixelShader>,:DWORD,:DWORD                                                  ; <THIS_ CONST DWORD* pFunction,DWORD* pHandle) PURE;
    STDMETHOD <SetPixelShader>,:DWORD                                                            ; <THIS_ DWORD Handle) PURE;
    STDMETHOD <GetPixelShader>,:DWORD                                                            ; <THIS_ DWORD* pHandle) PURE;
    STDMETHOD <DeletePixelShader>,:DWORD                                                         ; <THIS_ DWORD Handle) PURE;
    STDMETHOD <SetPixelShaderConstant>,:DWORD,:DWORD,:DWORD                                      ; <THIS_ DWORD Register,CONST void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD <GetPixelShaderConstant>,:DWORD,:DWORD,:DWORD                                      ; <THIS_ DWORD Register,void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD <GetPixelShaderFunction>,:DWORD,:DWORD,:DWORD                                      ; <THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD <DrawRectPatch>,:DWORD,:DWORD,:DWORD                                               ; <THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) PURE;
    STDMETHOD <DrawTriPatch>,:DWORD,:DWORD,:DWORD                                                ; <THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) PURE;
    STDMETHOD <DeletePatch>,:DWORD                                                               ;(THIS_ UINT Handle) PURE;
;};

LPDIRECT3DDEVICE8 typedef PTR
PDIRECT3DDEVICE8 typedef PTR



DECLARE_INTERFACE <IDirect3DVertexBuffer8_>      ;, IDirect3DResource8)
;{
    ;/*** IUnknown methods ***/
    INHERIT_IUnknown
    ;STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    ;STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    ;STDMETHOD_(ULONG,Release)(THIS) PURE;

    ;/*** IDirect3DResource8 methods ***/
    STDMETHOD <GetDevice>,:DWORD                                ;THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD <SetPrivateData>,:DWORD,:DWORD,:DWORD,:DWORD      ;THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD <GetPrivateData>,:DWORD,:DWORD,:DWORD             ;THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD <FreePrivateData>,:DWORD                          ;THIS_ REFGUID refguid) PURE;
    STDMETHOD <SetPriority>,:DWORD                              ;THIS_ DWORD PriorityNew) PURE;
    STDMETHOD <GetPriority>                                     ;THIS) PURE;
    STDMETHOD <PreLoad>                                         ;THIS) PURE;
    STDMETHOD <GetType>                                         ;THIS) PURE;
    STDMETHOD <Lock>,:DWORD,:DWORD,:DWORD,:DWORD                ;THIS_ UINT OffsetToLock,UINT SizeToLock,BYTE** ppbData,DWORD Flags) PURE;
    STDMETHOD <Unlock>                                          ;THIS) PURE;
    STDMETHOD <GetDesc>,:DWORD                                  ;THIS_ D3DVERTEXBUFFER_DESC *pDesc) PURE;
;};

LPDIRECT3DVERTEXBUFFER8 typedef PTR
PDIRECT3DVERTEXBUFFER8 typedef PTR


DECLARE_INTERFACE <IDirect3DTexture8_>           ;, IDirect3DBaseTexture8)
;{
    ;/*** IUnknown methods ***/
    INHERIT_IUnknown
    ;STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    ;STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    ;STDMETHOD_(ULONG,Release)(THIS) PURE;

    ;/*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD <GetDevice>,:DWORD                                            ;(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD <SetPrivateData>,:DWORD,:DWORD,:DWORD,:DWORD                  ;(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD <GetPrivateData>,:DWORD,:DWORD,:DWORD                         ;(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD <FreePrivateData>,:DWORD                                      ;(THIS_ REFGUID refguid) PURE;
    STDMETHOD <SetPriority>,:DWORD                                          ;(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD <GetPriority>                                                 ;(THIS) PURE;
    STDMETHOD <PreLoad>                                                     ;(THIS) PURE;
    STDMETHOD <GetType>                                                     ;(THIS) PURE;
    STDMETHOD <SetLOD>,:DWORD                                               ;(THIS_ DWORD LODNew) PURE;
    STDMETHOD <GetLOD>                                                      ;(THIS) PURE;
    STDMETHOD <GetLevelCount>                                               ;(THIS) PURE;
    STDMETHOD <GetLevelDesc>,:DWORD,:DWORD                                  ;(THIS_ UINT Level,D3DSURFACE_DESC *pDesc) PURE;
    STDMETHOD <GetSurfaceLevel>,:DWORD,:DWORD                               ;(THIS_ UINT Level,IDirect3DSurface8** ppSurfaceLevel) PURE;
    STDMETHOD <LockRect>,:DWORD,:DWORD,:DWORD,:DWORD                        ;(THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD <UnlockRect>,:DWORD                                           ;(THIS_ UINT Level) PURE;
    STDMETHOD <AddDirtyRect>,:DWORD                                         ;(THIS_ CONST RECT* pDirtyRect) PURE;
;};

LPDIRECT3DTEXTURE8  typedef PTR
PDIRECT3DTEXTURE8 typedef PTR


D3DFORMAT TYPEDEF DWORD
D3DMULTISAMPLE_TYPE TYPEDEF DWORD
D3DSWAPEFFECT TYPEDEF DWORD


_D3DMATRIX struct   DWORD
    _11		FLOAT		?
    _12		FLOAT		?
    _13		FLOAT		?
    _14		FLOAT		?
    _21		FLOAT		?
    _22		FLOAT		?
    _23		FLOAT		?
    _24		FLOAT		?
    _31		FLOAT		?
    _32		FLOAT		?
    _33		FLOAT		?
    _34		FLOAT		?
    _41		FLOAT		?
    _42		FLOAT		?
    _43		FLOAT		?
    _44		FLOAT		?
_D3DMATRIX  ENDS
  D3DMATRIX TYPEDEF      _D3DMATRIX
LPD3DMATRIX	TYPEDEF	 PTR _D3DMATRIX

D3DDISPLAYMODE STRUCT
    _Width			DWORD ?
    Height			DWORD ?
    RefreshRate	DWORD ?
    Format			D3DFORMAT ?
D3DDISPLAYMODE ENDS

D3DPRESENT_PARAMETERS STRUCT
    BackBufferWidth	UINT ?
    BackBufferHeight	UINT ?
    BackBufferFormat	D3DFORMAT ?
    BackBufferCount	UINT ?

    MultiSampleType	D3DMULTISAMPLE_TYPE ?

    SwapEffect			D3DSWAPEFFECT ?
    hDeviceWindow		HWND ?
    Windowed			BOOL ?
    EnableAutoDepthStencil	BOOL ?
    AutoDepthStencilFormat	D3DFORMAT ?
    Flags				DWORD ?

    ;/* Following elements must be zero for Windowed mode */
    FullScreen_RefreshRateInHz		UINT ?
    FullScreen_PresentationInterval	UINT ?

D3DPRESENT_PARAMETERS ENDS


Direct3DCreate8 PROTO :UINT


D3DADAPTER_DEFAULT EQU 0
D3DCREATE_SOFTWARE_VERTEXPROCESSING EQU 020h
D3DDEVTYPE_HAL EQU 1
