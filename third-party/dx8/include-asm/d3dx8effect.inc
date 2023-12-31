ifndef __D3DX8EFFECT__

__D3DX8EFFECT__			equ	1


DECLARE_INTERFACE <ID3DXTechnique_>
;   /*** IUnknown methods ***/
    INHERIT_IUnknown
;   /*** ID3DXTechnique methods ***/

    STDMETHOD	<GetDevice>, :DWORD
    STDMETHOD	<GetDesc>, :DWORD
    STDMETHOD	<GetPassDesc>, :DWORD, :DWORD
    STDMETHOD	<IsParameterUsed>, :DWORD

    STDMETHOD	<Validate>
    STDMETHOD	<Begin>, :DWORD
    STDMETHOD	<Pass>, :DWORD
    STDMETHOD	<End>, :DWORD

LPD3DXTECHNIQUE typedef PTR

 
DECLARE_INTERFACE <ID3DXEffect_>
;   /*** IUnknown methods ***/
    INHERIT_IUnknown
;   /*** ID3DXEffect methods ***/

    STDMETHOD	<GetDevice>, :DWORD
    STDMETHOD	<GetDesc>, :DWORD
    STDMETHOD	<GetParameterDesc>, :DWORD, :DWORD
    STDMETHOD	<GetTechniqueDesc>, :DWORD, :DWORD

    STDMETHOD	<SetDword>, :DWORD, :DWORD
    STDMETHOD	<GetDword>, :DWORD, :DWORD
    STDMETHOD	<SetFloat>, :DWORD, :DWORD
    STDMETHOD	<GetFloat>, :DWORD, :DWORD
    STDMETHOD	<SetVector>, :DWORD, :DWORD
    STDMETHOD	<GetVector>, :DWORD, :DWORD
    STDMETHOD	<SetMatrix>, :DWORD, :DWORD
    STDMETHOD	<GetMatrix>, :DWORD, :DWORD
    STDMETHOD	<SetTexture>, :DWORD, :DWORD
    STDMETHOD	<GetTexture>, :DWORD, :DWORD
    STDMETHOD	<SetVertexShader>, :DWORD, :DWORD
    STDMETHOD	<GetVertexShader>, :DWORD, :DWORD
    STDMETHOD	<SetPixelShader>, :DWORD, :DWORD
    STDMETHOD	<GetPixelShader>, :DWORD, :DWORD

    STDMETHOD	<GetTechnique>, :DWORD, :DWORD
    STDMETHOD	<CloneEffect>, :DWORD, :DWORD, :DWORD

LPD3DXEFFECT	typedef	ptr


  D3DXCompileEffectFromFileA	Proto	:DWORD, :DWORD, :DWORD
  D3DXCompileEffectFromFileW	Proto	:DWORD, :DWORD, :DWORD
  D3DXCompileEffect		Proto	:DWORD, :DWORD, :DWORD, :DWORD
  D3DXCreateEffect		Proto	:DWORD, :DWORD, :DWORD, :DWORD, :DWORD


ifdef UNICODE
  D3DXCompileEffectFromFile 	equ	D3DXCompileEffectFromFileW
else
  D3DXCompileEffectFromFile 	equ	D3DXCompileEffectFromFileA
ENDIF


_D3DXPARAMETERTYPE		TYPEDEF		DWORD
D3DXPARAMETERTYPE		TYPEDEF		_D3DXPARAMETERTYPE

D3DXPT_DWORD			equ		 0
D3DXPT_FLOAT			equ		 1
D3DXPT_VECTOR			equ		 2
D3DXPT_MATRIX			equ		 3
D3DXPT_TEXTURE			equ		 4
D3DXPT_VERTEXSHADER		equ		 5
D3DXPT_PIXELSHADER		equ		 6
D3DXPT_CONSTANT			equ		 7


_D3DXEFFECT_DESC		struct 

  Parameters			DWORD		?
  Techniques			DWORD		?
  Usage				DWORD		?

_D3DXEFFECT_DESC		ends

D3DXEFFECT_DESC			TYPEDEF		_D3DXEFFECT_DESC
LPD3DXEFFECT_DESC		TYPEDEF	PTR	D3DXEFFECT_DESC


_D3DXPARAMETER_DESC		struct

  _Name				DWORD			?
  _Type				D3DXPARAMETERTYPE	?

_D3DXPARAMETER_DESC		ENDS

D3DXPARAMETER_DESC		TYPEDEF		_D3DXPARAMETER_DESC
LPD3DXPARAMETER_DESC		TYPEDEF	PTR	D3DXPARAMETER_DESC


_D3DXTECHNIQUE_DESC		STRUCT

  _Name				DWORD		?
  _Passes			DWORD		?

_D3DXTECHNIQUE_DESC		ENDS

D3DXTECHNIQUE_DESC		TYPEDEF		_D3DXTECHNIQUE_DESC
LPD3DXTECHNIQUE_DESC		TYPEDEF Ptr	D3DXTECHNIQUE_DESC


_D3DXPASS_DESC			struct

  _Name				DWORD		?

_D3DXPASS_DESC			ENDS

D3DXPASS_DESC			TYPEDEF		_D3DXPASS_DESC
LPD3DXPASS_DESC			TYPEDEF	PTR	D3DXPASS_DESC

endif