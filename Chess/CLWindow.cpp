#include <vector>
#include <windows.h>
#include <commctrl.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifndef _CLWindow_
#define _CLWindow_

struct CLButton {
	UINT BtnID;
	LPCTSTR BtnText;
	LPCTSTR BtnNote;
	HICON BtnIcon;
};

class CLWindow {
	private:
		HWND hWnd;
		HWND hParent;
		HINSTANCE hInstance;
	public:
		CLWindow(HWND hPrnt, HINSTANCE hInst) {
			hParent = hPrnt;
			hInstance = hInst;
			
			WNDCLASSEX wc = {0};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = CLWndProc;
			wc.hInstance = hInstance;
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
			wc.lpszClassName = TEXT("CLWindow");
			
			RegisterClassEx(&wc);
		};
		
		UINT Show(LPCTSTR WndText, std::vector<CLButton>& BtnStruct, BOOL CloseBtn = TRUE, UINT BtnWidth = 256) {
			hWnd = CreateWindowEx(
				WS_EX_TOOLWINDOW, TEXT("CLWindow"), WndText, WS_OVERLAPPED | WS_CAPTION,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				hParent, NULL,
				hInstance, NULL
			);
			
			if (CloseBtn) {
				SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) | WS_SYSMENU);
			}
			
			OSVERSIONINFO osver = {0};
			osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			GetVersionEx(&osver);
			
			RECT clientrect = {0};
			RECT windowrect = {0};
			RECT parentrect = {0};
			HWND* hBtnMas = new HWND[BtnStruct.size()];
			
			if (osver.dwMajorVersion >= 6) {
				SIZE* szBtnMas = new SIZE[BtnStruct.size()];
				for (UINT i = 0; i < BtnStruct.size(); i++) {
					hBtnMas[i] = CreateWindowEx(
						NULL, WC_BUTTON, BtnStruct[i].BtnText, WS_VISIBLE | WS_CHILD | BS_COMMANDLINK,
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
						hWnd, (HMENU)BtnStruct[i].BtnID,
						hInstance, NULL
					);
					SendMessage(hBtnMas[i], BCM_SETNOTE, NULL, (LPARAM)BtnStruct[i].BtnNote);
					SendMessage(hBtnMas[i], BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)BtnStruct[i].BtnIcon);
					szBtnMas[i].cx = BtnWidth;
					SendMessage(hBtnMas[i], BCM_GETIDEALSIZE, NULL, (LPARAM)&szBtnMas[i]);
				}
				
				UINT szWnd = 0;
				for (UINT i = 0; i < BtnStruct.size(); i++) {
					SetWindowPos(hBtnMas[i], NULL, 8, 8 + (8 * i) + szWnd, BtnWidth, szBtnMas[i].cy, SWP_NOZORDER);
					szWnd += szBtnMas[i].cy;
				}
				
				GetClientRect(hWnd, &clientrect);
				GetWindowRect(hWnd, &windowrect);
				
				SetWindowPos(
					hWnd, NULL,
					NULL, NULL,
					BtnWidth + 16 + (windowrect.right - windowrect.left) - (clientrect.right),
					(8 * BtnStruct.size()) + szWnd + 8 + (windowrect.bottom - windowrect.top) - (clientrect.bottom),
					SWP_NOMOVE | SWP_NOZORDER
				);
			}
			else {
				UINT szBtn = 48;
				for (UINT i = 0; i < BtnStruct.size(); i++) {
					hBtnMas[i] = CreateWindowEx(
						NULL, WC_BUTTON, BtnStruct[i].BtnText, WS_VISIBLE | WS_CHILD,
						8, 8 + (8 * i) + (szBtn * i), BtnWidth, szBtn,
						hWnd, (HMENU)BtnStruct[i].BtnID,
						hInstance, NULL
					);
					SendMessage(hBtnMas[i], BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)BtnStruct[i].BtnIcon);
				}
				
				GetClientRect(hWnd, &clientrect);
				GetWindowRect(hWnd, &windowrect);
				
				SetWindowPos(
					hWnd, NULL,
					NULL, NULL,
					BtnWidth + 16 + (windowrect.right - windowrect.left) - (clientrect.right),
					((8 + szBtn) * BtnStruct.size()) + 8 + (windowrect.bottom - windowrect.top) - (clientrect.bottom),
					SWP_NOMOVE | SWP_NOZORDER
				);
			}
			
			GetWindowRect(hWnd, &windowrect);
			GetWindowRect(hParent, &parentrect);
			
			SetWindowPos(
				hWnd, NULL,
				((parentrect.right - parentrect.left) - (windowrect.right - windowrect.left)) / 2 + parentrect.left,
				((parentrect.bottom - parentrect.top) - (windowrect.bottom - windowrect.top)) / 2 + parentrect.top,
				NULL, NULL,
				SWP_NOSIZE | SWP_NOZORDER
			);
			
			EnableWindow(hParent, FALSE);
			ShowWindow(hWnd, SW_SHOWNORMAL);
			
			MSG msg;
			UINT res;
			while (GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				
				res = GetWindowLong(hWnd, GWL_USERDATA);
				for (UINT i = 0; i < BtnStruct.size(); i++) {
					if (res == BtnStruct[i].BtnID) {
						EnableWindow(hParent, TRUE);
						DestroyWindow(hWnd);
						return res;
					}
				}
				if (res == WM_CLOSE) {
					if (CloseBtn) {
						break;
					}
				}
			}
			
			EnableWindow(hParent, TRUE);
			DestroyWindow(hWnd);
			return 0;
		};
		
		~CLWindow() {
			UnregisterClass(TEXT("CLWindow"), hInstance);
		};
		
	private:
		static LRESULT CALLBACK CLWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case WM_COMMAND:
					SetWindowLong(hWnd, GWL_USERDATA, wParam);
					break;
					
				case WM_CLOSE:
					SetWindowLong(hWnd, GWL_USERDATA, WM_CLOSE);
					break;
					
				case WM_KEYDOWN:
					if (LOWORD(wParam) == VK_ESCAPE) {
						SetWindowLong(hWnd, GWL_USERDATA, WM_CLOSE);
					}
					else {
						return DefWindowProc(hWnd, uMsg, wParam, lParam);
					}
					break;
					
				default:
					return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
			
			return 0;
		};
};
#endif