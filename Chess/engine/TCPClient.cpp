#include "TCPClient.h"

TCPClient::TCPClient(HWND hWnd, LPCTSTR Name) : TCP(hWnd, Name) {
	bIsSearching = false;
	bIsConnecting = false;
	hLocateServersThread = NULL;
	hConnectToServerThread = NULL;
};

TCPClient::~TCPClient() {
	WaitForSingleObject(hLocateServersThread, INFINITE);
	WaitForSingleObject(hConnectToServerThread, INFINITE);
};

unsigned int TCPClient::GetServerCount() {
	csIsSearching.Enter();
	unsigned int tmpSize = servers.size();
	csIsSearching.Leave();
	return tmpSize;
};

LPTSTR TCPClient::GetServerNick(unsigned int num) {
	csIsSearching.Enter();
	if (num < servers.size()) {
		LPTSTR tmpNick = new TCHAR[STR_SIZE];
		_tcscpy_s(tmpNick, STR_SIZE, servers[num].Nick);
		
		csIsSearching.Leave();
		return tmpNick;
	}
	else {
		csIsSearching.Leave();
		return NULL;
	}
};

LPTSTR TCPClient::GetServerPCName(unsigned int num) {
	csIsSearching.Enter();
	if (num < servers.size()) {
		LPTSTR tmpPCName = new TCHAR[STR_SIZE];
		_tcscpy_s(tmpPCName, STR_SIZE, servers[num].PCName);
		
		csIsSearching.Leave();
		return tmpPCName;
	}
	else {
		csIsSearching.Leave();
		return NULL;
	}
};

LPTSTR TCPClient::GetServerIPAddr(unsigned int num) {
	csIsSearching.Enter();
	if (num < servers.size()) {
		LPTSTR tmpIPAddr = new TCHAR[STR_SIZE];
		_tcscpy_s(tmpIPAddr, STR_SIZE, servers[num].IPAddr);
		
		csIsSearching.Leave();
		return tmpIPAddr;
	}
	else {
		csIsSearching.Leave();
		return NULL;
	}
};

void CALLBACK TCPClient::GetConnectToServerThread(LPVOID p) {
	((TCPClient*)p)->ConnectToServerThread();
};

int TCPClient::ConnectToServer(unsigned int num) {
	csIsConnecting.Enter();
	if (bIsConnecting) {
		csIsConnecting.Leave();
		return ERROR_ALREADY_WORKING;
	}
	csIsConnecting.Leave();
	
	csTCP.Enter();
	if (!bIsInited) {
		csTCP.Leave();
		return ERROR_NOTINITED;
	}
	
	if (bIsConnected) {
		csTCP.Leave();
		return ERROR_ALREADY_CONNECTED;
	}
	csTCP.Leave();
	
	csIsSearching.Enter();
	if (num >= GetServerCount()) {
		csIsSearching.Leave();
		return ERROR_WRONG_SERVER_NUMBER;
	}
	
	#ifdef UNICODE
		size_t converted = 0;
		char* tmpIP = new char[16];
		wcstombs_s(&converted, tmpIP, 16, GetServerIPAddr(num), _TRUNCATE);
		connect_addr.sin_addr.s_addr = inet_addr(tmpIP);
		delete[] tmpIP;
	#else
		connect_addr.sin_addr.s_addr = inet_addr(GetServerIPAddr(num));
	#endif
	
	csTCP.Enter();
	_tcscpy_s(oppNick, STR_SIZE, servers[num].Nick);
	_tcscpy_s(oppPCName, STR_SIZE, servers[num].PCName);
	csTCP.Leave();
	csIsSearching.Leave();
	
	hConnectToServerThread = CreateThread(
		NULL, 0,
		(LPTHREAD_START_ROUTINE)GetConnectToServerThread, (LPVOID)this,
		0, NULL
	);
	
	if (hConnectToServerThread == NULL) {
		return ERROR_CREATE_THREAD_FAIL;
	}
	
	return 0;
};

void TCPClient::ConnectToServerThread() {
	csIsConnecting.Enter();
	bIsConnecting = true;
	csIsConnecting.Leave();
	
	SOCKET UDPSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (UDPSocket == INVALID_SOCKET) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket create fail!"));
		csIsConnecting.Enter();
		bIsConnecting = false;
		csIsConnecting.Leave();
		return;
	}
	
	UDPPacket answer = {0};
	answer.message = CONNECT_TO_SERVER;
	
	csTCP.Enter();
	_tcscpy_s(answer.nick, STR_SIZE, Nick);
	_tcscpy_s(answer.pcname, STR_SIZE, PCName);
	csTCP.Leave();
	
	if (sendto(UDPSocket, (char*)&answer, sizeof(UDPPacket), 0, (sockaddr*)&connect_addr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket sendto fail!"));
		csIsConnecting.Enter();
		bIsConnecting = false;
		csIsConnecting.Leave();
		return;
	}
	closesocket(UDPSocket);
	
	TCPSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPSocket == INVALID_SOCKET) {
		ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("TCPSocket create fail!"));
		csIsConnecting.Enter();
		bIsConnecting = false;
		csIsConnecting.Leave();
		return;
	}
	
	if (connect(TCPSocket, (sockaddr*)&connect_addr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("TCPSocket connect fail!"));
		csIsConnecting.Enter();
		bIsConnecting = false;
		csIsConnecting.Leave();
		return;
	}
	
	if (!KeepAlive()) {
		csIsConnecting.Enter();
		bIsConnecting = false;
		csIsConnecting.Leave();
		return;
	}
	
	if (!ReceiveData()) {
		ErrorHandler(TCPSocket, ERROR_CREATE_THREAD_FAIL, TEXT("ReceiveDataThread start fail!"));
		csIsConnecting.Enter();
		bIsConnecting = false;
		csIsConnecting.Leave();
		return;
	}
	
	csTCP.Enter();
	bIsConnected = true;
	csTCP.Leave();
	PostMessage(hSendWnd, SUCCESS_CONNECTED, NULL, NULL);
	
	csIsConnecting.Enter();
	bIsConnecting = false;
	csIsConnecting.Leave();
	
	return;
};

void CALLBACK TCPClient::GetLocateServersThread(LPVOID p) {
	((TCPClient*)p)->LocateServersThread();
};

int TCPClient::LocateServers(HWND hWnd) {
	csIsSearching.Enter();
	if (bIsSearching) {
		csIsSearching.Leave();
		return ERROR_ALREADY_WORKING;
	}
	csIsSearching.Leave();
	
	csTCP.Enter();
	if (!bIsInited) {
		csTCP.Leave();
		return ERROR_NOTINITED;
	}
	
	if (bIsConnected) {
		csTCP.Leave();
		return ERROR_ALREADY_CONNECTED;
	}
	csTCP.Leave();
	
	hLocateWnd = hWnd;
	
	hLocateServersThread = CreateThread(
		NULL, 0,
		(LPTHREAD_START_ROUTINE)GetLocateServersThread, (LPVOID)this,
		0, NULL
	);
	
	if (hLocateServersThread == NULL) {
		return ERROR_CREATE_THREAD_FAIL;
	}
	
	return 0;
};

void TCPClient::LocateServersThread() {
	csIsSearching.Enter();
	servers.clear();
	bIsSearching = true;
	csIsSearching.Leave();
	
	SOCKET UDPSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (UDPSocket == INVALID_SOCKET) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket create fail!"));
		csIsSearching.Enter();
		bIsSearching = false;
		csIsSearching.Leave();
		return;
	}
	
	BOOL bBroadcast = TRUE;
	if (setsockopt(UDPSocket, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(BOOL)) == SOCKET_ERROR) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket setsockopt fail!"));
		csIsSearching.Enter();
		bIsSearching = false;
		csIsSearching.Leave();
		return;
	}
	
	sockaddr_in udp_addr = {0};
	udp_addr.sin_family = AF_INET;
	udp_addr.sin_port = htons(PORT);
	udp_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	
	UDPPacket answer = {0};
	answer.message = LOCATE_SERVER;
	
	if (sendto(UDPSocket, (char*)&answer, sizeof(UDPPacket), 0, (sockaddr*)&udp_addr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket sendto fail!"));
		csIsSearching.Enter();
		bIsSearching = false;
		csIsSearching.Leave();
		return;
	}
	
	DWORD dwTime = LOCATE_TIME;
	if (setsockopt(UDPSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&dwTime, sizeof(DWORD)) == SOCKET_ERROR) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket setsockopt fail!"));
		csIsSearching.Enter();
		bIsSearching = false;
		csIsSearching.Leave();
		return;
	}
	
	while (true) {
		sockaddr_in server_addr = {0};
		int server_addr_size = sizeof(sockaddr_in);
		UDPPacket packet = {0};
		
		if (recvfrom(UDPSocket, (char*)&packet, sizeof(UDPPacket), 0, (sockaddr*)&server_addr, &server_addr_size) == SOCKET_ERROR) {
			UINT error = WSAGetLastError();
			if (error == WSAETIMEDOUT) {
				closesocket(UDPSocket);
				break;
			}
			else {
				ErrorHandler(UDPSocket, error, TEXT("UDPSocket recvfrom fail!"));
				csIsSearching.Enter();
				bIsSearching = false;
				csIsSearching.Leave();
				return;
			}
		}
		
		if (packet.message == CONFIRM_SERVER) {
			Server server = {0};
			
			#ifdef UNICODE
				size_t converted = 0;
				char* tmpIPAddr = inet_ntoa(server_addr.sin_addr);
				mbstowcs_s(&converted, server.IPAddr, 16, tmpIPAddr, _TRUNCATE);
			#else
				strcpy_s(server.IPAddr, 16, inet_ntoa(server_addr.sin_addr));
			#endif
			
			_tcscpy_s(server.Nick, STR_SIZE, packet.nick);
			_tcscpy_s(server.PCName, STR_SIZE, packet.pcname);
			
			csIsSearching.Enter();
			servers.push_back(server);
			csIsSearching.Leave();
		}
	}
	
	PostMessage(hLocateWnd, SUCCESS_LOCATE_SERVERS, NULL, NULL);
	
	csIsSearching.Enter();
	bIsSearching = false;
	csIsSearching.Leave();
	
	return;
};
