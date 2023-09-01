
#include "scene.h"
#include "../assets.h"

HINSTANCE hInst;



LRESULT CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR szText[]="Programmed by\r\nHani Kaabi\r\n\r\nOriginal Character Design\r\nWill Finn\r\n\r\nThis program is written in Assembly. It uses DirectX 8 for graphics.\r\n\r\nHani Kaabi\r\nWinter 2004\r\n";
	switch (message)
	{
	case WM_INITDIALOG:
		//TCHAR szVer[25];
		//wsprintf(szVer, TEXT("nabid.3.00.%s"), (IsWindowUnicode(hDlg) ? TEXT("unicode") : TEXT("ansi")));
		SetDlgItemText(hDlg, IDC_CREDITS, szText);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WORD wmId;

	switch (message)
	{
	case WM_COMMAND:
		wmId=LOWORD(wParam);
		switch (wmId)
		{
		case IDM_CLOSE:
			PostQuitMessage(0);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUT, hWnd, (DLGPROC)AboutProc);
			break;
		}
		break;

	case WM_NCRBUTTONUP:
		HMENU hMenu;
		hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDM_MAIN));
		if (hMenu)
		{
			TrackPopupMenu(GetSubMenu(hMenu, 0), TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
			DestroyMenu(hMenu);
		}
		break;

	case WM_NCHITTEST:
		if (DefWindowProc(hWnd, message, wParam, lParam)==HTCLIENT)
			return HTCAPTION;
		break;

	case WM_KEYDOWN:
		if (wParam==VK_ESCAPE)
			PostQuitMessage(0);
		break;

	case WM_PAINT:
		Render(hWnd);
		ValidateRect(hWnd, NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	hInst = hInstance;

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), NULL/*CS_CLASSDC*/, WndProc, 0L, 0L,
		hInst, NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, TEXT("DirectCogsworth"), NULL };
	RegisterClassEx(&wc);
	
	HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, TEXT("DirectCogsworth"), TEXT("Cogsworth"),
		WS_POPUP/*WS_OVERLAPPEDWINDOW*/, 100, 100, 256, 256,
		GetDesktopWindow(), NULL, hInst, NULL);

	if (!D3DInitialize(hWnd))
	{
		D3DUnInitialize();
		return -1;
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	MSG msg;
	while (1)
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				D3DUnInitialize();
				return (int)msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render(hWnd);
		}
}
