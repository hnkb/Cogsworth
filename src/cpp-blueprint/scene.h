
#pragma once

#include "pch.h"


extern TCHAR szAppPath[];

BOOL D3DInitialize(HWND hWnd);
void D3DUnInitialize();
void Render(HWND hWnd);
