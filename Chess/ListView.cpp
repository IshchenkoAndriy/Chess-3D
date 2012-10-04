#include <windows.h>
#include <commctrl.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define TEXT_NICK					"ѕсевдон≥м гравц€"
#define TEXT_PCNAME					"≤м'€ комп'ютера"
#define TEXT_IPADDR					"IP-адреса"
#define TEXT_NOSERVERS				"—ервер≥в не знайдено"

INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static TCPClient* client;
	
	switch (uMsg) {
		case WM_INITDIALOG:
			{
				client = (TCPClient*)lParam;
				
				HWND hLV = GetDlgItem(hwndDlg, IDC_SERVERS_LIST);
				
				ListView_SetExtendedListViewStyle(hLV, LVS_EX_FULLROWSELECT);
				
				LVCOLUMN lvCol = {0};
				lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
				lvCol.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH;
				lvCol.cx = 164;
				
				lvCol.iSubItem = 1;
				lvCol.pszText = TEXT(TEXT_NICK);
				ListView_InsertColumn(hLV, 1, &lvCol);
				
				lvCol.iSubItem = 2;
				lvCol.pszText = TEXT(TEXT_PCNAME);
				ListView_InsertColumn(hLV, 2, &lvCol);
				
				lvCol.cx = 104;
				lvCol.iSubItem = 3;
				lvCol.pszText = TEXT(TEXT_IPADDR);
				ListView_InsertColumn(hLV, 3, &lvCol);
				
				int result = client->LocateServers(hwndDlg);
				switch (result) {
					case ERROR_NOTINITED:
					case ERROR_ALREADY_CONNECTED:
					case ERROR_CREATE_THREAD_FAIL:
						EndDialog(hwndDlg, result);
						break;
						
					case 0:
					case ERROR_ALREADY_WORKING:
						break;
				}
			};
			break;
			
		case SUCCESS_LOCATE_SERVERS:
			{
				HWND hLV = GetDlgItem(hwndDlg, IDC_SERVERS_LIST);
				
				ListView_DeleteAllItems(hLV);
				
				LVITEM lvItem = {0};
				lvItem.mask = LVIF_TEXT;
				
				if (client->GetServerCount() == 0) {
					lvItem.iItem = ListView_GetItemCount(hLV);
					lvItem.iSubItem = 0;
					lvItem.pszText = TEXT(TEXT_NOSERVERS);
					ListView_InsertItem(hLV, &lvItem);
					
					HWND hBtn = GetDlgItem(hwndDlg, IDC_OK);
					EnableWindow(hBtn, FALSE);
				}
				else {
					for (unsigned int i = 0; i < client->GetServerCount(); i++) {
						lvItem.iItem = ListView_GetItemCount(hLV);
						lvItem.iSubItem = 0;
						lvItem.pszText = client->GetServerNick(i);
						ListView_InsertItem(hLV, &lvItem);
						
						lvItem.iSubItem = 1;
						lvItem.pszText = client->GetServerPCName(i);
						ListView_SetItem(hLV, &lvItem);
						
						lvItem.iSubItem = 2;
						lvItem.pszText = client->GetServerIPAddr(i);
						ListView_SetItem(hLV, &lvItem);
					}
					
					HWND hBtn = GetDlgItem(hwndDlg, IDC_OK);
					EnableWindow(hBtn, TRUE);
				}
			};
			break;
			
		case WM_COMMAND:
			{
				switch (LOWORD(wParam)) {
					case IDC_UPDATE:
						{
							HWND hLV = GetDlgItem(hwndDlg, IDC_SERVERS_LIST);
							
							ListView_DeleteAllItems(hLV);
							
							HWND hBtn = GetDlgItem(hwndDlg, IDC_OK);
							EnableWindow(hBtn, FALSE);
							
							int result = client->LocateServers(hwndDlg);
							switch (result) {
								case ERROR_NOTINITED:
								case ERROR_ALREADY_CONNECTED:
								case ERROR_CREATE_THREAD_FAIL:
									EndDialog(hwndDlg, result);
									break;
									
								case 0:
								case ERROR_ALREADY_WORKING:
									break;
							}
						};
						break;
						
					case IDC_OK:
						{
							HWND hLV = GetDlgItem(hwndDlg, IDC_SERVERS_LIST);
							
							int selected = ListView_GetNextItem(hLV, -1, LVNI_SELECTED);
							
							int result = client->ConnectToServer(selected);
							
							EndDialog(hwndDlg, result);
						};
						break;
						
					case IDC_CANCEL:
						EndDialog(hwndDlg, -1);
						break;
						
					default:
						return DefWindowProc(hwndDlg, uMsg, wParam, lParam);
				}
			};
			break;
			
		case WM_CLOSE:
			EndDialog(hwndDlg, -1);
			break;
			
		default:
			return DefWindowProc(hwndDlg, uMsg, wParam, lParam);
	}
	
	return 0;
};