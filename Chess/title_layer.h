/******************************************************************************************************
*
*	Гра "Шахи"				Курсова робота				дисципліна: "Мережі ЕОМ"					2011
*	Модуль, який реалізує фонову заставку
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

#define LOADING_TEXT 	TEXT("Завантаження ...")
#define SEARCH_TEXT 	TEXT("Пошук серверів ...")
#define WAITING_TEXT 	TEXT("Очікування підключення ...")

#define TITLE_SCALING	10

class Title: public Layer{
private:
	bool textEnabled;									// Прапор виведення тексту про завантаження
	VertexBuffer2DT vertex;							// Вершиний буфер об'єкту
	Text2D text;									// Об'єкт для виведення тексту в Direct3D
	Texture picture;								// Текстура (картинка)

public:
	Title(LPDIRECT3DDEVICE9 device, HWND handle);
	
	virtual void Draw();
	
	virtual void Resize(int width, int height);

	virtual void BeforeResetDevice();

	virtual void AfterResetDevice();
	
	virtual void SetParameter(int parametrID, int parametrValue);
};
#endif