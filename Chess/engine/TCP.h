#ifndef _TCP_H_
#define _TCP_H_

#include <queue>
#include <tchar.h>
#include <winsock2.h>
#include <mstcpip.h>
#include <windows.h>

#include "CritSect.h"

#pragma comment (lib, "ws2_32.lib")
//#pragma comment (lib, "mswsock.lib")

#define STR_SIZE						64
#define PORT							12870
#define LOCATE_TIME						3000
#define ALIVE_TIME						60000

#define LOCATE_SERVER					2010
#define CONFIRM_SERVER					2020
#define CONNECT_TO_SERVER				2030

#define ERROR_MESSAGE					WM_APP + 10
#define SUCCESS_CONNECTED				WM_APP + 11
#define SUCCESS_LOCATE_SERVERS			WM_APP + 12
#define SUCCESS_DATA_RECEIVED			WM_APP + 13

#define ERROR_CONN_ABORTED				7001
#define ERROR_UNKNOWN					7002

#define ERROR_NOTINITED					13001
#define ERROR_NOTCONNECTED				13002
#define ERROR_ALREADY_WORKING			13003
#define ERROR_ALREADY_CONNECTED			13004
#define ERROR_CREATE_THREAD_FAIL		13005
#define ERROR_SEND_DATA_FAIL			13006
#define ERROR_WRONG_SERVER_NUMBER		13007
#define ERROR_DATA_IS_TOO_SMALL			13008
#define ERROR_QUEUE_IS_EMPTY			13009

struct UDPPacket {
	UINT message;
	TCHAR nick[STR_SIZE];
	TCHAR pcname[STR_SIZE];
};

struct ReceivedDataStruct {
	int length;
	char* data;
};

class TCP {
	protected:
		HWND hSendWnd;
		SOCKET TCPSocket;
		sockaddr_in connect_addr;
		std::queue<ReceivedDataStruct> ReceivedData;
		
		TCHAR Nick[STR_SIZE];
		TCHAR PCName[STR_SIZE];
		TCHAR oppNick[STR_SIZE];
		TCHAR oppPCName[STR_SIZE];
		
		bool bIsInited;
		bool bIsWorking;
		bool bIsConnected;
		
		CritSect csTCP;
		CritSect csIsWorking;
		CritSect csReceivedData;
		
		bool KeepAlive();
		void ErrorHandler(SOCKET, UINT, LPCTSTR);
		
		HANDLE hReceiveDataThread;
		bool ReceiveData();
		void ReceiveDataThread();
		static void CALLBACK GetReceiveDataThread(LPVOID);
		
	public:
		TCP(HWND, LPCTSTR);
		
		LPTSTR GetNick();
		LPTSTR GetPCName();
		LPTSTR GetOppNick();
		LPTSTR GetOppPCName();
		
		int SendData(char*, int);
		int GetData(char*&, int&);
		
		void Disconnect();
		
		virtual ~TCP();
};

#endif // _TCP_H_
