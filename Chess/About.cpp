#include <windows.h>
#include <gdiplus.h>
#include "resource.h"

#define ABOUT_CLOSE 3201
#define ABOUT_ERROR 3202

#pragma comment (lib,"gdiplus.lib")

class About {
	private:
		HWND hAbout;
		HWND hParent;
		HINSTANCE hInstance;
	public:
		About(HWND hPrnt, HINSTANCE hInst) {
			hParent = hPrnt;
			hInstance = hInst;
			
			WNDCLASSEX wc = {0};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = AboutProc;
			wc.hInstance = hInstance;
			wc.hCursor = LoadCursor(NULL, IDC_HAND);
			wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
			wc.lpszClassName = TEXT("About");
			
			RegisterClassEx(&wc);
		};
		
		void Show() {
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			ULONG_PTR gdiplusToken;
			
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
			
			hAbout = CreateWindowEx(
				NULL, TEXT("About"), NULL, WS_POPUP,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				hParent, NULL,
				hInstance, NULL
			);
			
			EnableWindow(hParent, FALSE);
			ShowWindow(hAbout, SW_SHOWNORMAL);
			
			MSG msg;
			UINT res;
			while (GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				
				res = GetWindowLong(hAbout, GWL_USERDATA);
				if ((res == ABOUT_CLOSE) || (res == ABOUT_ERROR)) {
					break;
				}
			}
			
			EnableWindow(hParent, TRUE);
			DestroyWindow(hAbout);
			Gdiplus::GdiplusShutdown(gdiplusToken);
		};
		
		~About() {
			UnregisterClass(TEXT("About"), hInstance);
		};
		
	private:
		static LRESULT CALLBACK AboutProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			static Gdiplus::Bitmap* image;
			
			switch (uMsg) {
				case WM_CREATE:
					{
						HWND hParent = (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);
						HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
						HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(IDR_ABOUT), RT_RCDATA);
						if (!hRes) {
							MessageBox(hWnd, TEXT("Resource not found"), TEXT("Error"), MB_OK);
							SetWindowLong(hWnd, GWL_USERDATA, ABOUT_ERROR);
							return 0;
						}
						HGLOBAL hgTmp = LoadResource(hInstance, hRes);
						DWORD sz = SizeofResource(hInstance, hRes);
						void* pRes = LockResource(hgTmp);
						
						HGLOBAL hgRes = GlobalAlloc(GMEM_MOVEABLE, sz);
						if (!hgRes) {
							MessageBox(hWnd, TEXT("Memory not allocated"), TEXT("Error"), MB_OK);
							SetWindowLong(hWnd, GWL_USERDATA, ABOUT_ERROR);
							return 0;
						}
						void* pMem = GlobalLock(hgRes);
						CopyMemory(pMem, pRes, sz);
						GlobalUnlock(hgRes);
						
						IStream *pStream;
						if (FAILED(CreateStreamOnHGlobal(hgRes, TRUE, &pStream))) {
							GlobalFree(hgRes);
							MessageBox(hWnd, TEXT("Stream not created"), TEXT("Error"), MB_OK);
							SetWindowLong(hWnd, GWL_USERDATA, ABOUT_ERROR);
							return 0;
						}
						image = Gdiplus::Bitmap::FromStream(pStream);
						
						SetWindowPos(
							hWnd, NULL,
							NULL, NULL,
							image->GetWidth(), image->GetHeight(),
							SWP_NOMOVE | SWP_NOZORDER
						);
						
						RECT windowrect = {0};
						RECT parentrect = {0};
						GetWindowRect(hWnd, &windowrect);
						GetWindowRect(hParent, &parentrect);
						
						SetWindowPos(
							hWnd, NULL,
							((parentrect.right - parentrect.left) - (windowrect.right - windowrect.left)) / 2 + parentrect.left,
							((parentrect.bottom - parentrect.top) - (windowrect.bottom - windowrect.top)) / 2 + parentrect.top,
							NULL, NULL,
							SWP_NOSIZE | SWP_NOZORDER
						);
					};
					break;
					
				case WM_PAINT:
					{
						HDC hDC;
						RECT rect;
						PAINTSTRUCT ps;
						hDC = BeginPaint(hWnd, &ps);
						SetBkMode(hDC, TRANSPARENT);
						Gdiplus::Graphics graphics(hDC);
						GetClientRect(hWnd, &rect);
						Gdiplus::Rect drawrect(rect.left, rect.top, rect.right, rect.bottom);
						graphics.DrawImage(image, drawrect);
						EndPaint(hWnd, &ps);
					};
					break;
					
				case WM_LBUTTONDOWN:
					SetWindowLong(hWnd, GWL_USERDATA, ABOUT_CLOSE);
					break;
					
				case WM_KEYDOWN:
					if (LOWORD(wParam) == VK_ESCAPE) {
						SetWindowLong(hWnd, GWL_USERDATA, ABOUT_CLOSE);
					}
					break;
					
				default:
					return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
			
			return 0;
		};
};
