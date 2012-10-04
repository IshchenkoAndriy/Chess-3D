#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include "TCP.h"

class TCPServer : public TCP {
	private:
		bool bStopWait;
		bool bIsWaiting;
		
		CritSect csStopWait;
		CritSect csIsWaiting;
		
		HANDLE hWaitForClientThread;
		void WaitForClientThread();
		static void CALLBACK GetWaitForClientThread(LPVOID);
		
	public:
		TCPServer(HWND, LPCTSTR);
		
		int WaitForClient();
		void StopWait();
		
		virtual ~TCPServer();
};

#endif // _TCPSERVER_H_
