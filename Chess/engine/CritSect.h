#ifndef _CRITSECT_H_
#define _CRITSECT_H_

#include <windows.h>

class CritSect {
	private:
		CRITICAL_SECTION cs;
		
	public:
		CritSect();
		void Enter();
		void TryEnter();
		void Leave();
		~CritSect();
};

#endif // _CRITSECT_H_
