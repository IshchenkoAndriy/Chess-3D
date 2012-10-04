#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_

#include "TCP.h"

struct Server {
	TCHAR Nick[STR_SIZE];
	TCHAR PCName[STR_SIZE];
	TCHAR IPAddr[16];
};

class TCPClient : public TCP {
	private:
		HWND hLocateWnd;
		std::vector<Server> servers;
		
		bool bIsSearching;
		bool bIsConnecting;
		
		CritSect csIsSearching;
		CritSect csIsConnecting;
		
		HANDLE hLocateServersThread;
		void LocateServersThread();
		static void CALLBACK GetLocateServersThread(LPVOID);
		
		HANDLE hConnectToServerThread;
		void ConnectToServerThread();
		static void CALLBACK GetConnectToServerThread(LPVOID);
		
	public:
		TCPClient(HWND, LPCTSTR);
		
		unsigned int GetServerCount();
		LPTSTR GetServerNick(unsigned int);
		LPTSTR GetServerPCName(unsigned int);
		LPTSTR GetServerIPAddr(unsigned int);
		
		int LocateServers(HWND);
		int ConnectToServer(unsigned int);
		
		virtual ~TCPClient();
};

#endif // _TCPCLIENT_H_
