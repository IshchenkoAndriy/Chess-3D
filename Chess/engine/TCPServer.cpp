#include "TCPServer.h"

TCPServer::TCPServer(HWND hWnd, LPCTSTR Name) : TCP(hWnd, Name) {
	bStopWait = false;
	bIsWaiting = false;
	hWaitForClientThread = NULL;
};

TCPServer::~TCPServer() {
	StopWait();
	WaitForSingleObject(hWaitForClientThread, INFINITE);
};

void TCPServer::StopWait() {
	csStopWait.Enter();
	bStopWait = true;
	csStopWait.Leave();
};

void CALLBACK TCPServer::GetWaitForClientThread(LPVOID p) {
	((TCPServer*)p)->WaitForClientThread();
};

int TCPServer::WaitForClient() {
	csIsWaiting.Enter();
	if (bIsWaiting) {
		csIsWaiting.Leave();
		return ERROR_ALREADY_WORKING;
	}
	csIsWaiting.Leave();
	
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
	
	hWaitForClientThread = CreateThread(
		NULL, 0,
		(LPTHREAD_START_ROUTINE)GetWaitForClientThread, (LPVOID)this,
		0, NULL
	);
	
	if (hWaitForClientThread == NULL) {
		return ERROR_CREATE_THREAD_FAIL;
	}
	
	return 0;
};

void TCPServer::WaitForClientThread() {
	csIsWaiting.Enter();
	bIsWaiting = true;
	csIsWaiting.Leave();
	
	SOCKET UDPSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (UDPSocket == INVALID_SOCKET) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket create fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	sockaddr_in udp_addr = {0};
	udp_addr.sin_family = AF_INET;
	udp_addr.sin_port = htons(PORT);
	udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(UDPSocket, (sockaddr*)&udp_addr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket bind fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("WSACreateEvent fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	if (WSAEventSelect(UDPSocket, hEvent, FD_READ) == SOCKET_ERROR) {
		ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("WSAEventSelect fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	csStopWait.Enter();
	bStopWait = false;
	csStopWait.Leave();
	
	while (true) {
		DWORD result = WSAWaitForMultipleEvents(1, &hEvent, FALSE, 500, FALSE);
		if (result == WSA_WAIT_FAILED) {
			ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("WSAWaitForMultipleEvents fail!"));
			csIsWaiting.Enter();
			bIsWaiting = false;
			csIsWaiting.Leave();
			return;
		}
		
		csStopWait.Enter();
		if (bStopWait) {
			csStopWait.Leave();
			closesocket(UDPSocket);
			csIsWaiting.Enter();
			bIsWaiting = false;
			csIsWaiting.Leave();
			return;
		}
		csStopWait.Leave();
		
		if (result == WSA_WAIT_TIMEOUT) {
			continue;
		}
		
		WSANETWORKEVENTS netEvents = {0};
		if (WSAEnumNetworkEvents(UDPSocket, hEvent, &netEvents) == SOCKET_ERROR) {
			ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("WSAWaitForMultipleEvents fail!"));
			csIsWaiting.Enter();
			bIsWaiting = false;
			csIsWaiting.Leave();
			return;
		}
		
		if (netEvents.iErrorCode[FD_READ]) {
			ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("iErrorCode FD_READ fail!"));
			csIsWaiting.Enter();
			bIsWaiting = false;
			csIsWaiting.Leave();
			return;
		}
		
		sockaddr_in client_addr = {0};
		int client_addr_size = sizeof(sockaddr_in);
		UDPPacket packet = {0};
		
		if (recvfrom(UDPSocket, (char*)&packet, sizeof(UDPPacket), 0, (sockaddr*)&client_addr, &client_addr_size) == SOCKET_ERROR) {
			ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket recvfrom fail!"));
			csIsWaiting.Enter();
			bIsWaiting = false;
			csIsWaiting.Leave();
			return;
		}
		
		if (packet.message == LOCATE_SERVER) {
			UDPPacket answer = {0};
			answer.message = CONFIRM_SERVER;
			
			csTCP.Enter();
			_tcscpy_s(answer.nick, STR_SIZE, Nick);
			_tcscpy_s(answer.pcname, STR_SIZE, PCName);
			csTCP.Leave();
			
			if (sendto(UDPSocket, (char*)&answer, sizeof(UDPPacket), 0, (sockaddr*)&client_addr, client_addr_size) == SOCKET_ERROR) {
				ErrorHandler(UDPSocket, WSAGetLastError(), TEXT("UDPSocket sendto fail!"));
				csIsWaiting.Enter();
				bIsWaiting = false;
				csIsWaiting.Leave();
				return;
			}
			
			continue;
		}
		
		if (packet.message == CONNECT_TO_SERVER) {
			csTCP.Enter();
			_tcscpy_s(oppNick, STR_SIZE, packet.nick);
			_tcscpy_s(oppPCName, STR_SIZE, packet.pcname);
			csTCP.Leave();
			
			closesocket(UDPSocket);
			break;
		}
	}
	
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET) {
		ErrorHandler(listenSocket, WSAGetLastError(), TEXT("listenSocket create fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	sockaddr_in listen_addr = {0};
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(PORT);
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(listenSocket, (sockaddr*)&listen_addr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		ErrorHandler(listenSocket, WSAGetLastError(), TEXT("listenSocket bind fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	if (listen(listenSocket, 1) == SOCKET_ERROR) {
		ErrorHandler(listenSocket, WSAGetLastError(), TEXT("listenSocket listen fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	int connect_addr_size = sizeof(sockaddr_in);
	TCPSocket = accept(listenSocket, (sockaddr*)&connect_addr, &connect_addr_size);
	closesocket(listenSocket);
	if (TCPSocket == INVALID_SOCKET) {
		ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("listenSocket accept fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	if (!KeepAlive()) {
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	if (!ReceiveData()) {
		ErrorHandler(TCPSocket, ERROR_CREATE_THREAD_FAIL, TEXT("ReceiveDataThread start fail!"));
		csIsWaiting.Enter();
		bIsWaiting = false;
		csIsWaiting.Leave();
		return;
	}
	
	csTCP.Enter();
	bIsConnected = true;
	csTCP.Leave();
	PostMessage(hSendWnd, SUCCESS_CONNECTED, NULL, NULL);
	
	csIsWaiting.Enter();
	bIsWaiting = false;
	csIsWaiting.Leave();
	
	return;
};
