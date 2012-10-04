/******************************************************************************************************
*
*	��� "����"				������� ������				���������: "����� ���"					2011
*	������, ���� ����� ������ ������� ��'����
*
*******************************************************************************************************/

#ifndef _3D_OBJECTS_
#define _3D_OBJECTS_

#include <d3d9.h>							// ������������ ���� ��� Direct3D
#include <d3dx9.h>							// ������������ ���� ��� ���������� �������� Direct3D
#include <d3dx9core.h>
#include <d3dx9mesh.h>						// ������������ ���� ��� ������ � "������" Mesh
#include <tchar.h>

#define TEXT_HV_CENTER				DT_CENTER | DT_VCENTER | DT_NOCLIP
#define TEXT_HV_CENTER_ELIPSIS		DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS | DT_MODIFYSTRING
#define TEXT_LEFT_VCENTER			DT_LEFT | DT_VCENTER | DT_SINGLELINE 
// Flexible Vertex Format Types - ���� �������� ���������� �������

// ��� ������������ � 2D ��������� � ��������
#define D3DFVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// ��� ������������ � 2D ��������� � �������� �� ���������
#define D3DFVF_VERTEX2DT (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// ��� �������������� (3D) ��������� � �������� 
#define D3DFVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// ��� �������������� (3D) ��������� � �������
#define D3DFVF_VERTEX3DN (D3DFVF_XYZ | D3DFVF_NORMAL)

// ��� �������������� (3D) ��������� � ������� �� ����������� ������������
#define D3DFVF_VERTEX3DNT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

// ��������� ����������� (2D) ���������� � ��������
struct Vertex2D{
	FLOAT x, y, z, rhw;		// x, y, z - ����������
	DWORD Color;			// ����
};

// ��������� ����������� (2D) ���������� � ��������
struct Vertex2DT{
	FLOAT x, y, z, rhw;		// x, y, z - ����������
	DWORD Color;			// ����
	FLOAT tu, tv;			// tu, tv - �������� ����������
};

// ��������� ������������� (3D) ���������� � ��������
struct Vertex3D{
	FLOAT x, y, z;			// x, y, z - ����������
	DWORD Color;			// ����
};

// ��������� ������������� (3D) ���������� � �������
struct Vertex3DN{
	FLOAT x, y, z;			// x, y, z - ����������
	FLOAT nx, ny, nz;		// nx, ny, nz - ������ ������
};

// ��������� ������������� (3D) ���������� � ������� �� ����������� ������������
struct Vertex3DNT{
	FLOAT x, y, z;			// x, y, z - ����������
	FLOAT nx, ny, nz;		// nx, ny, nz - ������ ������
	FLOAT tu, tv;			// tu, tv - �������� ����������
};

// ���� ���� ���������� ������ � ��������� ������� ���� D3DFVF_VERTEX2D
class VertexBuffer2D{
private:
	LPDIRECT3DVERTEXBUFFER9 bufferVertex;

public:
	VertexBuffer2D():bufferVertex(NULL){};

	VertexBuffer2D(LPDIRECT3DDEVICE9 device, Vertex2D *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(				// ��������� ������
					size,
					0, D3DFVF_VERTEX2D,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			
			throw EngineException(TEXT("��������� �������� �������� �����"));
		}

		void *pBV;
		bufferVertex->Lock(0, size, (void **)&pBV, 0);
		memcpy(pBV, buffer, size);							// ���������� ������
		bufferVertex->Unlock();
	};

	void LoadBuffer(LPDIRECT3DDEVICE9 device, Vertex2D *buffer, int size){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}

		if(FAILED(device->CreateVertexBuffer(
					size,
					0, D3DFVF_VERTEX2D,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("��������� �������� �������� �����"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("��������� ��������� �������� �����"));
		memcpy(pBV, buffer, size);							// ���������� ������
		bufferVertex->Unlock();
	};

	DWORD GetFVF_Type(){								// ��������� ���������� �������
		return D3DFVF_VERTEX2D;
	};

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(){			// ��������� ��������� �� �����
		return bufferVertex;
	};

	~VertexBuffer2D(){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}
	};
};

// ���� ���� ���������� ������ � ��������� ������� ���� D3DFVF_VERTEX2DT
class VertexBuffer2DT{
private:
	LPDIRECT3DVERTEXBUFFER9 bufferVertex;

public:
	VertexBuffer2DT():bufferVertex(NULL){};

	VertexBuffer2DT(LPDIRECT3DDEVICE9 device, Vertex2DT *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(				// ��������� ������
					size,
					0, D3DFVF_VERTEX2DT,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			
			throw EngineException(TEXT("��������� �������� �������� �����"));
		}

		void *pBV;
		bufferVertex->Lock(0, size, (void **)&pBV, 0);
		memcpy(pBV, buffer, size);							// ���������� ������
		bufferVertex->Unlock();
	};

	void LoadBuffer(LPDIRECT3DDEVICE9 device, Vertex2DT *buffer, int size){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}

		if(FAILED(device->CreateVertexBuffer(
					size,
					0, D3DFVF_VERTEX2DT,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("��������� �������� �������� �����"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("��������� ��������� �������� �����"));
		memcpy(pBV, buffer, size);							// ���������� ������
		bufferVertex->Unlock();
	};

	DWORD GetFVF_Type(){								// ��������� ���������� �������
		return D3DFVF_VERTEX2DT;
	};

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(){			// ��������� ��������� �� �����
		return bufferVertex;
	};

	~VertexBuffer2DT(){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}
	};
};

// ���� ���� ���������� ������ � ��������� ������� ���� D3DFVF_VERTEX3DN
class VertexBuffer3DN{
private:
	LPDIRECT3DVERTEXBUFFER9 bufferVertex;

public:
	VertexBuffer3DN():bufferVertex(NULL){};

	VertexBuffer3DN(LPDIRECT3DDEVICE9 device, Vertex3DN *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(				// ��������� ������
					size,
					0, D3DFVF_VERTEX3DN,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("��������� �������� �������� �����"));
		}

		void *pBV;
		bufferVertex->Lock(0, size, (void **)&pBV, 0);
		memcpy(pBV, buffer, size);							// ���������� ������
		bufferVertex->Unlock();
	};

	void LoadBuffer(LPDIRECT3DDEVICE9 device, Vertex3DN *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(
					size,
					0, D3DFVF_VERTEX3DN,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("��������� �������� �������� �����"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("��������� ��������� �������� �����"));
		memcpy(pBV, buffer, size);
		bufferVertex->Unlock();
	};

	DWORD GetFVF_Type(){								// ��������� ���������� �������
		return D3DFVF_VERTEX3DN;
	};

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(){			// ��������� ��������� �� �����
		return bufferVertex;
	};

	~VertexBuffer3DN(){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}
	};
};

// ����, ���� ���������� ������ � ��������� ������� ���� D3DFVF_VERTEX3DNT
class VertexBuffer3DNT{
private:
	LPDIRECT3DVERTEXBUFFER9 bufferVertex;

public:
	VertexBuffer3DNT():bufferVertex(NULL){};

	VertexBuffer3DNT(LPDIRECT3DDEVICE9 device, const Vertex3DNT *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(				// ��������� ������
					size,
					0, D3DFVF_VERTEX3DNT,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("��������� �������� �������� �����"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("��������� ��������� �������� �����"));
		memcpy(pBV, buffer, size);							// ���������� ������
		bufferVertex->Unlock();
	};

	void LoadBuffer(LPDIRECT3DDEVICE9 device, const Vertex3DNT *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(
					size,
					0, D3DFVF_VERTEX3DNT,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("��������� �������� �������� �����"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("��������� ��������� �������� �����"));
		memcpy(pBV, buffer, size);
		bufferVertex->Unlock();
	};

	DWORD GetFVF_Type(){								// ��������� ���������� �������
		return D3DFVF_VERTEX3DNT;
	};

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(){			// ��������� ��������� �� �����
		return bufferVertex;
	};

	~VertexBuffer3DNT(){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}
	};
};

// ����, ���� ���������� ������ � ��������� �������
class IndexBuffer{
private:
	LPDIRECT3DINDEXBUFFER9 bufferIndex;

public:
	IndexBuffer():bufferIndex(NULL){};

	IndexBuffer(LPDIRECT3DDEVICE9 device, unsigned short *buffer, int size){
		if(FAILED(device->CreateIndexBuffer(
					size,
					0, D3DFMT_INDEX16,
					D3DPOOL_SYSTEMMEM,
					&bufferIndex, NULL))){
			throw EngineException(TEXT("��������� �������� ��������� �����"));
		}

		void *pBI;
		if(FAILED(bufferIndex->Lock(0, size, &pBI, 0))) throw EngineException(TEXT("��������� ��������� ��������� �����"));
		memcpy(pBI, buffer, size);
		bufferIndex->Unlock();
	};

	void LoadBuffer(LPDIRECT3DDEVICE9 device, unsigned short *buffer, int size){
		if(bufferIndex != NULL){
			bufferIndex->Release();
		}

		if(FAILED(device->CreateIndexBuffer(
					size,
					0, D3DFMT_INDEX16,
					D3DPOOL_SYSTEMMEM,
					&bufferIndex, NULL))){
			throw EngineException(TEXT("��������� �������� ��������� �����"));
		}

		void *pBI;
		if(FAILED(bufferIndex->Lock(0, size, &pBI, 0)))  throw EngineException(TEXT("��������� ��������� ��������� �����"));;
		memcpy(pBI, buffer, size);
		bufferIndex->Unlock();
	};


	LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(){			// ��������� ��������� �� �����
		return bufferIndex;
	};

	~IndexBuffer(){
		if(bufferIndex != NULL){
			bufferIndex->Release();
		}
	};
};

// �����, ���� ��������� ������ � ���'��
class Mesh{
protected:
	LPD3DXMESH model;					// ��� (������ � ���� *.�)
	DWORD numberParts;					// ʳ������ ������

public:
	Mesh():model(NULL){};

	// �����������, ���� ��������� ��� � �����
	Mesh(LPDIRECT3DDEVICE9 device, TCHAR* file):model(NULL){

		if(FAILED(D3DXLoadMeshFromX(file, D3DXMESH_SYSTEMMEM, device, NULL, NULL, NULL, &numberParts, &model))){
			throw EngineException(TEXT("��������� ����������� ������ � �����"));
		}
	};

	// �����������, ���� ��������� ��� � �������
	Mesh(LPDIRECT3DDEVICE9 device, int resID, char *resType):model(NULL){

		LPD3DXBUFFER msBuffer;
		
		if(FAILED(D3DXLoadMeshFromXResource(NULL, MAKEINTRESOURCEA(resID), resType, D3DXMESH_SYSTEMMEM, device, &msBuffer, NULL, NULL, &numberParts, &model)) ){
			throw EngineException(TEXT("��������� ����������� ������ � �������"));
		}

		model->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)msBuffer->GetBufferPointer(), 0, 0, 0);
		msBuffer->Release();
	};

	// ����������, �������� �� �������
	~Mesh(){
		if(model != NULL){
			model->Release();
		}
	};

	void Load(LPDIRECT3DDEVICE9 device, TCHAR* file){
		if(model != NULL){
			model->Release();
		}

		if( FAILED(D3DXLoadMeshFromX(file, D3DXMESH_SYSTEMMEM, device, NULL, NULL, NULL, &numberParts, &model))){
			throw EngineException(TEXT("��������� ����������� ������ � �����"));
		}
	};

	void Load(LPDIRECT3DDEVICE9 device, int resID, char *resType){
		if(model != NULL){
			model->Release();
		}

		LPD3DXBUFFER msBuffer;
		
		if(FAILED(D3DXLoadMeshFromXResource(NULL, MAKEINTRESOURCEA(resID), resType, D3DXMESH_SYSTEMMEM, device, &msBuffer, NULL, NULL, &numberParts, &model))){
			throw EngineException(TEXT("��������� ����������� ������ � �������"));
		}

		model->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)msBuffer->GetBufferPointer(), 0, 0, 0);
		msBuffer->Release();
	};

	// �����, ���� �������� ���
	void Draw(){
		if(model != NULL){
			for(DWORD i = 0; i < numberParts; i++){
				model->DrawSubset(i);							// ��������� ��������� ����
			}
		}
	};
};

// ����, ���� ��������� ������ � ���������
class Texture{
private:
	LPDIRECT3DTEXTURE9 tex;

public:
	Texture():tex(NULL){};

	Texture(LPDIRECT3DDEVICE9 device, int resID):tex(NULL){
		if(FAILED(D3DXCreateTextureFromResource(device, NULL, MAKEINTRESOURCE(resID), &tex))) throw EngineException(TEXT("��������� ����������� �������� � �������"));
	};

	void Load(LPDIRECT3DDEVICE9 device, int resID){
		if(tex != NULL){
			tex->Release();
		}

		if(FAILED(D3DXCreateTextureFromResource(device, NULL, MAKEINTRESOURCE(resID), &tex))) throw EngineException(TEXT("��������� ����������� �������� � �������"));
	};
	
	void Unload(){
		if(tex != NULL){
			tex->Release();
			tex = NULL;
		}
	};

	LPDIRECT3DTEXTURE9 GetTexture(){
		return tex;
	};

	~Texture(){
		if(tex != NULL){
			tex->Release();
		}
	};
};

// �����, ���� ��������� ������ � �������
class Text3D{
protected:
	LPD3DXMESH modelText;					// ��� (������ �����)

public:
	Text3D():modelText(NULL){};

	// �����������
	Text3D(LPDIRECT3DDEVICE9 device, const TCHAR* text, FLOAT depth):modelText(NULL){

		HDC hdc;
		HFONT font;

		hdc=CreateCompatibleDC(NULL);

		font=CreateFont(10,								//Height
					   0,								//Width
					   0,								//Escapement
					   0,								//Orientation
					   FW_NORMAL,						//Weight
					   false,							//Italic
					   false,							//Underline
					   false,							//Strikeout
					   DEFAULT_CHARSET,					//Charset 
					   OUT_DEFAULT_PRECIS,				//Output Precision
					   CLIP_DEFAULT_PRECIS,				//Clipping Precision
					   DEFAULT_QUALITY,					//Quality
					   DEFAULT_PITCH|FF_DONTCARE,		//Pitch and Family
					   TEXT("Arial"));

		SelectObject(hdc, font);
	
		HRESULT hr = D3DXCreateText(device,	//Device
                     hdc,					//GDI Device Context
                     text,					//Text 
                     0.001f,				//Maximum chordal deviation from true font outlines       
                     depth,					//Extrusion depth (along -Z axis)
                     &modelText,			//Mesh
                     NULL,					//Adjacency information
                     NULL);					//GlyphMetrics
		
		if(FAILED(hr)) throw EngineException(TEXT("��������� �������� �����"));
		
		DeleteObject(font);
		DeleteDC(hdc);
	};

	// ����������, �������� �� �������
	~Text3D(){
		if(modelText != NULL){
			modelText->Release();
		}
	};

	void Load(LPDIRECT3DDEVICE9 device, const TCHAR* text, FLOAT depth){
		if(modelText != NULL){
			modelText->Release();
		}

		HDC hdc;
		HFONT font;

		hdc=CreateCompatibleDC(NULL);

		font=CreateFont(10,								//Height
					   0,								//Width
					   0,								//Escapement
					   0,								//Orientation
					   FW_NORMAL,						//Weight
					   false,							//Italic
					   false,							//Underline
					   false,							//Strikeout
					   DEFAULT_CHARSET,					//Charset 
					   OUT_DEFAULT_PRECIS,				//Output Precision
					   CLIP_DEFAULT_PRECIS,				//Clipping Precision
					   DEFAULT_QUALITY,					//Quality
					   DEFAULT_PITCH|FF_DONTCARE,		//Pitch and Family
					   TEXT("Arial"));

		SelectObject(hdc, font);

		if(FAILED(D3DXCreateText(device, hdc, text, 0.001f, depth, &modelText, NULL, NULL))){
			throw EngineException(TEXT("��������� �������� �����"));
		}
		
		DeleteObject(font);
		DeleteDC(hdc);
	};

	// �����, ���� �������� ���
	void Draw(){
		if(modelText != NULL){
			modelText->DrawSubset(0);							// ��������� ����
		}
	};
};

// �����, ���� ��������� ������ � �������
class Text2D{
protected:
	LPDIRECT3DDEVICE9 device;
	LPD3DXFONT dxFont;					// �������� �� ��������� ������ �� �������
	RECT area;
	D3DCOLOR color;
	TCHAR* text;
	DWORD format;
	int height;

public:
	Text2D():dxFont(NULL), device(NULL){};

	// �����������
	Text2D(LPDIRECT3DDEVICE9 direct3DDevice, int textHeight, TCHAR* outputingText, RECT &outputArea, DWORD textFormat, D3DCOLOR textColor):dxFont(NULL){

		device = direct3DDevice;
		memcpy(&area, &outputArea, sizeof(RECT));
		color = textColor;
		text = _tcsdup(outputingText);
		format = textFormat;
		height = textHeight;

		if(text == NULL) throw EngineException(TEXT("��������� ������� ���'��� �� �����"));

		HRESULT hr = D3DXCreateFont(device,
									height,							//Height
									0,								//Width
									FW_NORMAL,						//Weight		
									0,								//MipsLevels
									false,							//Italic
									DEFAULT_CHARSET,				//Charset 
									OUT_DEFAULT_PRECIS,				//Output Precision
									DEFAULT_QUALITY,				//Quality
									DEFAULT_PITCH|FF_DONTCARE,		//Pitch and Family
									TEXT("Arial"),
									&dxFont);
		
		if(FAILED(hr)) throw EngineException(TEXT("��������� �������� �����"));

	};

	// ����������, �������� �� �������
	~Text2D(){
		if(dxFont != NULL){
			dxFont->Release();
		}
	};

	void Load(LPDIRECT3DDEVICE9 direct3DDevice, int textHeight, TCHAR* outputingText, RECT &outputArea, DWORD textFormat, D3DCOLOR textColor){
		if(dxFont != NULL){
			dxFont->Release();
		}

		device = direct3DDevice;
		memcpy(&area, &outputArea, sizeof(RECT));
		color = textColor;
		text = _tcsdup(outputingText);
		format = textFormat;
		height = textHeight;
		if(text == NULL) throw EngineException(TEXT("��������� ������� ���'��� �� �����"));

		HRESULT hr = D3DXCreateFont(device,
									height,							//Height
									0,								//Width
									FW_NORMAL,						//Weight		
									0,								//MipsLevels
									false,							//Italic
									DEFAULT_CHARSET,				//Charset 
									OUT_DEFAULT_PRECIS,				//Output Precision
									DEFAULT_QUALITY,				//Quality
									DEFAULT_PITCH|FF_DONTCARE,		//Pitch and Family
									TEXT("Trebuchet MS"),
									&dxFont);
		
		if(FAILED(hr)) throw EngineException(TEXT("��������� �������� �����"));
	};

	void SetArea(RECT &outputArea){
		memcpy(&area, &outputArea, sizeof(RECT));
	};

	void Reload(){
		if(dxFont != NULL){
			dxFont->Release();
		}

		if(device != NULL){
			HRESULT hr = D3DXCreateFont(device,
										height,							//Height
										0,								//Width
										FW_NORMAL,						//Weight		
										0,								//MipsLevels
										false,							//Italic
										DEFAULT_CHARSET,				//Charset 
										OUT_DEFAULT_PRECIS,				//Output Precision
										DEFAULT_QUALITY,				//Quality
										DEFAULT_PITCH|FF_DONTCARE,		//Pitch and Family
										TEXT("Trebuchet MS"),
										&dxFont);
		
			if(FAILED(hr)) throw EngineException(TEXT("��������� �������� �����"));
		}
	};

	void Unload(){
		if(dxFont != NULL){
			dxFont->Release();
			dxFont = NULL;
		}
	};

	void SetSize(int size){
		height = size;

		if(dxFont != NULL){
			dxFont->Release();
		}

		if(device != NULL){
			HRESULT hr = D3DXCreateFont(device,
									height,							//Height
									0,								//Width
									FW_NORMAL,						//Weight		
									0,								//MipsLevels
									false,							//Italic
									DEFAULT_CHARSET,				//Charset 
									OUT_DEFAULT_PRECIS,				//Output Precision
									DEFAULT_QUALITY,				//Quality
									DEFAULT_PITCH|FF_DONTCARE,		//Pitch and Family
									TEXT("Trebuchet MS"),
									&dxFont);
		
			if(FAILED(hr)) throw EngineException(TEXT("��������� �������� �����"));
		}
	};

	// �����, ���� �������� �����
	void Draw(){
		if(dxFont != NULL){
					
			#ifdef UNICODE
				dxFont->DrawTextW(NULL, text, -1, &area, format, color);		// ��������� ������
			#else
				dxFont->DrawTextA(NULL, text, -1, &area, format, color);		// ��������� ������
			#endif
		}
	};
};

// ��'��� ������
class Camera{
private:
	FLOAT distance;						// ³������ ������
	FLOAT angleX, angleY;				// ���� ������ ������
	FLOAT minAngleY, maxAngleY;			// ̳�������� � ������������ ���� ������ �� �� �
	FLOAT minDistance, maxDistance;		// ̳������� � ����������� ������� ������
	
public:
	Camera(){
		distance =  0;
		angleX = 0;
		angleY = 0;
		minDistance = -20.0f;
		maxDistance = 20.0f;
		minAngleY = D3DXToRadian(0.0f);
		maxAngleY = D3DXToRadian(360.0f);
	};

	Camera(FLOAT newDistance, FLOAT newAngleX, FLOAT newAngleY){
		distance =  newDistance;
		angleX = newAngleX;
		angleY = newAngleY;
	};

	void SetDistance(FLOAT newDistance){
		distance =  newDistance;
		if(distance > minDistance){
			distance = minDistance;
		} else if (distance < maxDistance){
			distance = maxDistance;
		}
	};

	void SetAngleX(FLOAT newAngleX){
		angleX = newAngleX;
	};

	void SetAngleY(FLOAT newAngleY){
		angleY = newAngleY;
		if (angleY < minAngleY){
			angleY = minAngleY;
		} else if (angleY > maxAngleY){
			angleY = maxAngleY;
		}
	};

	FLOAT GetAngelX(){
		return angleX;
	};

	FLOAT GetAngelY(){
		return angleY;
	};

	FLOAT GetDistance(){
		return distance;
	};

	void RotateX(FLOAT angle){
		angleX = angleX + angle;
		
		// ����������� ����
		if(angleX > D3DXToRadian(360.0f)) angleX = angleX - D3DXToRadian(360.0f);
		if(angleX < D3DXToRadian(-360.0f)) angleX = angleX + D3DXToRadian(360.0f);
	};

	void RotateY(FLOAT angle){
		angleY = angleY + angle;
		if (angleY < minAngleY){
			angleY = minAngleY;
		} else if (angleY > maxAngleY){
			angleY = maxAngleY;
		}
	};

	void ChangeDistance(FLOAT addValue){
		distance = distance + addValue;
		if(distance > minDistance){
			distance = minDistance;
		} else if (distance < maxDistance){
			distance = maxDistance;
		}
	};

	D3DXVECTOR3 GetPosition(){
		D3DXVECTOR3 camera;									// ������� ������
		camera.z = distance * sin(angleY) * cos(angleX);	// ������������ � ������� ������� ��������� � ���������
		camera.x = distance * sin(angleY) * sin(angleX);
		camera.y = distance * cos(angleY);
		return camera;
	};
	
	void SetMinAngleY(FLOAT newMinAngleY){
		minAngleY = newMinAngleY;
	};
	
	void SetMaxAngleY(FLOAT newMaxAngleY){
		maxAngleY = newMaxAngleY;
	};
	
	void SetMinDistance(FLOAT newMinDistance){
		minDistance = newMinDistance;
	};
	
	void SetMaxDistance(FLOAT newMaxDistance){
		maxDistance = newMaxDistance;
	};
};
#endif