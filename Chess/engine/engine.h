/******************************************************************************************************
*
*	��� "����"				������� ������				���������: "����� ���"					2011
*	������, ���� ������ ����������� Direct3D �� ��������� �����
*
*******************************************************************************************************/

#ifndef _ENGINE_
#define _ENGINE_

#include <d3d9.h>							// ������������ ���� ��� DirectX3D
#include <d3dx9.h>	
#include <vector>
#include "engine_exception.h"

#define ENABLED_LAYER 0x0001
#define DEFAULT_STATE ENABLED_LAYER

#define IS_ENABLED(X) X & 0x0001

#define ENGINE_INVALID_ID -1

// ����������� ���� ��� ����������� �������� ��'������
class Primitive{
protected:
	LPDIRECT3DDEVICE9 device;				// �������� �� ��������� IDirect3DDevice9
public:
	Primitive(LPDIRECT3DDEVICE9 device3D){
		device = device3D;
	};

	virtual ~Primitive(){
	};

	// ����� ����������� ��'����
	virtual void Draw() = 0;
};

class Layer{
protected:
	LPDIRECT3DDEVICE9 direct3DDevice;			// �������� �� ��������� IDirect3DDevice9
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
	LPDIRECT3D9 direct3D;									// �������� �� �������� ��������� IDirect3D9
	LPDIRECT3DDEVICE9 direct3DDevice;						// �������� �� ��������� IDirect3DDevice9
	HWND hWnd;												// ���������� ����
	D3DPRESENT_PARAMETERS direct3DParameter; 
	D3DXMATRIX matrixProj;
	
	int animation;
	
	std::vector<Layer *> layers;
	std::vector<int> layersID;								// �������������� ����
	std::vector<short int> params;
	
	void SetParams();
public:
		
	Engine(HWND hWindow);
	~Engine();

	void Init() throw(...);									// ����������� DirectX3D
	void Destroy();											// ��������� ������� DirectX3D
	void Rendering() throw(...);							// ��������� ����� �������� DirectX3D
	void ResizeScene(int width, int height) throw(...);
	LPDIRECT3DDEVICE9 Get3DDevice();						// �������, ��� ������� �������� �� ��������� IDirect3DDevice9
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