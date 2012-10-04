/******************************************************************************************************
*
*	Гра "Шахи"				Курсова робота				дисципліна: "Мережі ЕОМ"					2011
*	Модуль, який описує основні графічні об'єкти
*
*******************************************************************************************************/

#ifndef _3D_OBJECTS_
#define _3D_OBJECTS_

#include <d3d9.h>							// Заголовочний файл для Direct3D
#include <d3dx9.h>							// Заголовочний файл для додаткових операцій Direct3D
#include <d3dx9core.h>
#include <d3dx9mesh.h>						// Заголовочний файл для роботи з "сітками" Mesh
#include <tchar.h>

#define TEXT_HV_CENTER				DT_CENTER | DT_VCENTER | DT_NOCLIP
#define TEXT_HV_CENTER_ELIPSIS		DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS | DT_MODIFYSTRING
#define TEXT_LEFT_VCENTER			DT_LEFT | DT_VCENTER | DT_SINGLELINE 
// Flexible Vertex Format Types - Типи гнучкого вершинного формату

// Тип перетворених в 2D координат з кольором
#define D3DFVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// Тип перетворених в 2D координат з кольором та текстурою
#define D3DFVF_VERTEX2DT (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// Тип неперетворених (3D) координат з кольором 
#define D3DFVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// Тип неперетворених (3D) координат з нормалю
#define D3DFVF_VERTEX3DN (D3DFVF_XYZ | D3DFVF_NORMAL)

// Тип неперетворених (3D) координат з нормалю та текстурними координатами
#define D3DFVF_VERTEX3DNT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

// Структура перетвореної (2D) координати з кольором
struct Vertex2D{
	FLOAT x, y, z, rhw;		// x, y, z - координати
	DWORD Color;			// колір
};

// Структура перетвореної (2D) координати з кольором
struct Vertex2DT{
	FLOAT x, y, z, rhw;		// x, y, z - координати
	DWORD Color;			// колір
	FLOAT tu, tv;			// tu, tv - текстурні координати
};

// Структура неперетвореної (3D) координати з кольором
struct Vertex3D{
	FLOAT x, y, z;			// x, y, z - координати
	DWORD Color;			// колір
};

// Структура неперетвореної (3D) координати з нормалю
struct Vertex3DN{
	FLOAT x, y, z;			// x, y, z - координати
	FLOAT nx, ny, nz;		// nx, ny, nz - вектор нормалі
};

// Структура неперетвореної (3D) координати з нормалю та текстурними координатами
struct Vertex3DNT{
	FLOAT x, y, z;			// x, y, z - координати
	FLOAT nx, ny, nz;		// nx, ny, nz - вектор нормалі
	FLOAT tu, tv;			// tu, tv - текстурні координати
};

// Клас який інкапсулює роботу з вершинним буфером типу D3DFVF_VERTEX2D
class VertexBuffer2D{
private:
	LPDIRECT3DVERTEXBUFFER9 bufferVertex;

public:
	VertexBuffer2D():bufferVertex(NULL){};

	VertexBuffer2D(LPDIRECT3DDEVICE9 device, Vertex2D *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(				// Створення буферу
					size,
					0, D3DFVF_VERTEX2D,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			
			throw EngineException(TEXT("Неможливо створити вершиний буфер"));
		}

		void *pBV;
		bufferVertex->Lock(0, size, (void **)&pBV, 0);
		memcpy(pBV, buffer, size);							// Заповнення буферу
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
			throw EngineException(TEXT("Неможливо створити вершиний буфер"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("Неможливо заповнити вершиний буфер"));
		memcpy(pBV, buffer, size);							// Заповнення буферу
		bufferVertex->Unlock();
	};

	DWORD GetFVF_Type(){								// Отримання вершинного формату
		return D3DFVF_VERTEX2D;
	};

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(){			// Отримання вказівника на буфер
		return bufferVertex;
	};

	~VertexBuffer2D(){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}
	};
};

// Клас який інкапсулює роботу з вершинним буфером типу D3DFVF_VERTEX2DT
class VertexBuffer2DT{
private:
	LPDIRECT3DVERTEXBUFFER9 bufferVertex;

public:
	VertexBuffer2DT():bufferVertex(NULL){};

	VertexBuffer2DT(LPDIRECT3DDEVICE9 device, Vertex2DT *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(				// Створення буферу
					size,
					0, D3DFVF_VERTEX2DT,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			
			throw EngineException(TEXT("Неможливо створити вершиний буфер"));
		}

		void *pBV;
		bufferVertex->Lock(0, size, (void **)&pBV, 0);
		memcpy(pBV, buffer, size);							// Заповнення буферу
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
			throw EngineException(TEXT("Неможливо створити вершиний буфер"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("Неможливо заповнити вершиний буфер"));
		memcpy(pBV, buffer, size);							// Заповнення буферу
		bufferVertex->Unlock();
	};

	DWORD GetFVF_Type(){								// Отримання вершинного формату
		return D3DFVF_VERTEX2DT;
	};

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(){			// Отримання вказівника на буфер
		return bufferVertex;
	};

	~VertexBuffer2DT(){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}
	};
};

// Клас який інкапсулює роботу з вершинним буфером типу D3DFVF_VERTEX3DN
class VertexBuffer3DN{
private:
	LPDIRECT3DVERTEXBUFFER9 bufferVertex;

public:
	VertexBuffer3DN():bufferVertex(NULL){};

	VertexBuffer3DN(LPDIRECT3DDEVICE9 device, Vertex3DN *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(				// Створення буферу
					size,
					0, D3DFVF_VERTEX3DN,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("Неможливо створити вершиний буфер"));
		}

		void *pBV;
		bufferVertex->Lock(0, size, (void **)&pBV, 0);
		memcpy(pBV, buffer, size);							// Заповнення буферу
		bufferVertex->Unlock();
	};

	void LoadBuffer(LPDIRECT3DDEVICE9 device, Vertex3DN *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(
					size,
					0, D3DFVF_VERTEX3DN,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("Неможливо створити вершиний буфер"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("Неможливо заповнити вершиний буфер"));
		memcpy(pBV, buffer, size);
		bufferVertex->Unlock();
	};

	DWORD GetFVF_Type(){								// Отримання вершинного формату
		return D3DFVF_VERTEX3DN;
	};

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(){			// Отримання вказівника на буфер
		return bufferVertex;
	};

	~VertexBuffer3DN(){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}
	};
};

// Клас, який інкапсулює роботу з вершинним буфером типу D3DFVF_VERTEX3DNT
class VertexBuffer3DNT{
private:
	LPDIRECT3DVERTEXBUFFER9 bufferVertex;

public:
	VertexBuffer3DNT():bufferVertex(NULL){};

	VertexBuffer3DNT(LPDIRECT3DDEVICE9 device, const Vertex3DNT *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(				// Створення буферу
					size,
					0, D3DFVF_VERTEX3DNT,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("Неможливо створити вершиний буфер"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("Неможливо заповнити вершиний буфер"));
		memcpy(pBV, buffer, size);							// Заповнення буферу
		bufferVertex->Unlock();
	};

	void LoadBuffer(LPDIRECT3DDEVICE9 device, const Vertex3DNT *buffer, int size){
		if(FAILED(device->CreateVertexBuffer(
					size,
					0, D3DFVF_VERTEX3DNT,
					D3DPOOL_SYSTEMMEM,
					&bufferVertex, NULL))){
			throw EngineException(TEXT("Неможливо створити вершиний буфер"));
		}

		void *pBV;
		if(FAILED(bufferVertex->Lock(0, size, (void **)&pBV, 0))) throw EngineException(TEXT("Неможливо заповнити вершиний буфер"));
		memcpy(pBV, buffer, size);
		bufferVertex->Unlock();
	};

	DWORD GetFVF_Type(){								// Отримання вершинного формату
		return D3DFVF_VERTEX3DNT;
	};

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(){			// Отримання вказівника на буфер
		return bufferVertex;
	};

	~VertexBuffer3DNT(){
		if(bufferVertex != NULL){
			bufferVertex->Release();
		}
	};
};

// Клас, який інкапсулює роботу з індексним буфером
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
			throw EngineException(TEXT("Неможливо створити індексний буфер"));
		}

		void *pBI;
		if(FAILED(bufferIndex->Lock(0, size, &pBI, 0))) throw EngineException(TEXT("Неможливо заповнити індексний буфер"));
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
			throw EngineException(TEXT("Неможливо створити індексний буфер"));
		}

		void *pBI;
		if(FAILED(bufferIndex->Lock(0, size, &pBI, 0)))  throw EngineException(TEXT("Неможливо заповнити індексний буфер"));;
		memcpy(pBI, buffer, size);
		bufferIndex->Unlock();
	};


	LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(){			// Отримання вказівника на буфер
		return bufferIndex;
	};

	~IndexBuffer(){
		if(bufferIndex != NULL){
			bufferIndex->Release();
		}
	};
};

// Класс, який організовує роботу з Меш'ем
class Mesh{
protected:
	LPD3DXMESH model;					// Меш (модель в файлі *.Х)
	DWORD numberParts;					// Кількість частин

public:
	Mesh():model(NULL){};

	// Конструктор, який завантажує меш з файлу
	Mesh(LPDIRECT3DDEVICE9 device, TCHAR* file):model(NULL){

		if(FAILED(D3DXLoadMeshFromX(file, D3DXMESH_SYSTEMMEM, device, NULL, NULL, NULL, &numberParts, &model))){
			throw EngineException(TEXT("Неможливо завантажити модель з файлу"));
		}
	};

	// Конструктор, який завантажує меш з ресурсів
	Mesh(LPDIRECT3DDEVICE9 device, int resID, char *resType):model(NULL){

		LPD3DXBUFFER msBuffer;
		
		if(FAILED(D3DXLoadMeshFromXResource(NULL, MAKEINTRESOURCEA(resID), resType, D3DXMESH_SYSTEMMEM, device, &msBuffer, NULL, NULL, &numberParts, &model)) ){
			throw EngineException(TEXT("Неможливо завантажити модель з ресурсів"));
		}

		model->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)msBuffer->GetBufferPointer(), 0, 0, 0);
		msBuffer->Release();
	};

	// Деструктор, вивільняє всі ресурси
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
			throw EngineException(TEXT("Неможливо завантажити модель з файлу"));
		}
	};

	void Load(LPDIRECT3DDEVICE9 device, int resID, char *resType){
		if(model != NULL){
			model->Release();
		}

		LPD3DXBUFFER msBuffer;
		
		if(FAILED(D3DXLoadMeshFromXResource(NULL, MAKEINTRESOURCEA(resID), resType, D3DXMESH_SYSTEMMEM, device, &msBuffer, NULL, NULL, &numberParts, &model))){
			throw EngineException(TEXT("Неможливо завантажити модель з ресурсів"));
		}

		model->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)msBuffer->GetBufferPointer(), 0, 0, 0);
		msBuffer->Release();
	};

	// Метод, який виводить меш
	void Draw(){
		if(model != NULL){
			for(DWORD i = 0; i < numberParts; i++){
				model->DrawSubset(i);							// Почергове виведення мешу
			}
		}
	};
};

// Клас, який організовує роботу з текстурою
class Texture{
private:
	LPDIRECT3DTEXTURE9 tex;

public:
	Texture():tex(NULL){};

	Texture(LPDIRECT3DDEVICE9 device, int resID):tex(NULL){
		if(FAILED(D3DXCreateTextureFromResource(device, NULL, MAKEINTRESOURCE(resID), &tex))) throw EngineException(TEXT("Неможливо завантажити текстуру з ресурсів"));
	};

	void Load(LPDIRECT3DDEVICE9 device, int resID){
		if(tex != NULL){
			tex->Release();
		}

		if(FAILED(D3DXCreateTextureFromResource(device, NULL, MAKEINTRESOURCE(resID), &tex))) throw EngineException(TEXT("Неможливо завантажити текстуру з ресурсів"));
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

// Класс, який організовує роботу з текстом
class Text3D{
protected:
	LPD3DXMESH modelText;					// Меш (модель текту)

public:
	Text3D():modelText(NULL){};

	// Конструктор
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
		
		if(FAILED(hr)) throw EngineException(TEXT("Неможливо створити текст"));
		
		DeleteObject(font);
		DeleteDC(hdc);
	};

	// Деструктор, вивільняє всі ресурси
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
			throw EngineException(TEXT("Неможливо створити текст"));
		}
		
		DeleteObject(font);
		DeleteDC(hdc);
	};

	// Метод, який виводить меш
	void Draw(){
		if(modelText != NULL){
			modelText->DrawSubset(0);							// Виведення мешу
		}
	};
};

// Класс, який організовує роботу з текстом
class Text2D{
protected:
	LPDIRECT3DDEVICE9 device;
	LPD3DXFONT dxFont;					// Вказівник на інтерфейс роботи із шрифтом
	RECT area;
	D3DCOLOR color;
	TCHAR* text;
	DWORD format;
	int height;

public:
	Text2D():dxFont(NULL), device(NULL){};

	// Конструктор
	Text2D(LPDIRECT3DDEVICE9 direct3DDevice, int textHeight, TCHAR* outputingText, RECT &outputArea, DWORD textFormat, D3DCOLOR textColor):dxFont(NULL){

		device = direct3DDevice;
		memcpy(&area, &outputArea, sizeof(RECT));
		color = textColor;
		text = _tcsdup(outputingText);
		format = textFormat;
		height = textHeight;

		if(text == NULL) throw EngineException(TEXT("Неможливо виділити пам'ять під текст"));

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
		
		if(FAILED(hr)) throw EngineException(TEXT("Неможливо створити текст"));

	};

	// Деструктор, вивільняє всі ресурси
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
		if(text == NULL) throw EngineException(TEXT("Неможливо виділити пам'ять під текст"));

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
		
		if(FAILED(hr)) throw EngineException(TEXT("Неможливо створити текст"));
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
		
			if(FAILED(hr)) throw EngineException(TEXT("Неможливо створити текст"));
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
		
			if(FAILED(hr)) throw EngineException(TEXT("Неможливо створити текст"));
		}
	};

	// Метод, який виводить текст
	void Draw(){
		if(dxFont != NULL){
					
			#ifdef UNICODE
				dxFont->DrawTextW(NULL, text, -1, &area, format, color);		// Виведення тексту
			#else
				dxFont->DrawTextA(NULL, text, -1, &area, format, color);		// Виведення тексту
			#endif
		}
	};
};

// Об'єкт камера
class Camera{
private:
	FLOAT distance;						// Відстань камери
	FLOAT angleX, angleY;				// Кути нахилу камери
	FLOAT minAngleY, maxAngleY;			// Мінімальний і максимальний кути камери по осі У
	FLOAT minDistance, maxDistance;		// Мінімальна і максимальна відстань камери
	
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
		
		// Нормалізація кутів
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
		D3DXVECTOR3 camera;									// Позиція камери
		camera.z = distance * sin(angleY) * cos(angleX);	// Перетворення з полярної системи координат в декартову
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