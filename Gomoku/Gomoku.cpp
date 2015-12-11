// Gomoku.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Gomoku.h"
#include "Field.h"

#define MAX_LOADSTRING	100
#define BUTTONZ			4444
#define BUTTONZEND		BUTTONZ+SIZE*SIZE
#include "Server.h"
#include "Client.h"
#include "Network.h"


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
Field g_field;
HANDLE g_hSyncThread;
char g_ip[100];
char g_message[SIZE];
Network g_network;
Field::Player g_thisPlayer;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK		IPItemProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI 		ReceiveOtherPlayerTurn(LPVOID lpParam);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GOMOKU, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GOMOKU));

	// Main message loop:
	while (g_field.GetGamestate() == 0 && GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	switch (g_field.GetGamestate())
	{
	case Field::Draw:
		MessageBoxA(NULL, "It's a draw!", "Game Over", MB_OK);
		break;
	case Field::KrestikiWon:
		MessageBoxA(NULL, "Krestiki has won!", "Game Over", MB_OK);
		break;
	case Field::NolikiWon:
		MessageBoxA(NULL, "Noliki has won!", "Game Over", MB_OK);
		break;
	default:
		break;
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GOMOKU));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GOMOKU);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
   
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 500, 500, NULL, NULL, hInstance, NULL);
   int buttonSize = 25;
   for (int i = 0; i < SIZE; i++)
	   for (int j = 0; j < SIZE; j++)
			CreateWindowEx(WS_EX_STATICEDGE, L"BUTTON", L"", WS_CHILD | WS_VISIBLE,
			20+j*buttonSize, 20+i*buttonSize, buttonSize, buttonSize,
			hWnd, (HMENU)(BUTTONZ+i*SIZE+j), hInstance, NULL);

   DWORD thread_id;
   g_hSyncThread = CreateThread(NULL, 0, ReceiveOtherPlayerTurn, hWnd, 0, &thread_id);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		if (wmId >= BUTTONZ && wmId < BUTTONZEND && g_network.gomokuPipe != INVALID_HANDLE_VALUE && g_thisPlayer == g_field.GetActivePlayer())
		{
			int cellIndex = wmId - BUTTONZ;
			try{
				//если мы - крестики, то мы сначала ходим, а потом ждём хода ноликов (если не выиграли своим ходом)
				g_field.TakeTurn(cellIndex);
				SetDlgItemTextA(hWnd, wmId, Field::GameSymbols[g_field.GetCell(cellIndex)]);
				g_network.SendTurn(cellIndex);
			}
			catch (const char* msg)
			{
				MessageBoxA(NULL, msg, "Turn error", MB_OK);
			}
		}
		switch (wmId)
		{
		case BTN_CREATE_ID:
			g_network.CreateServer();
			g_thisPlayer = Field::Krestiki;
			break;
		case BTN_CONNECT_ID:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)IPItemProc);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	default:
		return DefWindowProc(hDlg, message, wParam, lParam);
	}
	return (INT_PTR)FALSE;
}

BOOL CALLBACK IPItemProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			if (!GetDlgItemTextA(hwndDlg, IDC_EDIT1, g_ip, 100))
				g_ip[0] = 0;
			else
			{
				try{
					g_network.ConnectToServer(g_ip);
					g_thisPlayer = Field::Noliki;
				}
				catch (const char* msg)
				{
					MessageBoxA(NULL, msg, "Network Error", MB_OK);
				}
			}
			// Fall through. 

		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
		}
	}
	return FALSE;
}

DWORD WINAPI ReceiveOtherPlayerTurn(LPVOID lpParam)
{
	HWND hWnd = (HWND)lpParam;
	while (g_field.GetGamestate() == Field::NotFinished)
	{
		if (g_network.gomokuPipe != INVALID_HANDLE_VALUE)
		{
			int cellIndex = g_network.ReceiveTurn();
			g_field.TakeTurn(cellIndex);
			SetDlgItemTextA(hWnd, cellIndex + BUTTONZ, Field::GameSymbols[g_field.GetCell(cellIndex)]);
		}
	}
	return 0;
}