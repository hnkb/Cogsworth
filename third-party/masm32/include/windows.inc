BOOL                        typedef DWORD
FLOAT                       typedef REAL4
HINSTANCE                   typedef DWORD
HMENU                       typedef DWORD
HWND                        typedef DWORD
LONG                        typedef DWORD
LPARAM                      typedef DWORD
LPSTR                       typedef DWORD
LPVOID                      typedef DWORD
UINT                        typedef DWORD
WPARAM                      typedef DWORD

WNDCLASSEXA STRUCT
  cbSize            DWORD      ?
  style             DWORD      ?
  lpfnWndProc       DWORD      ?
  cbClsExtra        DWORD      ?
  cbWndExtra        DWORD      ?
  hInstance         DWORD      ?
  hIcon             DWORD      ?
  hCursor           DWORD      ?
  hbrBackground     DWORD      ?
  lpszMenuName      DWORD      ?
  lpszClassName     DWORD      ?
  hIconSm           DWORD      ?
WNDCLASSEXA ENDS
WNDCLASSEX  equ  <WNDCLASSEXA>

POINT STRUCT
  x  DWORD ?
  y  DWORD ?
POINT ENDS

MSG STRUCT
  hwnd      DWORD      ?
  message   DWORD      ?
  wParam    DWORD      ?
  lParam    DWORD      ?
  time      DWORD      ?
  pt        POINT      <>
MSG ENDS

SYSTEMTIME STRUCT
  wYear             WORD      ?
  wMonth            WORD      ?
  wDayOfWeek        WORD      ?
  wDay              WORD      ?
  wHour             WORD      ?
  wMinute           WORD      ?
  wSecond           WORD      ?
  wMilliseconds     WORD      ?
SYSTEMTIME ENDS

GUID    STRUCT
    Data1   dd ?
    Data2   dw ?
    Data3   dw ?
    Data4   db 8 dup(?)
GUID ENDS

TRUE                                 equ 1
FALSE                                equ 0
NULL                                 equ 0

MAX_PATH                             equ 260

CS_CLASSDC                           equ 40h
CW_USEDEFAULT                        equ 80000000h
IDC_ARROW                            equ 32512
HTCAPTION                            equ 2
HTCLIENT                             equ 1
MB_ICONHAND                          equ 10h
MB_ICONSTOP                          equ MB_ICONHAND
PM_REMOVE                            equ 1h
S_OK                                 equ 0h
S_FALSE                              equ 1h
SW_SHOWDEFAULT                       equ 10
TPM_LEFTALIGN                        equ 0h
TPM_RIGHTBUTTON                      equ 2h
TPM_TOPALIGN                      equ 0
VK_ESCAPE                            equ 1Bh
WM_COMMAND                           equ 111h
WM_DESTROY                           equ 2h
WM_INITDIALOG                        equ 110h
WM_KEYDOWN                           equ 100h
WM_NCHITTEST                         equ 84h
WM_NCRBUTTONUP                       equ 0A5h
WM_PAINT                             equ 0Fh
WM_QUIT                              equ 12h
WS_POPUP                             equ 80000000h
WS_EX_TOPMOST                        equ 8h



; kernel32

ExitProcess PROTO STDCALL :DWORD
GetLocalTime PROTO STDCALL :DWORD
GetModuleFileNameA PROTO STDCALL :DWORD,:DWORD,:DWORD
GetModuleFileName equ <GetModuleFileNameA>
GetModuleHandleA PROTO STDCALL :DWORD
GetModuleHandle equ <GetModuleHandleA>
RtlZeroMemory PROTO STDCALL :DWORD,:DWORD
lstrcpyA PROTO STDCALL :DWORD,:DWORD
lstrcpy equ <lstrcpyA>



; user32

CreateWindowExA PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CreateWindowEx equ <CreateWindowExA>
DefWindowProcA PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD
DefWindowProc equ <DefWindowProcA>
DestroyMenu PROTO STDCALL :DWORD
DialogBoxParamA PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DialogBoxParam equ <DialogBoxParamA>
DispatchMessageA PROTO STDCALL :DWORD
DispatchMessage equ <DispatchMessageA>
EndDialog PROTO STDCALL :DWORD,:DWORD
GetDesktopWindow PROTO STDCALL
GetSubMenu PROTO STDCALL :DWORD,:DWORD
LoadCursorA PROTO STDCALL :DWORD,:DWORD
LoadCursor equ <LoadCursorA>
LoadIconA PROTO STDCALL :DWORD,:DWORD
LoadIcon equ <LoadIconA>
LoadMenuA PROTO STDCALL :DWORD,:DWORD
LoadMenu equ <LoadMenuA>
MessageBoxA PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD
MessageBox equ <MessageBoxA>
PeekMessageA PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
PeekMessage equ <PeekMessageA>
PostQuitMessage PROTO STDCALL :DWORD
RegisterClassExA PROTO STDCALL :DWORD
RegisterClassEx equ <RegisterClassExA>
SetDlgItemTextA PROTO STDCALL :DWORD,:DWORD,:DWORD
SetDlgItemText equ <SetDlgItemTextA>
ShowWindow PROTO STDCALL :DWORD,:DWORD
TrackPopupMenu PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
TranslateMessage PROTO STDCALL :DWORD
UpdateWindow PROTO STDCALL :DWORD
ValidateRect PROTO STDCALL :DWORD,:DWORD
