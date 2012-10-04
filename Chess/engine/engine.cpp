#include "engine.h"

//-----------------------------------------------------------------------------
// Name: Layer
// Desc: ��������� ����� �������� ����
//-----------------------------------------------------------------------------
Layer::Layer(LPDIRECT3DDEVICE9 device, HWND handle):direct3DDevice(device), hWnd(handle){};

Layer::~Layer(){};

void Layer::LBtnDown(int xPos, int yPos){};

void Layer::LBtnUp(int xPos, int yPos){};

void Layer::LBtnDblClk(int xPos, int yPos){};

void Layer::RBtnDown(int xPos, int yPos){};

void Layer::RBtnUp(int xPos, int yPos){};

void Layer::RBtnDblClk(int xPos, int yPos){};

void Layer::MouseMove(int xPos, int yPos){};

void Layer::Wheel(int delta){};

void Layer::WindowActive(int state){};

void Layer::KeyDown(int key){};

void Layer::KeyUp(int key){};

void Layer::Timer(int time){};

void Layer::Resize(int width, int height){};

void Layer::BeforeResetDevice(){};

void Layer::AfterResetDevice(){};

void Layer::BeforeFreezing(){};

void Layer::AfterFreezing(){};

void Layer::SetParameter(int parametrID, int parametrValue){};

int Layer::GetParameter(int parametrID){
	return ENGINE_INVALID_ID;
};

void Layer::SendData(char *data, int len){};

//-----------------------------------------------------------------------------
// Name: Engine
// Desc: ��������� ����� �������� "�������"
//-----------------------------------------------------------------------------
Engine::Engine(HWND hWindow){
	direct3D = NULL;
	direct3DDevice = NULL;
	hWnd = hWindow;
	animation = 0;
};

Engine::~Engine(){
	if (direct3D != NULL){
		direct3D->Release();
	}
	if (direct3DDevice != NULL){
		direct3DDevice->Release();
	}
};

void Engine::SetParams(){

	if(direct3DDevice != NULL) {

		// ������������ ������� ��������
		D3DXMatrixPerspectiveFovLH(&matrixProj, D3DX_PI / 4, (float)direct3DParameter.BackBufferWidth / (float)direct3DParameter.BackBufferHeight, 1.0f, 50.f);

		direct3DDevice->SetTransform(D3DTS_PROJECTION, &matrixProj);
	
		// ������������ ������ �������� ��������� ������
		direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
		// ��������� ���������(��������� �����-������)
		direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
		direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// ������������ ����� ���������(������� ����)
		D3DXMATRIX MatrixView;
		D3DXMatrixLookAtLH(&MatrixView, &D3DXVECTOR3(0.0f, 4.0f, -8.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		direct3DDevice->SetTransform(D3DTS_VIEW, &MatrixView);

		// ��������� ���������
		direct3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		direct3DDevice->SetRenderState(D3DRS_AMBIENT, 0);

		// ��������� ����
		direct3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
		direct3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

		// ��������� Z-������(������ �������)
		direct3DDevice->SetRenderState (D3DRS_ZENABLE, D3DZB_TRUE); 
	
		direct3DDevice->SetSamplerState(0,  D3DSAMP_MAGFILTER,  D3DTEXF_ANISOTROPIC);
		direct3DDevice->SetSamplerState(0,  D3DSAMP_MINFILTER,  D3DTEXF_ANISOTROPIC);
		direct3DDevice->SetSamplerState(0,  D3DSAMP_MIPFILTER,  D3DTEXF_ANISOTROPIC);

		direct3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	
		direct3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		direct3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		direct3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		direct3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		direct3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		direct3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);	
		direct3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		direct3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
		direct3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);

		direct3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
		direct3DDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		direct3DDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		
		direct3DDevice->SetSamplerState(1,  D3DSAMP_MAGFILTER,  D3DTEXF_ANISOTROPIC);
		direct3DDevice->SetSamplerState(1,  D3DSAMP_MINFILTER,  D3DTEXF_ANISOTROPIC);
		direct3DDevice->SetSamplerState(1,  D3DSAMP_MIPFILTER,  D3DTEXF_ANISOTROPIC);
	}
};

void Engine::Init(){
	
	if((direct3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL){		// ��������� IDirect3D9 ����������
		throw EngineException(TEXT("������� ��������� IDirect3D9 ����������"));
	}
	
	D3DDISPLAYMODE DisplayMode;

	if(FAILED( direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode) ) ){		// ��������� ��������� ������
		throw EngineException(TEXT("������� ��������� ��������� ������"));
	}

	ZeroMemory(&direct3DParameter, sizeof(direct3DParameter));

	// �������� �� �������� �����������
	if(SUCCEEDED(direct3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DisplayMode.Format, FALSE, D3DMULTISAMPLE_8_SAMPLES, NULL))){
		direct3DParameter.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	}else if(SUCCEEDED(direct3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DisplayMode.Format, FALSE, D3DMULTISAMPLE_4_SAMPLES, NULL))){
		direct3DParameter.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	}else if(SUCCEEDED(direct3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DisplayMode.Format, FALSE, D3DMULTISAMPLE_2_SAMPLES, NULL))){
		direct3DParameter.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	}else {
		direct3DParameter.MultiSampleType = D3DMULTISAMPLE_NONE;
	}

	direct3DParameter.Windowed = true;						// ������������ ������� ������
	direct3DParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
	direct3DParameter.BackBufferFormat = DisplayMode.Format;
	direct3DParameter.EnableAutoDepthStencil = TRUE;
	direct3DParameter.AutoDepthStencilFormat = D3DFMT_D16;
	direct3DParameter.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	
	RECT windowClient;
	GetClientRect(hWnd, &windowClient);
	
	direct3DParameter.BackBufferWidth = windowClient.right;
	direct3DParameter.BackBufferHeight = windowClient.bottom;
	
	// ��������� �������� Direct3DDevice
	if(FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &direct3DParameter, &direct3DDevice))){
		throw EngineException(TEXT("������� ��������� �������� Direct3D"));
	}
	
	SetParams();
};

void Engine::Destroy(){
	if (direct3D != NULL){
		direct3D->Release();
		direct3D = NULL;
	}
	if (direct3DDevice != NULL){
		direct3DDevice->Release();
		direct3DDevice = NULL;
	}
};

void Engine::Rendering(){

	// ������� �������� ������
	direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF), 1.0f, 0);
		
	direct3DDevice->BeginScene();						// ������� �����
	
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->Draw();							// ���������� ��'����
		}
	}

	direct3DDevice->EndScene();							// ʳ���� �����
	direct3DDevice->Present(NULL, NULL, NULL, NULL);	// ��������� �� �������� ������ � �������(�� �����)
};

void Engine::ResizeScene(int width, int height){
	
	BeforeResetDevice();
	
	// ������������ ��� ������ ���� ��������� � ����������� ������������ 0 �������
	direct3DParameter.BackBufferWidth = (width == 0)? 1 : width;
	direct3DParameter.BackBufferHeight = (height == 0)? 1 : height;

	if(FAILED(direct3DDevice->Reset(&direct3DParameter))){
		throw EngineException(TEXT("��������� ��������������� Direct3D"));
	}
	
	SetParams();

	AfterResetDevice();
};

LPDIRECT3DDEVICE9 Engine::Get3DDevice(){
	return direct3DDevice;
};

// ��������� ������� �� ������� ����������� �� �볺������ ������ ����, �������� ���������� ������� �� ����������� �������
void Engine::GetRay(int xPos, int yPos, D3DXVECTOR3 *rayStart, D3DXVECTOR3 *rayDirct){
	D3DXVECTOR3 currPos;													// ������� �� ���������� ������
	D3DXMATRIX viewMat, projMat;											// ������� ���� � ������ ��� ����������
							
	RECT client;
	GetClientRect(hWnd, &client);											// ��������� ������ �볺������ ������ ����
	direct3DDevice->GetTransform(D3DTS_PROJECTION, &projMat);
	currPos.x = ((2.0f * xPos) / client.right - 1.0f) / projMat._11;		// ������������ ���������� ����� � ������� �� -1 �� 1
	currPos.y = -((2.0f * yPos) / client.bottom - 1.0f) / projMat._22;		// ��� ������������ �� � ���������� �� ������������ ������
	currPos.z = 1.0f;
				
	direct3DDevice->GetTransform(D3DTS_VIEW, &viewMat);						// �������� ������� ��������
	D3DXMatrixInverse(&viewMat, NULL, &viewMat);							// ��������� �������

	// ������� ������� ���������� ������
	rayStart->x = viewMat._41;		
	rayStart->y = viewMat._42;
	rayStart->z = viewMat._43;
	
	// ����������� �������. ������������ ��������� � ���������� ������� � �����
	rayDirct->x  = currPos.x * viewMat._11 + currPos.y * viewMat._21 + currPos.z * viewMat._31;
	rayDirct->y  = currPos.x * viewMat._12 + currPos.y * viewMat._22 + currPos.z * viewMat._32;
	rayDirct->z  = currPos.x * viewMat._13 + currPos.y * viewMat._23 + currPos.z * viewMat._33;
	// ����������� �������
	D3DXVec3Normalize(rayDirct, rayDirct);
}

HWND Engine::GetWindowHandle(){
	return hWnd;
};

void Engine::RegisterLayer(Layer *newLayer, int layerID){
	layers.push_back(newLayer);
	layersID.push_back(layerID);
	params.push_back(DEFAULT_STATE);
};

bool Engine::UnregisterLayerID(int lID){
	for(unsigned i = 0; i < layersID.size(); i++){
		if (layersID[i] == lID){
			layers.erase(layers.begin() + i);
			layersID.erase(layersID.begin() + i);
			params.erase(params.begin() + i);
			return true;
		}
	}
	return false;
};

bool Engine::EnableLayer(int lID){
	for(unsigned i = 0; i < layersID.size(); i++){
		if (layersID[i] == lID){
			params[i] = params[i] | ENABLED_LAYER;
			return true;
		}
	}
	return false;
};

bool Engine::DisableLayer(int lID){
	for(unsigned i = 0; i < layersID.size(); i++){
		if (layersID[i] == lID){
			params[i] = params[i] & (~ENABLED_LAYER);
			return true;
		}
	}
	return false;
};

void Engine::BeforeResetDevice(){
	for(unsigned i = 0; i < layers.size(); i++){
		layers[i]->BeforeResetDevice();
	}
};

void Engine::AfterResetDevice(){
	for(unsigned i = 0; i < layers.size(); i++){
		layers[i]->AfterResetDevice();
	}
};

void Engine::LBtnDown(int xPos, int yPos){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->LBtnDown(xPos, yPos);
		}
	}
};

void Engine::LBtnUp(int xPos, int yPos){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->LBtnUp(xPos, yPos);
		}
	}
};

void Engine::LBtnDblClk(int xPos, int yPos){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->LBtnDblClk(xPos, yPos);
		}
	}
};

void Engine::RBtnDown(int xPos, int yPos){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->RBtnDown(xPos, yPos);
		}
	}
};

void Engine::RBtnUp(int xPos, int yPos){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->RBtnUp(xPos, yPos);
		}
	}
};

void Engine::RBtnDblClk(int xPos, int yPos){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->RBtnDblClk(xPos, yPos);
		}
	}
};

void Engine::MouseMove(int xPos, int yPos){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->MouseMove(xPos, yPos);
		}
	}
};

void Engine::Wheel(int delta){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->Wheel(delta);
		}
	}
};
	
void Engine::WindowActive(int state){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->WindowActive(state);
		}
	}
};
	
void Engine::KeyDown(int key){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->KeyDown(key);
		}
	}
};

void Engine::KeyUp(int key){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->KeyUp(key);
		}
	}
};
	
void Engine::Timer(int time){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->Timer(time);
		}
	}
};
	
void Engine::Resize(int width, int height){
	for(unsigned i = 0; i < layers.size(); i++){
		layers[i]->Resize(width, height);
	}
};

void Engine::SetParameter(int layerID, int parametrID, int parametrValue){
	for(unsigned i = 0; i < layersID.size(); i++){
		if (layersID[i] == layerID){
			layers[i]->SetParameter(parametrID, parametrValue);
		}
	}
};

int Engine::GetParameter(int layerID, int parametrID){
	for(unsigned i = 0; i < layersID.size(); i++){
		if (layersID[i] == layerID){
			return layers[i]->GetParameter(parametrID);
		}
	}
	return ENGINE_INVALID_ID;
};


void Engine::BeforeFreezing(){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->BeforeFreezing();
		}
	}
};

void Engine::AfterFreezing(){
	for(unsigned i = 0; i < layers.size(); i++){
		if(IS_ENABLED(params[i])){
			layers[i]->AfterFreezing();
		}
	}
};

void Engine::ResetAnimation(){
	animation = 0;
};

void Engine::StartAnimation(){
	animation++;
};

void Engine::EndAnimation(){
	if(animation > 0) animation--;
};

bool Engine::IsAnimated(){
	return (animation > 0);
};

void Engine::SendData(int layerID, char *data, int len){
	for(unsigned i = 0; i < layers.size(); i++){
		if (layersID[i] == layerID){
			layers[i]->SendData(data, len);
		}
	}
};