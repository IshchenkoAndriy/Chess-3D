#include "CritSect.h"

CritSect::CritSect() {
	InitializeCriticalSection(&cs);
};

void CritSect::Enter() {
	EnterCriticalSection(&cs);
};

void CritSect::TryEnter() {
	TryEnterCriticalSection(&cs);
};

void CritSect::Leave() {
	LeaveCriticalSection(&cs);
};

CritSect::~CritSect() {
	DeleteCriticalSection(&cs);
};
