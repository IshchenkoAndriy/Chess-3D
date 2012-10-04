/******************************************************************************************************
*
*	Гра "Шахи"				Курсова робота				дисципліна: "Мережі ЕОМ"					2011
*	Модуль, який реалізує фонову заставку
*
*******************************************************************************************************/

#include "title_layer.h"

Title::Title(LPDIRECT3DDEVICE9 device, HWND handle):Layer(device, handle){

	RECT windowClient;
	GetClientRect(hWnd, &windowClient);
	Resize(windowClient.left, windowClient.bottom);

	textEnabled = false;
		
	picture.Load(direct3DDevice, IDR_LOADING);
};

void Title::Draw(){
		
	direct3DDevice->SetFVF(vertex.GetFVF_Type());
	direct3DDevice->SetStreamSource(0, vertex.GetVertexBuffer(), 0, sizeof(Vertex2DT));
	direct3DDevice->SetTexture(0, picture.GetTexture());
	direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		
	if(textEnabled){	
		text.Draw();
	}
};

void Title::Resize(int width, int height){
		
	Vertex2DT mas[6];
	mas[0].x = 0.0f;			mas[0].y = 0.0f;			mas[0].z = 0.99f;	mas[0].rhw = 1.0f;	mas[0].Color = 0xFFFFFFFF;	mas[0].tu = 0.0f;	mas[0].tv = 0.0f; 
	mas[1].x = (FLOAT)width;	mas[1].y = (FLOAT)height;	mas[1].z = 0.99f;	mas[1].rhw = 1.0f;	mas[1].Color = 0xFFFFFFFF;	mas[1].tu = 1.0f;	mas[1].tv = 1.0f;
	mas[2].x = 0.0f;			mas[2].y = (FLOAT)height;	mas[2].z = 0.99f;	mas[2].rhw = 1.0f;	mas[2].Color = 0xFFFFFFFF;	mas[2].tu = 0.0f;	mas[2].tv = 1.0f;

	mas[3].x = 0.0f;			mas[3].y = 0.0f;			mas[3].z = 0.99f;	mas[3].rhw = 1.0f;	mas[3].Color = 0xFFFFFFFF;	mas[3].tu = 0.0f;	mas[3].tv = 0.0f;
	mas[4].x = (FLOAT)width;	mas[4].y = 0.0f;			mas[4].z = 0.99f;	mas[4].rhw = 1.0f;	mas[4].Color = 0xFFFFFFFF;	mas[4].tu = 1.0f;	mas[4].tv = 0.0f;
	mas[5].x = (FLOAT)width;	mas[5].y = (FLOAT)height;	mas[5].z = 0.99f;	mas[5].rhw = 1.0f;	mas[5].Color = 0xFFFFFFFF;	mas[5].tu = 1.0f;	mas[5].tv = 1.0f;

	vertex.LoadBuffer(direct3DDevice, mas, sizeof(mas));
		
	RECT area;
	
	area.left = area.top = 0;
	area.right = width;
	area.bottom = height;
	
	text.SetArea(area);
	
	text.SetSize(height / TITLE_SCALING);
};

void Title::BeforeResetDevice(){
	text.Unload();
};

void Title::AfterResetDevice(){
	text.Reload();
};

void Title::SetParameter(int parametrID, int parametrValue){
	
	switch(parametrID){
	
		case ID_LOADING_TEXT:
		{
			RECT windowClient;
			GetClientRect(hWnd, &windowClient);

			text.Load(direct3DDevice, windowClient.bottom / TITLE_SCALING, LOADING_TEXT, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
			textEnabled = (parametrValue == TEXT_ENABLE)? true : false;
			break;
		}

		case ID_SEARCH_TEXT:
		{
			RECT windowClient;
			GetClientRect(hWnd, &windowClient);

			text.Load(direct3DDevice, windowClient.bottom / TITLE_SCALING, SEARCH_TEXT, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
			textEnabled = (parametrValue == TEXT_ENABLE)? true : false;
			break;
		}

		case ID_WAITING_TEXT:
		{
			RECT windowClient;
			GetClientRect(hWnd, &windowClient);

			text.Load(direct3DDevice, windowClient.bottom / TITLE_SCALING, WAITING_TEXT, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
			textEnabled = (parametrValue == TEXT_ENABLE)? true : false;
			break;
		}
	
	default:
		break;
	};
};