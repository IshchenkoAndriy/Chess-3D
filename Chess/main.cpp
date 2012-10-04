/******************************************************************************************************
*
*	��� "����"				������� ������				���������: "����� ���"					2011
*	������, ���� ������ ����������� �������� �� ��������� ���
*
*******************************************************************************************************/

// ϳ������� ���������� �����
#include "engine\\TCP.h"
#include "engine\\TCPServer.h"
#include "engine\\TCPClient.h"

#include "engine\\engine.h"														// ������������ ���� ��� Direct3D9
#include "resource.h"
#include "game.cpp"																// �������� ���� ���
#include "hint.cpp"
#include "about.cpp"															// ����� "� �������"
#include "ListView.cpp"															// ����� ������ ������� ��� ����������
#include "CLWindow.cpp"															// ����-������ ��� ������: ���, ������� ��� ����� � �.�.
#include "title_layer.h"														// ������ ��������

#define ENABLE_MENU_ITEM(HANDLE, ID) EnableMenuItem(GetMenu(HANDLE), ID, MF_ENABLED)
#define DISABLE_MENU_ITEM(HANDLE, ID) EnableMenuItem(GetMenu(HANDLE), ID, MF_GRAYED)

#define ID_LOCAL_GAME		WM_APP + 1
#define ID_NET_SERVER		WM_APP + 2
#define ID_NET_CLIENT		WM_APP + 3
#define ID_WHITE_THEME		WM_APP + 4
#define ID_COLORED_THEME	WM_APP + 5

#define WINDOW_DEFAULT_WIDHT	860												// ������ �볺������ ������ ����
#define WINDOW_DEFAULT_HEIGHT	645												// ������ �볺������ ������ ����

#define ID_LAYER_GAME	1														// �������������� ����
#define ID_LAYER_TITLE	2

Engine *Render = NULL;
Hint *hint = NULL;
About *about;

std::vector<CLButton> buttons;
std::vector<CLButton> themeButtons;
CLWindow *selectGame;

Layer *game = NULL;
Layer *title = NULL;

TCPClient *client = NULL;
TCPServer *server = NULL;

// ϳ��������� ��� ������������ ���� � ��������� ����� ����� � �������
void EnableWindowSizing(HWND hWnd, bool sizing = true){
	
	int shift = 4;

	if(sizing){
		SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) | (WS_MAXIMIZEBOX | WS_SIZEBOX));
			
		RECT rect, windowRect;
		GetWindowRect(hWnd, &windowRect);
		GetClientRect(hWnd, &rect);

		AdjustWindowRectEx(&rect, GetWindowLong(hWnd, GWL_STYLE), true, GetWindowLong(hWnd, GWL_EXSTYLE));
		
		SetWindowPos(hWnd, 
						HWND_NOTOPMOST, 
						windowRect.left - shift, 
						windowRect.top - shift, 
						rect.right - rect.left, 
						rect.bottom - rect.top, 
						SWP_FRAMECHANGED);

	}
	else{
		SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~(WS_MAXIMIZEBOX | WS_SIZEBOX));
				
		RECT rect, windowRect;
		GetWindowRect(hWnd, &windowRect);
		GetClientRect(hWnd, &rect);

		AdjustWindowRectEx(&rect, GetWindowLong(hWnd, GWL_STYLE), true, GetWindowLong(hWnd, GWL_EXSTYLE));
		SetWindowPos(hWnd, 
						HWND_NOTOPMOST, 
						windowRect.left + shift, 
						windowRect.top + shift, 
						rect.right - rect.left, 
						rect.bottom - rect.top, 
						SWP_FRAMECHANGED);
	}
};

// ϳ��������� ������� ����������
LRESULT  WINAPI  MsgProc(HWND hWnd,			// ���������� ����
						 UINT msg,			// �����������
						 WPARAM wParam,		// ��������� �����������
						 LPARAM lParam)		// ��������� �����������
{
	switch (msg)																// ������� ����������
	{
		case WM_SYSCOMMAND:														// ������������ ������� �������
			{
				switch (wParam)
				{
					case SC_SCREENSAVE:											// ����������� ��������� �����������
					case SC_MONITORPOWER:										// ��� ����������� ������� � ����� ���������������
					return 0;
				}
				break;
			}

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			
			case ID_GAME_NEW:													// �������� ����� "���� ���"
				{
				UINT gameType;

				Render->BeforeFreezing();
				selectGame = new CLWindow(hWnd, NULL);
				gameType = selectGame->Show(TEXT("������� ��� ���"), buttons, true, 300);
				delete selectGame;
				Render->AfterFreezing();

				switch (gameType) {												// �������� ���� �����������
					case ID_LOCAL_GAME:
					case ID_NET_SERVER:
					case ID_NET_CLIENT:
						{
							
							if(game != NULL){	// ���� ��� ��������, �� �������� ��� ���������� ������� ���
								UINT endGame = Render->GetParameter(ID_LAYER_GAME, GAME_END);
								if(endGame != GAME_YES){						// � ������� ���� ���� �����������
									UINT endGame = MessageBox(hWnd, 
														TEXT("��������� ������� ���?"),
														TEXT("�������"),
														MB_YESNO);

									if(endGame == IDYES){
										DISABLE_MENU_ITEM(hWnd, ID_CHANGE_THEME);
										Render->EnableLayer(ID_LAYER_TITLE);
										Render->ResetAnimation();
										Render->UnregisterLayerID(ID_LAYER_GAME);
										Render->SetParameter(ID_LAYER_TITLE, ID_LOADING_TEXT, TEXT_ENABLE);
										Render->Rendering();
						
										delete game;
										game = NULL;

										// �������, ���� ��� ��������� �볺� ��� ������

										Render->EnableLayer(ID_LAYER_TITLE);
										if(server != NULL) {
											delete server;
											server = NULL;
										}

										if(client != NULL) {
											delete client;
											client = NULL;
										}
					
										// �������� ����������� ��� ��������� �������� ���
										SendMessage(hWnd, WM_COMMAND, gameType, NULL);
									}
								}
								else{
									DISABLE_MENU_ITEM(hWnd, ID_CHANGE_THEME);
									Render->EnableLayer(ID_LAYER_TITLE);
									Render->ResetAnimation();
									Render->UnregisterLayerID(ID_LAYER_GAME);
									Render->SetParameter(ID_LAYER_TITLE, ID_LOADING_TEXT, TEXT_ENABLE);
									Render->Rendering();
						
									delete game;
									game = NULL;

									Render->EnableLayer(ID_LAYER_TITLE);
									if(server != NULL) {
										delete server;
										server = NULL;
									}

									if(client != NULL) {
										delete client;
										client = NULL;
									}
					
									SendMessage(hWnd, WM_COMMAND, gameType, NULL);
							}
							}
							else{
								if(server == NULL && client == NULL) {			// ���� ������ ������
									EnableWindowSizing(hWnd, true);				// ������������ ����
								}
								else{
									if(server != NULL) {
										delete server;
										server = NULL;
									}

									if(client != NULL) {
										delete client;
										client = NULL;
									}
								}
								Render->ResetAnimation();
								SendMessage(hWnd, WM_COMMAND, gameType, NULL);
							}
							break;
					}
								
						default:
							break;
					}
				}
				break;

			case ID_CHANGE_THEME:												// ������� ������ ���� "������ ����"
				if(game != NULL){
					Render->BeforeFreezing();
					selectGame = new CLWindow(hWnd, NULL);
					UINT themeType = selectGame->Show(TEXT("������� ����"), themeButtons, true, 300);
					delete selectGame;
					Render->AfterFreezing();

					switch (themeType) {										// �������� ������� �����������
						case ID_WHITE_THEME:									// ������� � ����, �������� ����
							game->SetParameter(GAME_CHANGE_THEME, THEME_WHITE);
							break;
								
						case ID_COLORED_THEME:
							game->SetParameter(GAME_CHANGE_THEME, THEME_COLORED);
							break;
								
						default:
							break;
					}
				}
				break;

			case ID_GAME_EXIT:													// ������� ������ ��� "�����"
				SendMessage(hWnd, WM_CLOSE, NULL, NULL);	// �������� ����������� ��� ����������
				break;
					
			case ID_HELP_URL:													// ������� ������ ���� "��������"
				// ³�������� ����������� ��������� ���� ³����� �� ������� �����
				ShellExecute(NULL, TEXT("open"), TEXT("http://ru.wikipedia.org/wiki/%D0%A8%D0%B0%D1%85%D0%BC%D0%B0%D1%82%D1%8B"), NULL, NULL, SW_SHOWNORMAL);
				break;
					
			case ID_HELP_ABOUT:													// ������� ������ ��� "��� ��������"
				Render->BeforeFreezing();
				about = new About(hWnd, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE));
				about->Show();													// �������� �������� �����
				delete about;
				Render->AfterFreezing();
				break;

			case ID_LOCAL_GAME:													// ������� ��������� �������� ���
				Render->SetParameter(ID_LAYER_TITLE, ID_LOADING_TEXT, TEXT_ENABLE);
				Render->Rendering();											// �������� ������ �� ��� ��� ������������

				game = new LocalChessGame(Render->Get3DDevice(), hWnd);			// ��������� ���
				Render->SetParameter(ID_LAYER_TITLE, ID_LOADING_TEXT, TEXT_DISABLE);
				Render->DisableLayer(ID_LAYER_TITLE);
				Render->RegisterLayer(game, ID_LAYER_GAME);						// �������� ���� � ������ ������
				Render->Rendering();

				ENABLE_MENU_ITEM(hWnd, ID_CHANGE_THEME);						// �������� ����� ���� "������ ����"
				break;
								
			case ID_NET_SERVER:													// ��������� �������� ���, �������
				{
					
					Render->SetParameter(ID_LAYER_TITLE, ID_WAITING_TEXT, TEXT_ENABLE);
					Render->Rendering();

					server = new TCPServer(hWnd, TEXT("Server"));				// ��������� ��'��� ������

					int result = server->WaitForClient();						// ���������� � ������� �볺���

					switch (result) {											// ������� �������
						case ERROR_NOTINITED:
							MessageBox(hWnd, TEXT("��������� ������������ �����"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
								
						case ERROR_ALREADY_WORKING:
							MessageBox(hWnd, TEXT("��������� ������ �������"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
								
						case ERROR_ALREADY_CONNECTED:
							MessageBox(hWnd, TEXT("������ ��� ��������� �'�������"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
							
						case ERROR_CREATE_THREAD_FAIL:
							MessageBox(hWnd, TEXT("��������� ������������ ������"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
						case 0:
							break;
					}
				}
				break;
								
			case ID_NET_CLIENT:													// ��������� �������� ���, �볺���
				{
					Render->SetParameter(ID_LAYER_TITLE, ID_SEARCH_TEXT, TEXT_ENABLE);
					Render->Rendering();
						
					client = new TCPClient(hWnd, TEXT("Client"));				// ��������� ��'��� �볺��
					
					// �������� �������� ����, ��� ������ � �������� ������� �������
					int result = DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_SERVER_SELECT), hWnd, DlgProc, (LPARAM)client);

					ShowWindow(hWnd, SW_SHOWNORMAL);							// �������� ����
					SetFocus(hWnd);												// ������������ �����
					UpdateWindow(hWnd);											// ��������� ����

					switch (result) {											// �������� ��������� ���������� �����(�볺������� ��������)
						case ERROR_NOTINITED:
							MessageBox(hWnd, TEXT("��������� ������������ �����"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
								
						case ERROR_ALREADY_WORKING:
							MessageBox(hWnd, TEXT("��������� ������ �볺���"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
								
						case ERROR_ALREADY_CONNECTED:
							MessageBox(hWnd, TEXT("�볺�� ��� ��������� �'�������"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
								
						case ERROR_CREATE_THREAD_FAIL:
							MessageBox(hWnd, TEXT("��������� ������������ �볺��"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
								
						case ERROR_WRONG_SERVER_NUMBER:
							MessageBox(hWnd, TEXT("�������� ������� ����� �������"), TEXT("�������"), MB_OK);
							DestroyWindow(hWnd);
							break;
								
						case 0:
							break;
								
						case -1:
							DISABLE_MENU_ITEM(hWnd, ID_CHANGE_THEME);
							break;
					}
					Render->SetParameter(ID_LAYER_TITLE, ID_SEARCH_TEXT, TEXT_DISABLE);
				}
				break;
					
			default:															// ������� ���������� �� �������������			
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

		// ����������� ���������
		case WM_KEYDOWN:														// ���� ��������� ������
			if (LOWORD(wParam) == VK_F1) {
				ShellExecute(NULL, TEXT("open"), TEXT("http://ru.wikipedia.org/wiki/%D0%A8%D0%B0%D1%85%D0%BC%D0%B0%D1%82%D1%8B"), NULL, NULL, SW_SHOWNORMAL);
			}
			Render->KeyDown(wParam);											// �������� ��� ������ �� �������
			return 0;

		case WM_KEYUP:															// ���� �������� ������
			Render->KeyUp(wParam);
			return 0;
		
		// ����������� �����
		case WM_LBUTTONDOWN:
			Render->LBtnDown(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_LBUTTONUP:
			Render->LBtnUp(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_LBUTTONDBLCLK:
			Render->LBtnDblClk(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_RBUTTONDOWN:
			Render->RBtnDown(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_RBUTTONUP:
			Render->RBtnUp(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_RBUTTONDBLCLK:
			Render->RBtnDblClk(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_MOUSEMOVE:
			Render->MouseMove(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_MOUSEWHEEL:
			// wParam ������ ������� �������� �����
			Render->Wheel(GET_WHEEL_DELTA_WPARAM(wParam));
			return 0;
		
		case WM_ACTIVATE:
			// wParam � WA_ACTIVE ��� WA_INACTIVE ������������ ����
			Render->WindowActive(LOWORD(wParam));
			return 0;

		case WM_SIZE:															// ������� ����������� ���� ����
			Render->ResizeScene(LOWORD(lParam), HIWORD(lParam));				// ������� ��������� ����� � ��� � ������������� �������
			Render->Resize(LOWORD(lParam), HIWORD(lParam));						// �������� ����������� ����� ��� ���� ������ �����
			Render->Timer(GetTickCount());										// ������ ����������� �������� ���
			Render->Rendering();
			return 0;
			
		case WM_WINDOWPOSCHANGED:												// ������� ����������� ���� ������� ����
			if(hint != NULL) hint->Update();									// ������� ��������� �������, ���� ���� �������
			Render->BeforeFreezing();
			return DefWindowProc(hWnd, msg, wParam, lParam);

		case WM_ENTERMENULOOP:													// ������� ������� ����� ����������� ����
			Render->BeforeFreezing();											// �������� ����������� ����� "����������" �����
			return 0;
		
		case WM_EXITSIZEMOVE:													// ������� ���������� ����
			Render->AfterFreezing();											// �������� ����������� ����� ���������� ������
			return DefWindowProc(hWnd, msg, wParam, lParam);

		case WM_EXITMENULOOP:													// ������� ������� ���� ������ � ����
			Render->AfterFreezing();
			return 0;
	
		case SUCCESS_CONNECTED:													// ������� ����������� �� ������� ��� �볺��� ��� ������
			{																	// ������������ �'�������
					
				Render->DisableLayer(ID_LAYER_TITLE);							// �������� ���
				Render->SetParameter(ID_LAYER_TITLE, ID_WAITING_TEXT, TEXT_DISABLE);
				Render->SetParameter(ID_LAYER_TITLE, ID_SEARCH_TEXT, TEXT_DISABLE);
				
				Render->ResetAnimation();										// ������� ������ �������
				game = new NetChessGame(Render->Get3DDevice(), hWnd, (client == NULL)? WHITE : BLACK);
				Render->RegisterLayer(game, ID_LAYER_GAME);
				Render->Rendering();
				ENABLE_MENU_ITEM(hWnd, ID_CHANGE_THEME);						// ���������� ������ ���� "������ ����"
			};
			break;
			
		case SUCCESS_DATA_RECEIVED:												// ������� ����������� ��� ������� ������ ������
			{
				int len = 0;
				char* mes = NULL;
				
				if(client != NULL){												// ��������� "���" ������� ����
					if (client->GetData(mes, len) != ERROR_QUEUE_IS_EMPTY) {	// ������� ����
						Render->SendData(ID_LAYER_GAME, mes, len);				// � �������� ����� �� �������
					}
				}
				else{
					if (server->GetData(mes, len) != ERROR_QUEUE_IS_EMPTY) {
						Render->SendData(ID_LAYER_GAME, mes, len);
					}
				}
				
				delete[] mes;													// ������� �����

			};
			break;
			
		case ERROR_MESSAGE:														// ������� �������

			if (wParam == WSAEADDRINUSE) {										// ���������� �� ������ ����� ��������� ������ �� ���
				MessageBox(hWnd, TEXT("������ ��� ��������� �� ������ ����'����"), TEXT("�������"), MB_OK);
				DestroyWindow(hWnd);

			}
			
			Render->SetParameter(ID_LAYER_GAME, GAME_DISCONNECTION, GAME_YES);	// �������� ����� ����������� ��� �������
			break;
	
		case WM_DESTROY:														// ������� ����������� ��� �������� ��������
		case WM_CLOSE:
		{
			if(game != NULL){
					
				UINT endGame = Render->GetParameter(ID_LAYER_GAME, GAME_END);
				if(endGame != GAME_YES){
					endGame = MessageBox(hWnd, 
										TEXT("��������� ������� ���?"),
										TEXT("�������"),
										MB_YESNO);
					
					if(endGame == IDYES){
						Render->UnregisterLayerID(ID_LAYER_GAME);
						delete game;
						Render->EnableLayer(ID_LAYER_TITLE);
						PostQuitMessage(0);
					}
				}
				else{
					Render->UnregisterLayerID(ID_LAYER_GAME);
					delete game;
					Render->EnableLayer(ID_LAYER_TITLE);
					PostQuitMessage(0);
				}
			}
			else{
				PostQuitMessage(0);
			}
			return 0;
		}
	}
	// ���������� �� ���� ����������� � DefWindowProc
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


// ��������� ����� ��������
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	RECT WindowRect;
	HWND hWnd;	
	WNDCLASSEX wc;
	TCHAR ClassName[] = TEXT("Application");
	TCHAR WindowName[] = TEXT("Chess 3D");
	MSG msg;


	// ��������� ��������
	// ��������� ����� ����
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_DBLCLKS;
	wc.lpfnWndProc		= MsgProc;
	wc.cbClsExtra		= 0L;
	wc.cbWndExtra		= 0L;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));	// ��������� �������� ������ ����
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);									// ��������� ����������� ������
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName	= ClassName;
	wc.hIconSm	        = NULL;

    RegisterClassEx(&wc);															// �������� ���� ����

	DWORD WindowStyle, WindowExStyle;
		
	WindowExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;								// ���������� Window Extended Style
	WindowStyle = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_SIZEBOX);				// ���������� Windows Style

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	WindowRect.left = (long)0;														// ������������ ������� �� X
	WindowRect.right = (long)WINDOW_DEFAULT_WIDHT;									// ������������ ������ 
	WindowRect.top = (long)0;														// ������������ ������� �� �� Y
	WindowRect.bottom = (long)WINDOW_DEFAULT_HEIGHT;								// ������������ ������
	
	AdjustWindowRectEx(&WindowRect, WindowStyle, true, WindowExStyle);				// ���������� ������ �� ������

	int windowWidth = WindowRect.right - WindowRect.left;
	int windowHeight = WindowRect.bottom - WindowRect.top;

	// ������� ����
	if (!(hWnd=CreateWindowEx(	WindowExStyle,										// ���������� ����� ����
								ClassName,											// ��'� �����
								WindowName,											// ��������� �����
								WindowStyle |										// ����� ����
								WS_CLIPSIBLINGS |
								WS_CLIPCHILDREN,
								(screenWidth / 2) - (windowWidth / 2),				// ������� ���� X
								(screenHeight / 2) - (windowHeight / 2),			// ������� ���� Y
								windowWidth,										// ������ ����
								windowHeight,										// ������ ����
								NULL,												// ���� ������������ ����
								NULL,												// ��� ���� (������ ���� �����)
								wc.hInstance,										// ���������� ���������� ��������
								NULL)))												// �������� �� ��� ��������� ����
	{
		MessageBox(NULL, TEXT("��������� �������� ����!"), TEXT("�������"), MB_OK | MB_ICONEXCLAMATION);
		return 1;
	}

	CLButton button;																// ���������� �������� ������

	button.BtnID = ID_LOCAL_GAME;
	button.BtnText = TEXT("��������� �������� ���");
	button.BtnNote = TEXT("��� ��� ���� ������� �� ������ ����'�����: ���� ��� �� ����, ����� �� ������");
	button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_LOCAL_GAME));
	buttons.push_back(button);

	button.BtnID = ID_NET_SERVER;
	button.BtnText = TEXT("�������� �������� ���");
	button.BtnNote = TEXT("��� ��� ���� ������� ����� ������: �� ����� �� ����, �������� �� ������");
	button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_NET_SERVER));
	buttons.push_back(button);

	button.BtnID = ID_NET_CLIENT;
	button.BtnText = TEXT("ϳ���������� �� �������� ���");
	button.BtnNote = TEXT("��� ��� ���� ������� ����� ������: �� ����� �� ������, �������� �� ����");
	button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_NET_CLIENT));
	buttons.push_back(button);

	button.BtnID = ID_WHITE_THEME;
	button.BtnText = TEXT("���� ����");
	button.BtnNote = TEXT("");
	button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_WHITE_THEME));
	themeButtons.push_back(button);

	button.BtnID = ID_COLORED_THEME;
	button.BtnText = TEXT("��������� ����");
	button.BtnNote = TEXT("");
	button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_COLORED_THEME));
	themeButtons.push_back(button);

	hint = new Hint(hWnd, hInst);														// ��������� ��'��� �������

	try{

		Render = new Engine(hWnd);														// ��������� �������
		Render->Init();																	// ����������� Direct3D
		
		title = new Title(Render->Get3DDevice(), hWnd);
		Render->RegisterLayer(title, ID_LAYER_TITLE);

		Render->BeforeFreezing();

		ShowWindow(hWnd, SW_SHOWNORMAL);												// �������� ����
		SetFocus(hWnd);																	// ������������ �����
		UpdateWindow(hWnd);																// ��������� ����
		SetForegroundWindow(hWnd);														// ϳ������� ��������

		Render->AfterFreezing();

		DISABLE_MENU_ITEM(hWnd, ID_CHANGE_THEME);

		// �������� �������� ������ ����������
		do{
			if(Render->IsAnimated()){													// ���� ��������� ��'����(������) �� ����
				if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				Render->Timer(GetTickCount());											// ���������� ����� �������� ��'����
				Render->Rendering();													// ��������� �����
			}
			else{
				if(GetMessage(&msg, NULL, 0, 0)){										// �������� ��� ����������
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					Render->Rendering();
				}
			}
		}while(msg.message != WM_QUIT);
					
		Render->Destroy();																// ������� ������

		Render->UnregisterLayerID(ID_LAYER_TITLE);
		
		delete title;

		delete Render;																	// ��������� �������
	}
	catch(EngineException &e){
		MessageBox(hWnd, e.what(), TEXT("�������"), MB_OK | MB_ICONEXCLAMATION);
	}
	
	UnregisterClass(ClassName, wc.hInstance);
    
	return 0;
}