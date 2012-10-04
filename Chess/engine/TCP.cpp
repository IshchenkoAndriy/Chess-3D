#include "TCP.h"

TCP::TCP(HWND hWnd, LPCTSTR Name) {
	int result = 0;
	WSAData tmpWSAData = {0};
	
	hSendWnd = hWnd;
	hReceiveDataThread = NULL;
	
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_port = htons(PORT);
	connect_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bIsInited = true;
	bIsWorking = false;
	bIsConnected = false;
	
	result = WSAStartup(MAKEWORD(2, 2), &tmpWSAData);
	if (result) {
		bIsInited = false;
		ErrorHandler(INVALID_SOCKET, result, TEXT("WSAStartup fail!"));;
	}
	
	result = _tcscpy_s(Nick, STR_SIZE, Name);
	if (result == ERANGE) {
		bIsInited = false;
	}
	
	#ifdef UNICODE
		size_t converted = 0;
		char* tmpPCName = new char[STR_SIZE];
		
		if (gethostname(tmpPCName, STR_SIZE) == SOCKET_ERROR) {
			bIsInited = false;
			ErrorHandler(INVALID_SOCKET, WSAGetLastError(), TEXT("gethostname fail!"));
		}
		else {
			mbstowcs_s(&converted, PCName, STR_SIZE, tmpPCName, _TRUNCATE);
		}
		
		delete[] tmpPCName;
	#else
		if (gethostname(PCName, STR_SIZE) == SOCKET_ERROR) {
			bIsInited = false;
			ErrorHandler(INVALID_SOCKET, WSAGetLastError(), TEXT("gethostname fail!"));
		}
	#endif
};

TCP::~TCP() {
	Disconnect();
	WaitForSingleObject(hReceiveDataThread, INFINITE);
	bIsInited = false;
	WSACleanup();
};

LPTSTR TCP::GetNick() {
	csTCP.Enter();
	if (bIsInited) {
		LPTSTR tmpNick = new TCHAR[STR_SIZE];
		_tcscpy_s(tmpNick, STR_SIZE, Nick);
		
		csTCP.Leave();
		return tmpNick;
	}
	else {
		csTCP.Leave();
		return NULL;
	}
};

LPTSTR TCP::GetPCName() {
	csTCP.Enter();
	if (bIsInited) {
		LPTSTR tmpPCName = new TCHAR[STR_SIZE];
		_tcscpy_s(tmpPCName, STR_SIZE, PCName);
		
		csTCP.Leave();
		return tmpPCName;
	}
	else {
		csTCP.Leave();
		return NULL;
	}
};

LPTSTR TCP::GetOppNick() {
	csTCP.Enter();
	if (bIsConnected) {
		LPTSTR tmpOppNick = new TCHAR[STR_SIZE];
		_tcscpy_s(tmpOppNick, STR_SIZE, oppNick);
		
		csTCP.Leave();
		return tmpOppNick;
	}
	else {
		csTCP.Leave();
		return NULL;
	}
};

LPTSTR TCP::GetOppPCName() {
	csTCP.Enter();
	if (bIsConnected) {
		LPTSTR tmpOppPCName = new TCHAR[STR_SIZE];
		_tcscpy_s(tmpOppPCName, STR_SIZE, oppPCName);
		
		csTCP.Leave();
		return tmpOppPCName;
	}
	else {
		csTCP.Leave();
		return NULL;
	}
};

void CALLBACK TCP::GetReceiveDataThread(LPVOID p) {
	((TCP*)p)->ReceiveDataThread();
};

bool TCP::ReceiveData() {
	hReceiveDataThread = CreateThread(
		NULL, 0,
		(LPTHREAD_START_ROUTINE)GetReceiveDataThread, (LPVOID)this,
		0, NULL
	);
	
	if (hReceiveDataThread == NULL) {
		return false;
	}
	
	return true;
};

void TCP::ReceiveDataThread() {
	csIsWorking.Enter();
	bIsWorking = true;
	csIsWorking.Leave();
	
	while (true) {
		ReceivedDataStruct message = {0};
		
		if (recv(TCPSocket, (char*)&message.length, sizeof(int), 0) == SOCKET_ERROR) {
			ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("TCPSocket recv fail!"));
			csIsWorking.Enter();
			bIsWorking = false;
			csIsWorking.Leave();
			return;
		}
		
		message.data = new char[message.length];
		
		if (recv(TCPSocket, message.data, message.length, 0) == SOCKET_ERROR) {
			ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("TCPSocket recv fail!"));
			csIsWorking.Enter();
			bIsWorking = false;
			csIsWorking.Leave();
			return;
		}
		
		csReceivedData.Enter();
		ReceivedData.push(message);
		csReceivedData.Leave();
		
		PostMessage(hSendWnd, SUCCESS_DATA_RECEIVED, NULL, NULL);
	}
};

bool TCP::KeepAlive() {
	BOOL bKeepAlive = TRUE;
	if (setsockopt(TCPSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(BOOL)) == SOCKET_ERROR) {
		ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("KeepAlive setsockopt fail!"));
		return false;
	}
	
	tcp_keepalive alive;
	alive.onoff = 1;
	alive.keepalivetime = ALIVE_TIME;
	alive.keepaliveinterval = 1000;
	
	DWORD bReturned = 0;
	if (WSAIoctl(TCPSocket, SIO_KEEPALIVE_VALS, &alive, sizeof(tcp_keepalive), NULL, 0, &bReturned, NULL, NULL) == SOCKET_ERROR) {
		ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("KeepAlive WSAIoctl fail!"));
		return false;
	}
	
	return true;
};

int TCP::SendData(char* data, int length) {
	csTCP.Enter();
	if (!bIsInited) {
		csTCP.Leave();
		return ERROR_NOTINITED;
	}
	
	if (!bIsConnected) {
		csTCP.Leave();
		return ERROR_NOTCONNECTED;
	}
	csTCP.Leave();
	
	if (length < 1) {
		return ERROR_DATA_IS_TOO_SMALL;
	}
	
	if (send(TCPSocket, (char*)&length, sizeof(int), 0) == SOCKET_ERROR) {
		ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("TCPSocket send fail!"));
		return ERROR_SEND_DATA_FAIL;
	}
	
	if (send(TCPSocket, data, length, 0) == SOCKET_ERROR) {
		ErrorHandler(TCPSocket, WSAGetLastError(), TEXT("TCPSocket send fail!"));
		return ERROR_SEND_DATA_FAIL;
	}
	
	return 0;
};

int TCP::GetData(char*& data, int& length) {
	csTCP.Enter();
	if (!bIsInited) {
		csTCP.Leave();
		return ERROR_NOTINITED;
	}
	
	if (!bIsConnected) {
		csTCP.Leave();
		return ERROR_NOTCONNECTED;
	}
	csTCP.Leave();
	
	csReceivedData.Enter();
	if (ReceivedData.empty()) {
		csReceivedData.Leave();
		return ERROR_QUEUE_IS_EMPTY;
	}
	
	length = ReceivedData.front().length;
	data = new char[length];
	memcpy_s(data, length, ReceivedData.front().data, length);
	delete[] ReceivedData.front().data;
	ReceivedData.pop();
	
	csReceivedData.Leave();
	return 0;
};

void TCP::Disconnect() {
	csTCP.Enter();
	if (bIsConnected) {
		closesocket(TCPSocket);
		bIsConnected = false;
	}
	csTCP.Leave();
};

void TCP::ErrorHandler(SOCKET sock, UINT error, LPCTSTR message) { // Надо дописать
	closesocket(sock);
	
	csTCP.Enter();
	bIsConnected = false;
	csTCP.Leave();
	
	switch(error) {
		case WSAECONNABORTED:
			PostMessage(hSendWnd, ERROR_MESSAGE, (WPARAM)ERROR_CONN_ABORTED, (LPARAM)message);
			break;
			
		case WSAECONNRESET:
			PostMessage(hSendWnd, ERROR_MESSAGE, (WPARAM)ERROR_CONN_ABORTED, (LPARAM)message);
			break;
			
		case WSAECONNREFUSED:
			PostMessage(hSendWnd, ERROR_MESSAGE, (WPARAM)ERROR_CONN_ABORTED, (LPARAM)message);
			break;
			
		default:
			PostMessage(hSendWnd, ERROR_MESSAGE, (WPARAM)error, (LPARAM)message);
			break;
	}
};
