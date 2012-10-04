/******************************************************************************************************
*
*	��� "����"				������� ������				���������: "����� ���"					2011
*	������, ���� ������ ���� ����������
*
*******************************************************************************************************/

#ifndef _ENGINE_EXCEPTION_
#define _ENGINE_EXCEPTION_

#include <exception>

class EngineException:public std::exception{
private:
	TCHAR *message;
	
public:
	EngineException():exception(){
		message = NULL;
	};
	
	EngineException(TCHAR *exceptionMessage):exception(){
		message = exceptionMessage;
	};
	
	virtual TCHAR *what(){
		return message;
	};
	
	~EngineException(){};
};

#endif