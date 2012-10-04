/******************************************************************************************************
*
*	Гра "Шахи"				Курсова робота				дисципліна: "Мережі ЕОМ"					2011
*	Модуль, який реалізує ініціалізацію Direct3D та ренднринг сцени
*
*******************************************************************************************************/

#ifndef _ENGINE_
#define _ENGINE_

#include <d3d9.h>							// Заголовочний файл для DirectX3D
#include <d3dx9.h>	
#include <vector>
#include "engine_exception.h"

#define ENABLED_LAYER 0x0001
#define DEFAULT_STATE ENABLED_LAYER

#define IS_ENABLED(X) X & 0x0001

#define ENGINE_INVALID_ID -1

// Абстрактний клас для наслідування ігровими об'єктами
class Primitive{
protected:
	LPDIRECT3DDEVICE9 device;				// Вказівник на інтерфейс IDirect3DDevice9
public:
	Primitive(LPDIRECT3DDEVICE9 device3D){
		device = device3D;
	};

	virtual ~Primitive(){
	};

	// Метод відображення об'єкта
	virtual void Draw() = 0;
};

class Layer{
protected:
	LPDIRECT3DDEVICE9 direct3DDevice;			// Вказівник на інтерфейс IDirect3DDevice9
	HWND hWnd;
public:
	Layer(LPDIRECT3DDEVICE9 device, HWND handle);
	virtual ~Layer();

	virtual void Draw() = 0;
	
	virtual void LBtnDown(int xPos, int yPos);
	virtual void LBtnUp(int xPos, int yPos);
	virtual void LBtnDblClk(int xPos, int yPos);
	virtual void RBtnDown(int xPos, int yPos);
	virtual void RBtnUp(int xPos, int yPos);
	virtual void RBtnDblClk(int xPos, int yPos);
	virtual void MouseMove(int xPos, int yPos);
	virtual void Wheel(int delta);
	
	virtual void WindowActive(int state);
	
	virtual void KeyDown(int key);
	virtual void KeyUp(int key);
	
	virtual void Timer(int time);
	
	virtual void Resize(int width, int height);

	virtual void BeforeResetDevice();
	virtual void AfterResetDevice();

	virtual void BeforeFreezing();
	virtual void AfterFreezing();
	
	virtual void SetParameter(int parametrID, int parametrValue);
	virtual int GetParameter(int parametrID);

	virtual void SendData(char *data, int len);
};

class Engine{
private:
	LPDIRECT3D9 direct3D;									// Вказівник на головний інтерфейс IDirect3D9
	LPDIRECT3DDEVICE9 direct3DDevice;						// Вказівник на інтерфейс IDirect3DDevice9
	HWND hWnd;												// Дескриптор вікна
	D3DPRESENT_PARAMETERS direct3DParameter; 
	D3DXMATRIX matrixProj;
	
	int animation;
	
	std::vector<Layer *> layers;
	std::vector<int> layersID;								// Ідентифікатори слоїв
	std::vector<short int> params;
	
	void SetParams();
public:
		
	Engine(HWND hWindow);
	~Engine();

	void Init() throw(...);									// Ініціалізація DirectX3D
	void Destroy();											// Звільнення ресурсів DirectX3D
	void Rendering() throw(...);							// Рендеринг сцени засобами DirectX3D
	void ResizeScene(int width, int height) throw(...);
	LPDIRECT3DDEVICE9 Get3DDevice();						// Функція, яка повертає вказівник на інтерфейс IDirect3DDevice9
	void GetRay(int xPos, int yPos, D3DXVECTOR3 *rayStart, D3DXVECTOR3 *rayDirct);
	HWND GetWindowHandle();
	
	void RegisterLayer(Layer *newLayer, int layerID);
	bool UnregisterLayerID(int lID);
	bool EnableLayer(int lID);
	bool DisableLayer(int lID);

	void LBtnDown(int xPos, int yPos);
	void LBtnUp(int xPos, int yPos);
	void LBtnDblClk(int xPos, int yPos);
	void RBtnDown(int xPos, int yPos);
	void RBtnUp(int xPos, int yPos);
	void RBtnDblClk(int xPos, int yPos);
	void MouseMove(int xPos, int yPos);
	void Wheel(int delta);
	
	void WindowActive(int state);
	
	void KeyDown(int key);
	void KeyUp(int key);
	
	void Timer(int time);
	
	void Resize(int width, int height);

	void BeforeResetDevice();
	void AfterResetDevice();
	
	void BeforeFreezing();
	void AfterFreezing();

	void SetParameter(int layerID, int parametrID, int parametrValue);
	int GetParameter(int layerID, int parametrID);
	
	void SendData(int layerID, char *data, int len);

	void ResetAnimation();
	void StartAnimation();
	void EndAnimation();
	bool IsAnimated();
	
};
#endif