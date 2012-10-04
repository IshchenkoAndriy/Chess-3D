#include <windows.h>
#include <commctrl.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifndef _HINT_
#define _HINT_


class Hint {
	private:
		HWND hHint;
		HWND hParent;
		HINSTANCE hInstance;
		UINT uSize;
	public:
		Hint(HWND hPrnt, HINSTANCE hInst) {
			hParent = hPrnt;
			hInstance = hInst;
			
			hHint = CreateWindowEx(
				NULL, TOOLTIPS_CLASS, NULL, NULL,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				hParent, NULL,
				hInstance, NULL
			);
			
			TOOLINFO tInfo = {0};
			tInfo.cbSize = sizeof(TOOLINFO);
			tInfo.uFlags = TTF_TRACK | TTF_ABSOLUTE;
			tInfo.hwnd = hParent;
			
			SendMessage(hHint, TTM_ADDTOOL, NULL, (LPARAM)&tInfo);
			SendMessage(hHint, TTM_SETMAXTIPWIDTH, NULL, 128); // 128 - Tooltip width
		};
		
		void Show(LPTSTR text, LPTSTR title, HICON icon = (HICON)TTI_INFO_LARGE, UINT time = 2000) {
			TOOLINFO tInfo = {0};
			tInfo.cbSize = sizeof(TOOLINFO);
			tInfo.hwnd = hParent;
			tInfo.lpszText = text;
			
			SendMessage(hHint, TTM_UPDATETIPTEXT, NULL, (LPARAM)&tInfo);
			SendMessage(hHint, TTM_SETTITLE, (WPARAM)icon, (LPARAM)title);
			SendMessage(hHint, TTM_TRACKACTIVATE, WPARAM(TRUE), (LPARAM)&tInfo);
			uSize = HIWORD(SendMessage(hHint, TTM_GETBUBBLESIZE, NULL, (LPARAM)&tInfo));
			
			Update();
			
			SetTimer(hHint, 2012, time, &Hide); // 2012 - Timer ID
		};
		
		void Update() {
			POINT point;
			RECT rect;
			GetClientRect(hParent, &rect);
			point.x = rect.left + 10;
			point.y = rect.bottom - uSize - 10;
			ClientToScreen(hParent, &point);
			
			SendMessage(hHint, TTM_TRACKPOSITION, NULL, MAKELPARAM(point.x, point.y));
		};
		
		static void CALLBACK Hide(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
			TOOLINFO tInfo = {0};
			tInfo.cbSize = sizeof(TOOLINFO);
			SendMessage(hWnd, TTM_GETTOOLINFO, NULL, (LPARAM)&tInfo);
			SendMessage(hWnd, TTM_TRACKACTIVATE, WPARAM(FALSE), (LPARAM)&tInfo);
		};
		
		~Hint() {
		};
};
#endif