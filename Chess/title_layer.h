/******************************************************************************************************
*
*	��� "����"				������� ������				���������: "����� ���"					2011
*	������, ���� ������ ������ ��������
*
*******************************************************************************************************/

#ifndef _GAME_TITLE_
#define _GAME_TITLE_

#include "windows.h"
#include "engine\\engine.h"
#include "engine\\3d_objects.h"
#include "resource.h"

#define ID_LOADING_TEXT	1
#define ID_SEARCH_TEXT	2
#define ID_WAITING_TEXT	3

#define TEXT_ENABLE		1
#define TEXT_DISABLE	0

#define LOADING_TEXT 	TEXT("������������ ...")
#define SEARCH_TEXT 	TEXT("����� ������� ...")
#define WAITING_TEXT 	TEXT("���������� ���������� ...")

#define TITLE_SCALING	10

class Title: public Layer{
private:
	bool textEnabled;									// ������ ��������� ������ ��� ������������
	VertexBuffer2DT vertex;							// �������� ����� ��'����
	Text2D text;									// ��'��� ��� ��������� ������ � Direct3D
	Texture picture;								// �������� (��������)

public:
	Title(LPDIRECT3DDEVICE9 device, HWND handle);
	
	virtual void Draw();
	
	virtual void Resize(int width, int height);

	virtual void BeforeResetDevice();

	virtual void AfterResetDevice();
	
	virtual void SetParameter(int parametrID, int parametrValue);
};
#endif