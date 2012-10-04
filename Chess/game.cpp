#include "game.h"

ColoredBackground::ColoredBackground(LPDIRECT3DDEVICE9 device, HWND handle):Background(device , handle){
	RECT windowClient;
	GetClientRect(hWnd, &windowClient);
	Update(windowClient.right, windowClient.bottom);
};

void ColoredBackground::Update(int width, int height){

	Vertex2D mas[6];
	mas[0].x = 0.0f;			mas[0].y = 0.0f;			mas[0].z = 0.99f;	mas[0].rhw = 1.0f;	mas[0].Color = 0xFF4B81ED;
	mas[1].x = (FLOAT)width;	mas[1].y = (FLOAT)height;	mas[1].z = 0.99f;	mas[1].rhw = 1.0f;	mas[1].Color = 0xFFD8E430;
	mas[2].x = 0.0f;			mas[2].y = (FLOAT)height;	mas[2].z = 0.99f;	mas[2].rhw = 1.0f;	mas[2].Color = 0xFFF05400;

	mas[3].x = 0.0f;			mas[3].y = 0.0f;			mas[3].z = 0.99f;	mas[3].rhw = 1.0f;	mas[3].Color = 0xFF4B81ED;
	mas[4].x = (FLOAT)width;	mas[4].y = 0.0f;			mas[4].z = 0.99f;	mas[4].rhw = 1.0f;	mas[4].Color = 0xFF305460;
	mas[5].x = (FLOAT)width;	mas[5].y = (FLOAT)height;	mas[5].z = 0.99f;	mas[5].rhw = 1.0f;	mas[5].Color = 0xFFD8E430;

	vertex.LoadBuffer(device, mas, sizeof(mas));
};

void ColoredBackground::Draw(){
	device->SetTexture(0, NULL);
	device->SetFVF(vertex.GetFVF_Type());
	device->SetStreamSource(0, vertex.GetVertexBuffer(), 0, sizeof(Vertex2D));
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
};


WhiteBackground::WhiteBackground(LPDIRECT3DDEVICE9 device, HWND handle):Background(device , handle){
	RECT windowClient;
	GetClientRect(hWnd, &windowClient);
	Update(windowClient.right, windowClient.bottom);
};

void WhiteBackground::Update(int width, int height){

	Vertex2D mas[15];
	mas[0].x = 0.0f;					mas[0].y = 0.0f;					mas[0].z = 0.99f;	mas[0].rhw = 1.0f;	mas[0].Color = 0xFFDFDFE2;
	mas[1].x = (FLOAT)width / 2.0f;		mas[1].y = 0.0f;					mas[1].z = 0.99f;	mas[1].rhw = 1.0f;	mas[1].Color = 0xFFFFFFFF;
	mas[2].x = 0.0f;					mas[2].y = (FLOAT)height * 0.6f;	mas[2].z = 0.99f;	mas[2].rhw = 1.0f;	mas[2].Color = 0xFFB1B1B8;

	mas[3].x = (FLOAT)width / 2.0f;		mas[3].y = 0.0f;					mas[3].z = 0.99f;	mas[3].rhw = 1.0f;	mas[3].Color = 0xFFFFFFFF;
	mas[4].x = (FLOAT)width;			mas[4].y = 0.0f;					mas[4].z = 0.99f;	mas[4].rhw = 1.0f;	mas[4].Color = 0xFFFDFDFD;
	mas[5].x = (FLOAT)width;			mas[5].y = (FLOAT)height * 0.6f;	mas[5].z = 0.99f;	mas[5].rhw = 1.0f;	mas[5].Color = 0xFFB4B4B4;

	mas[6].x = (FLOAT)width / 2.0f;		mas[6].y = 0.0f;					mas[6].z = 0.99f;	mas[6].rhw = 1.0f;	mas[6].Color = 0xFFFFFFFF;
	mas[7].x = (FLOAT)width;			mas[7].y = (FLOAT)height * 0.6f;	mas[7].z = 0.99f;	mas[7].rhw = 1.0f;	mas[7].Color = 0xFFB4B4B4;
	mas[8].x = 0.0f;					mas[8].y = (FLOAT)height * 0.6f;	mas[8].z = 0.99f;	mas[8].rhw = 1.0f;	mas[8].Color = 0xFFB1B1B8;

	mas[9].x = 0.0f;					mas[9].y = (FLOAT)height * 0.6f;	mas[9].z = 0.99f;	mas[9].rhw = 1.0f;	mas[9].Color = 0xFFB1B1B8;
	mas[10].x = (FLOAT)width;			mas[10].y = (FLOAT)height * 0.6f;	mas[10].z = 0.99f;	mas[10].rhw = 1.0f;	mas[10].Color = 0xFFB4B4B4;
	mas[11].x = 0.0f;					mas[11].y = (FLOAT)height;			mas[11].z = 0.99f;	mas[11].rhw = 1.0f;	mas[11].Color = 0xFFCBCBCF;
		
	mas[12].x = 0.0f;					mas[12].y = (FLOAT)height;			mas[12].z = 0.99f;	mas[12].rhw = 1.0f;	mas[12].Color = 0xFFCBCBCF;
	mas[13].x = (FLOAT)width;			mas[13].y = (FLOAT)height * 0.6f;	mas[13].z = 0.99f;	mas[13].rhw = 1.0f;	mas[13].Color = 0xFFB4B4B4;
	mas[14].x = (FLOAT)width;			mas[14].y = (FLOAT)height;			mas[14].z = 0.99f;	mas[14].rhw = 1.0f;	mas[14].Color = 0xFFCDCDCD;

	vertex.LoadBuffer(device, mas, sizeof(mas));
};

void WhiteBackground::Draw(){
	device->SetTexture(0, NULL);
	device->SetFVF(vertex.GetFVF_Type());
	device->SetStreamSource(0, vertex.GetVertexBuffer(), 0, sizeof(Vertex2D));
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 5);
};


Foreground::Foreground(LPDIRECT3DDEVICE9 device, HWND handle):Background(device , handle){
	RECT windowClient;
	GetClientRect(hWnd, &windowClient);
	Update(windowClient.right, windowClient.bottom);
};

void Foreground::Update(int width, int height){

	Vertex2D mas[6];
	mas[0].x = 0.0f;			mas[0].y = 0.0f;			mas[0].z = 0.00f;	mas[0].rhw = 0.0f;	mas[0].Color = 0x50000000;
	mas[1].x = (FLOAT)width;	mas[1].y = (FLOAT)height;	mas[1].z = 0.00f;	mas[1].rhw = 0.0f;	mas[1].Color = 0x50000000;
	mas[2].x = 0.0f;			mas[2].y = (FLOAT)height;	mas[2].z = 0.00f;	mas[2].rhw = 0.0f;	mas[2].Color = 0x50000000;

	mas[3].x = 0.0f;			mas[3].y = 0.0f;			mas[3].z = 0.00f;	mas[3].rhw = 0.0f;	mas[3].Color = 0x50000000;
	mas[4].x = (FLOAT)width;	mas[4].y = 0.0f;			mas[4].z = 0.00f;	mas[4].rhw = 0.0f;	mas[4].Color = 0x50000000;
	mas[5].x = (FLOAT)width;	mas[5].y = (FLOAT)height;	mas[5].z = 0.00f;	mas[5].rhw = 0.0f;	mas[5].Color = 0x50000000;

	vertex.LoadBuffer(device, mas, sizeof(mas));
};

void Foreground::Draw(){
	device->SetTexture(0, NULL);
	device->SetFVF(vertex.GetFVF_Type());
	device->SetStreamSource(0, vertex.GetVertexBuffer(), 0, sizeof(Vertex2D));
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
};


ChessBoard::ChessBoard(LPDIRECT3DDEVICE9 device):Primitive(device){

	D3DXMatrixIdentity(&matrixWorld);									// Встановлення одиничної матриці
	board.LoadBuffer(device, boardVertex, sizeof(boardVertex));			// Завантаження вершиного буферу вершинами дошки
		
	border.LoadBuffer(device, borderVertex, sizeof(borderVertex));		// Завантаження вершинного буферу вершинами рамки
	
	SetTheme(THEME_WHITE);
	
	D3DXMATRIX rotaion, translation, sizing;
	for(int i = 0; i < 32; i++){
		text[i].Load(device, &TextOnBoard[i].character, TEXT_HEIGHT);	// Завантаження символу

		// Проведення трансформацій з матрицями положення
		D3DXMatrixRotationYawPitchRoll(&rotaion, 0.0f, D3DXToRadian(TextOnBoard[i].rotationX), D3DXToRadian(TextOnBoard[i].rotationZ));
		D3DXMatrixTranslation(&translation, TextOnBoard[i].shiftX, 0.0f, TextOnBoard[i].shiftZ);
		D3DXMatrixMultiply(&textPositions[i], &rotaion, &translation);
		D3DXMatrixScaling(&sizing, TEXT_SCALING, TEXT_SCALING, TEXT_SCALING);
		D3DXMatrixMultiply(&textPositions[i], &sizing, &textPositions[i]);
	}
};

void ChessBoard::SetTheme(int themeID){
	switch(themeID){
	case THEME_WHITE:
		boardTexture.Load(device, TEX_BOARD);								// Завантаження текстури
		borderTexture[0].Load(device, TEX_BORDER);
		borderTexture[1].Unload();
		borderTexture[2].Load(device, TEX_BORDER);
		textTexture.Unload();

		borderMaterial[0] = &CS_Board;
		borderMaterial[1] = &CS_Theme1_Border;
		borderMaterial[2] = &CS_Board;
		textMaterial = &CS_Theme1_Text;
		break;

	case THEME_COLORED:
		boardTexture.Load(device, TEX_BOARD);								// Завантаження текстури
		borderTexture[0].Unload();
		borderTexture[1].Unload();
		borderTexture[2].Unload();
		textTexture.Unload();

		borderMaterial[0] = &CS_Theme2_Border;
		borderMaterial[1] = &CS_Theme2_Border;
		borderMaterial[2] = &CS_Theme2_Border;
		textMaterial = &CS_Theme2_Border;
		break;

	default:
		break;
	};
};

void ChessBoard::Draw(){
	device->SetTransform(D3DTS_WORLD, &matrixWorld);							// Встановлення матриці світу для дошки
	device->SetStreamSource(0, board.GetVertexBuffer(), 0, sizeof(Vertex3DNT));
	device->SetFVF(board.GetFVF_Type());
	device->SetTexture(0, boardTexture.GetTexture());
	
	device->SetMaterial(&CS_Board);												// Встановлення матеріалу дошки
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);							// Виведення дошки

	device->SetFVF(border.GetFVF_Type());
	device->SetStreamSource(0, border.GetVertexBuffer(), 0, sizeof(Vertex3DNT));

	device->SetTexture(0, borderTexture[0].GetTexture());	
	device->SetMaterial(borderMaterial[0]);	
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);							// Виведення рамки
	
	device->SetTexture(0, borderTexture[1].GetTexture());	
	device->SetMaterial(borderMaterial[1]);	
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 24, 8);

	device->SetTexture(0, borderTexture[2].GetTexture());	
	device->SetMaterial(borderMaterial[2]);	
	device->DrawPrimitive(D3DPT_TRIANGLELIST, 48, 8);							// Виведення рамки
		
	
	device->SetTexture(0, textTexture.GetTexture());
	device->SetMaterial(textMaterial);
	
	for(int i = 0; i < 32; i++){
		device->SetTransform(D3DTS_WORLD, &textPositions[i]);					// Встановлення матриці положення символу
		text[i].Draw();															// Виведення символів
	}
};


ChessFigure::ChessFigure(LPDIRECT3DDEVICE9 device, int modelResID, D3DMATERIAL9 *newMaterial, int textureResID):Primitive(device){
	model.Load(device, modelResID, "RC_DATA");
		
	if(textureResID != 0){
		texture.Load(device, textureResID);
	}

	if(newMaterial != NULL){
		material = new D3DMATERIAL9;
		memcpy(material, newMaterial, sizeof(D3DMATERIAL9));
	}
	D3DXMatrixIdentity(&matrixWorld);
};

void ChessFigure::ChangeModel(int resID){
	model.Load(device, resID, "RC_DATA");
};

void ChessFigure::ChangeTexture(int resID){
	texture.Load(device, resID);
};

// Зміна матриці світу об'єкта
void ChessFigure::SetWorldMatrix(D3DXMATRIX *newMatWorld){
	memcpy(&matrixWorld, newMatWorld, sizeof(D3DXMATRIX));
};

void ChessFigure::SetMaterial(D3DMATERIAL9 *newMaterial){

	if(newMaterial != NULL){

		if(material == NULL){
			material = new D3DMATERIAL9;
		}
		memcpy(material, newMaterial, sizeof(D3DMATERIAL9));
	}
};

void ChessFigure::SetTransparency(FLOAT value){
	material->Diffuse.a = value;
	material->Ambient.a = value;
	material->Emissive.a = value;
	material->Specular.a = value;
};

void ChessFigure::Draw(){
	device->SetTransform(D3DTS_WORLD, &matrixWorld);			// Встановлення матриці світу для кожного мешу
	if(material != NULL) device->SetMaterial(material);			// Встановлення матеріалу
	device->SetTexture(0, texture.GetTexture());
	model.Draw();				
};

ChessFigure::~ChessFigure(){
	
	if(material == NULL){
		delete material;
	}
};

Color WhiteFigure::Who(){
	return WHITE;
};

BlackFigure::BlackFigure(LPDIRECT3DDEVICE9 device, int modelResID, D3DMATERIAL9 *newMaterial, int textureResID):ChessFigure(device, modelResID, newMaterial, textureResID){
	D3DXMatrixRotationY(&RotatedMatrx, D3DXToRadian(180.0f));
};

// Зміна матриці світу об'єкта
void BlackFigure::SetWorldMatrix(D3DXMATRIX *newMatWorld){
	memcpy(&matrixWorld, newMatWorld, sizeof(D3DXMATRIX));
	D3DXMatrixMultiply(&matrixWorld, &RotatedMatrx, &matrixWorld);
};

Color BlackFigure::Who(){
	return BLACK;
};

bool ChessGame::SelectedCell(int column, int row, D3DXVECTOR3 *rayStart, D3DXVECTOR3 *rayDirection){
		
	if(column < 8 && column >= 0 && row < 8 && row >= 0){
		int cell = column * 9 + row;

		D3DXVECTOR3 p0 = D3DXVECTOR3(Vertexs[cell].x, Vertexs[cell].y, Vertexs[cell].z);
		D3DXVECTOR3 p1 = D3DXVECTOR3(Vertexs[cell + 10].x, Vertexs[cell + 10].y, Vertexs[cell + 10].z);
		D3DXVECTOR3 p2 = D3DXVECTOR3(Vertexs[cell + 1].x, Vertexs[cell + 1].y, Vertexs[cell + 1].z);
		D3DXVECTOR3 p4 = D3DXVECTOR3(Vertexs[cell + 9].x, Vertexs[cell + 9].y, Vertexs[cell + 9].z);
		
		if(D3DXIntersectTri(&p0, &p1, &p2, rayStart, rayDirection, NULL, NULL, NULL)){ 
			return true;
		}
		if(D3DXIntersectTri(&p0, &p4, &p1, rayStart, rayDirection, NULL, NULL, NULL)){
			return true;
		}
	}
	return false;
};

bool ChessGame::OnBoard(D3DXVECTOR3 *rayStart, D3DXVECTOR3 *rayDirection){
	
	D3DXVECTOR3 p0 = D3DXVECTOR3(boardVertex[0].x, boardVertex[0].y, boardVertex[0].z);
	D3DXVECTOR3 p1 = D3DXVECTOR3(boardVertex[1].x, boardVertex[1].y, boardVertex[1].z);
	D3DXVECTOR3 p2 = D3DXVECTOR3(boardVertex[2].x, boardVertex[2].y, boardVertex[2].z);
	D3DXVECTOR3 p3 = D3DXVECTOR3(boardVertex[3].x, boardVertex[3].y, boardVertex[3].z);
	D3DXVECTOR3 p4 = D3DXVECTOR3(boardVertex[4].x, boardVertex[4].y, boardVertex[4].z);
	D3DXVECTOR3 p5 = D3DXVECTOR3(boardVertex[5].x, boardVertex[5].y, boardVertex[5].z);
						
	if(D3DXIntersectTri(&p0, &p1, &p2, rayStart, rayDirection, NULL, NULL, NULL)){ 
		return true;
	}
	if(D3DXIntersectTri(&p3, &p4, &p5, rayStart, rayDirection, NULL, NULL, NULL)){
		return true;
	}
	return false;
};

void ChessGame::PlaceFigures(unsigned int field[8][8], unsigned int color[8][8]){
	
	for(int i = 0; i < 8; i++)	{
		for(int j = 0; j < 8; j++)	{
			D3DXMATRIX m;

			switch(field[i][j]){
			
			case FIGURE_NULL:
				figures[i][j] = NULL;
				break;
			
			case ROCK:
				D3DXMatrixTranslation(&m, Pos[i][j].x, Pos[i][j].y, Pos[i][j].z);
				if (color[i][j] == WHITE) figures[i][j] = new WhiteFigure(direct3DDevice, CS_ROOK, &CS_Theme1_White);
				else figures[i][j] = new BlackFigure(direct3DDevice, CS_ROOK, &CS_Theme1_Black);
				figures[i][j]->SetWorldMatrix(&m);
				break;
			
			case KNIGHT:
				D3DXMatrixTranslation(&m, Pos[i][j].x, Pos[i][j].y, Pos[i][j].z);
				if (color[i][j] == WHITE) figures[i][j] = new WhiteFigure(direct3DDevice, CS_KNIGHT, &CS_Theme1_White);
				else figures[i][j] = new BlackFigure(direct3DDevice, CS_KNIGHT, &CS_Theme1_Black);
				figures[i][j]->SetWorldMatrix(&m);
				break;

			case BISHOP:
				D3DXMatrixTranslation(&m, Pos[i][j].x, Pos[i][j].y, Pos[i][j].z);
				if (color[i][j] == WHITE) figures[i][j] = new WhiteFigure(direct3DDevice, CS_BISHOP, &CS_Theme1_White);
				else figures[i][j] = new BlackFigure(direct3DDevice, CS_BISHOP, &CS_Theme1_Black);
				figures[i][j]->SetWorldMatrix(&m);
				break;

			case QUEEN:
				D3DXMatrixTranslation(&m, Pos[i][j].x, Pos[i][j].y, Pos[i][j].z);
				if (color[i][j] == WHITE) figures[i][j] = new WhiteFigure(direct3DDevice, CS_QUEEN, &CS_Theme1_White);
				else figures[i][j] = new BlackFigure(direct3DDevice, CS_QUEEN, &CS_Theme1_Black);
				figures[i][j]->SetWorldMatrix(&m);
				break;
			
			case KING:
				D3DXMatrixTranslation(&m, Pos[i][j].x, Pos[i][j].y, Pos[i][j].z);
				if (color[i][j] == WHITE) figures[i][j] = new WhiteFigure(direct3DDevice, CS_KING, &CS_Theme1_White);
				else figures[i][j] = new BlackFigure(direct3DDevice, CS_KING, &CS_Theme1_Black);
				figures[i][j]->SetWorldMatrix(&m);
				break;

			case PAWN:
				D3DXMatrixTranslation(&m, Pos[i][j].x, Pos[i][j].y, Pos[i][j].z);
				if (color[i][j] == WHITE) figures[i][j] = new WhiteFigure(direct3DDevice, CS_PAWN, &CS_Theme1_White);
				else figures[i][j] = new BlackFigure(direct3DDevice, CS_PAWN, &CS_Theme1_Black);
				figures[i][j]->SetWorldMatrix(&m);
				break;
			}
		}
	}
};

ChessGame::ChessGame(LPDIRECT3DDEVICE9 device, HWND handle):Layer(device, handle){
		
	background = new WhiteBackground(direct3DDevice, hWnd);
		
	board = new ChessBoard(direct3DDevice);
		
	cam.SetMinAngleY(MIN_CAM_ANGLE_Y);
	cam.SetMaxAngleY(MAX_CAM_ANGLE_Y);
	cam.SetMinDistance(MIN_CAM_DISTANCE);
	cam.SetMaxDistance(MAX_CAM_DISTANCE);

	cam.SetAngleX(DEFAULT_CAM_ANGLE_X);
	cam.SetAngleY(DEFAULT_CAM_ANGLE_Y);
	cam.SetDistance(DEFAULT_CAM_DIST);

	// Встановимо освітлення
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type       = D3DLIGHT_DIRECTIONAL;	// Тип світла - направлений
	light.Specular.r = light.Diffuse.r  = 1.0f;	// RGB-колір світла - білий
	light.Specular.g = light.Diffuse.g  = 1.0f;
	light.Specular.b = light.Diffuse.b  = 1.0f;
	light.Specular.a = light.Diffuse.a  = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Range      = 1000.0f;					// Відстань розповсюдження променів
		
	rButtonDown = false;
	selColumn = _cnull;
	selRow = _rnull;

	secondClick = false;
	movingCam = false;

	checkColunm = _cnull;
	checkRow = _rnull;

	transperentRow = _rnull;
	transperentColumn = _cnull;

	gameOver = false;
	resultMoving = SUCCESS_MOVE;
	foreground = new Foreground(direct3DDevice, hWnd);

	Vertex3DNT Rect[6]; 

	for(int row = 0; row < 8; row++){
		for(int column = 0; column < 8; column++){
			Rect[0].x = (column - 4) * CS_FIGURE_SIZE; Rect[0].y = 0.0005f; Rect[0].z = (row - 3)* CS_FIGURE_SIZE; Rect[0].nx = 0.0f; Rect[0].ny = 1.0f; Rect[0].nz = 0.0f; Rect[0].tu = 0.0f; Rect[0].tv = 0.0f;
			Rect[1].x = (column - 3) * CS_FIGURE_SIZE; Rect[1].y = 0.0005f; Rect[1].z = (row - 4)* CS_FIGURE_SIZE; Rect[1].nx = 0.0f; Rect[1].ny = 1.0f; Rect[1].nz = 0.0f; Rect[1].tu = 1.0f; Rect[1].tv = 1.0f;
			Rect[2].x = (column - 4) * CS_FIGURE_SIZE; Rect[2].y = 0.0005f; Rect[2].z = (row - 4)* CS_FIGURE_SIZE; Rect[2].nx = 0.0f; Rect[2].ny = 1.0f; Rect[2].nz = 0.0f; Rect[2].tu = 0.0f; Rect[2].tv = 1.0f;

			Rect[3].x = (column - 4) * CS_FIGURE_SIZE; Rect[3].y = 0.0005f; Rect[3].z = (row - 3)* CS_FIGURE_SIZE; Rect[3].nx = 0.0f; Rect[3].ny = 1.0f; Rect[3].nz = 0.0f; Rect[3].tu = 0.0f; Rect[3].tv = 0.0f;
			Rect[4].x = (column - 3) * CS_FIGURE_SIZE; Rect[4].y = 0.0005f; Rect[4].z = (row - 3)* CS_FIGURE_SIZE; Rect[4].nx = 0.0f; Rect[4].ny = 1.0f; Rect[4].nz = 0.0f; Rect[4].tu = 1.0f; Rect[4].tv = 0.0f;
			Rect[5].x = (column - 3) * CS_FIGURE_SIZE; Rect[5].y = 0.0005f; Rect[5].z = (row - 4)* CS_FIGURE_SIZE; Rect[5].nx = 0.0f; Rect[5].ny = 1.0f; Rect[5].nz = 0.0f; Rect[5].tu = 1.0f; Rect[5].tv = 1.0f;
		
			highlightCells[row][column].LoadBuffer(direct3DDevice, Rect, sizeof(Rect));
		}
	}
	D3DXMatrixIdentity(&matrixHighlight);
		
	textureHighlight[TEXTURE_NULL].Unload();
	textureHighlight[TEXTURE_CURPOS].Load(direct3DDevice, IDB_CURENT);
	textureHighlight[TEXTURE_MOVE].Load(direct3DDevice, IDB_MOVE);
	textureHighlight[TEXTURE_ATTACK].Load(direct3DDevice, IDB_ATTACK);
	textureHighlight[TEXTURE_PROMOTION].Load(direct3DDevice, IDB_PROMOTION);
	textureHighlight[TEXTURE_CASTLING].Load(direct3DDevice, IDB_CASTLING);
	textureHighlight[TEXTURE_CHECK].Load(direct3DDevice, IDB_CHECK);
	textureHighlight[TEXTURE_CURSOR].Load(direct3DDevice, IDB_CURSOR);
	textureHighlight[TEXTURE_CURSOR2].Load(direct3DDevice, IDB_CURSOR2);

	ZeroMemory(&highlight, sizeof(highlight));

	Render->StartAnimation();
	startTimeMovingCam = GetTickCount() + DELAY_FIRST_ROTATION;
	startCamPos = cam;
	movingCam = true;
};

void ChessGame::Draw(){
		
	D3DXMATRIX MatrixView;							// Матриція перегляду(камера)
	D3DXVECTOR3 camera = cam.GetPosition();			// Позиція камери

	D3DXVECTOR3 VectorDir = -camera;				//  Встановимо нормаль
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &VectorDir);
		
	direct3DDevice->SetLight(0, &light);
	direct3DDevice->LightEnable(0, TRUE);

	D3DXMatrixLookAtLH(&MatrixView, &camera, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	direct3DDevice->SetTransform(D3DTS_VIEW, &MatrixView);
		
	background->Draw();
	board->Draw();

	for(int row = 0; row < 8; row++){
		for(int column = 0; column < 8; column++){
			if(figures[row][column] != NULL && (transperentRow != row || transperentColumn != column)){
				figures[row][column]->Draw();
			};
		}
	}

	// Встановлюємо звичайний матеріал
	direct3DDevice->SetMaterial(&CS_Board);
	// Встановюємо матрицю світу
	direct3DDevice->SetTransform(D3DTS_WORLD, &matrixHighlight);

	// Переглядаємо масив підсвітки і рисуємо текстури на дошці
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			switch(highlight[i][j]){
				
			// Пуста клітинка
			case MOVE_NULL:
				if(checkColunm == j && checkRow == i){			// Перевіяємо чи на клітинці стоїть король з шахом
					if(selColumn == j && selRow == i){			// Далі перевіряємо чи клітинка виділена
							// Встановлюємо на 0 текстурний рівень текстуру курсору
						direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR].GetTexture());
							// Встановлюємо на 1 текстурний рівень текстуру шаху
						direct3DDevice->SetTexture(1, textureHighlight[TEXTURE_CHECK].GetTexture());
					}
					else{
						direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CHECK].GetTexture());
					}
					direct3DDevice->SetStreamSource(0, highlightCells[i][j].GetVertexBuffer(), 0, sizeof(Vertex3DNT));
					direct3DDevice->SetFVF(highlightCells[i][j].GetFVF_Type());
					direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
				} else if(selColumn == j && selRow == i){			// Перевіряємо чи клітинка виділена
					if(figures[i][j] != NULL){						// і чи стоїть на клітинці фігура?
						direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR2].GetTexture());
					}
					else{
						direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR].GetTexture());
					}
					// Встановлюємо вершини примітиву і виводимо його
					direct3DDevice->SetStreamSource(0, highlightCells[i][j].GetVertexBuffer(), 0, sizeof(Vertex3DNT));
					direct3DDevice->SetFVF(highlightCells[i][j].GetFVF_Type());
					direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
				}

				// Скидуємо текстуру з 1 текстурного рівня, для 0 ми завжи перевстановлюємо для виведення
				direct3DDevice->SetTexture(1, NULL);
				break;

			// Клітинка на якій стоїть вибрана фігура
			case MOVE_CURPOS:
				if(checkColunm == j && checkRow == i){
					if(selColumn == j && selRow == i){
						direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR].GetTexture());
						direct3DDevice->SetTexture(1, textureHighlight[TEXTURE_CHECK].GetTexture());
					} else {
						direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CHECK].GetTexture());
					}
				}
				else{
					if(selColumn == j && selRow == i){
						direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR].GetTexture());
						direct3DDevice->SetTexture(1, textureHighlight[TEXTURE_CURPOS].GetTexture());
					} else {
						direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURPOS].GetTexture());
					}
				}
				direct3DDevice->SetStreamSource(0, highlightCells[i][j].GetVertexBuffer(), 0, sizeof(Vertex3DNT));
				direct3DDevice->SetFVF(highlightCells[i][j].GetFVF_Type());
				direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
				direct3DDevice->SetTexture(1, NULL);
				break;

			// Клітинка яку можливо побити та "пройти з взяттям" фігури суперника
			case ATTACK:
			case ATTACK_INPASSING:
				if(selColumn == j && selRow == i){
					direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR].GetTexture());
					direct3DDevice->SetTexture(1, textureHighlight[TEXTURE_ATTACK].GetTexture());
				} else {
					direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_ATTACK].GetTexture());
				}

				direct3DDevice->SetStreamSource(0, highlightCells[i][j].GetVertexBuffer(), 0, sizeof(Vertex3DNT));
				direct3DDevice->SetFVF(highlightCells[i][j].GetFVF_Type());
				
				direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
				direct3DDevice->SetTexture(1, NULL);
				break;

			// Клітинка на яку можливий хід
			case MOVE:
			case MOVE_INPASSING: 
				if(selColumn == j && selRow == i){
					direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR].GetTexture());
					direct3DDevice->SetTexture(1, textureHighlight[TEXTURE_MOVE].GetTexture());
				} else {
					direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_MOVE].GetTexture());
				}

				direct3DDevice->SetStreamSource(0, highlightCells[i][j].GetVertexBuffer(), 0, sizeof(Vertex3DNT));
				direct3DDevice->SetFVF(highlightCells[i][j].GetFVF_Type());
				direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
				direct3DDevice->SetTexture(1, NULL);
				break;

			// Клітинка на яку можливий хід при рокіровці
			case SHORT_CASTLING:
			case LONG_CASTLING:
				if(selColumn == j && selRow == i){
					direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR].GetTexture());
					direct3DDevice->SetTexture(1, textureHighlight[TEXTURE_CASTLING].GetTexture());
				} else {
					direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CASTLING].GetTexture());
				}

				direct3DDevice->SetStreamSource(0, highlightCells[i][j].GetVertexBuffer(), 0, sizeof(Vertex3DNT));
				direct3DDevice->SetFVF(highlightCells[i][j].GetFVF_Type());
								
				direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
				direct3DDevice->SetTexture(1, NULL);
				break;

			// Клітинка при ході на яку можлива заміна фігури
			case ATTACK_PROMOTION:
			case MOVE_PROMOTION:
				if(selColumn == j && selRow == i){
					direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_CURSOR].GetTexture());
					direct3DDevice->SetTexture(1, textureHighlight[TEXTURE_PROMOTION].GetTexture());
				} else {
					direct3DDevice->SetTexture(0, textureHighlight[TEXTURE_PROMOTION].GetTexture());
				}
				direct3DDevice->SetStreamSource(0, highlightCells[i][j].GetVertexBuffer(), 0, sizeof(Vertex3DNT));
				direct3DDevice->SetFVF(highlightCells[i][j].GetFVF_Type());
				
				direct3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
				direct3DDevice->SetTexture(1, NULL);
				break;
			}
		}
	}

	if(transperentRow != _rnull && transperentColumn != _cnull && figures[transperentRow][transperentColumn] != NULL){
		figures[transperentRow][transperentColumn]->Draw();
	}

	if(gameOver){
		foreground->Draw();
		text.Draw();
	}
};

	// Підпрограма обробки прокрутки коліщатком мишки
void ChessGame::Wheel(int delta){
	if(!gameOver){
		(delta > 0) ? cam.ChangeDistance(0.1f) : cam.ChangeDistance(-0.1f);
	}
};

// Підпрограма обробки натиснення правої кнопки миші
void ChessGame::RBtnDown(int xPos, int yPos){
	if(!gameOver){
		if(rButtonDown == false){								// Перевіряємо прапор опущеності кнопки
			if(movingCam){
				Render->ResetAnimation();
				movingCam = false;									// Скидаємо прапор переміщення камери
			}
			rButtonDown = true;									// Встановлюємо прапор натиснутої кнопки
			OldPos.x = xPos;									// Зберігаємо поточну позицію курсору
			OldPos.y = yPos;

			RECT client;
			GetClientRect(hWnd, &client);						// Отримуємо розміри клієнтської області вікна
			POINT p;
			p.x = client.left;	p.y = client.top;
			ClientToScreen(hWnd, &p);							// Переводимо верхній лівий кут вікна в екрані координати
			client.left = p.x;	client.top = p.y;
			p.x = client.right;	p.y = client.bottom;
			ClientToScreen(hWnd, &p);							// Переводимо нижній прави кут вікна в екрані координати
			client.right = p.x;	client.bottom = p.y;

			ClipCursor(&client);								//  Встановлюємо область обмеження переміщення курсору
			ShowCursor(false);									// Приховуємо курсор
		}
	}
};

	// Підпрограма обробки відпущення правої кнопки миші
void ChessGame::RBtnUp(int xPos, int yPos){
	if(!gameOver){
		if(rButtonDown == true){								// Перевіряємо прапор опущеності кнопки
			rButtonDown = false;								// Скидуємо прапор
			ClipCursor(NULL);									// Скидаємо область обмеження переміщення курсору
			ShowCursor(true);									// Показуємо курсор
		}
	}
};

	// Підпрограма обробки подвійного клацання правої клавіші мишки
void ChessGame::RBtnDblClk(int xPos, int yPos){
	if(!gameOver){
		if(!movingCam){
			movingCam = true;									// Встановлюємо прапор повороту камери
			Render->StartAnimation();
		}
		startCamPos = cam;										// Зберігаємо початкову позицію камери
		startTimeMovingCam = GetTickCount();					// Встановлюємо початкову мітку часу
	}
};

void ChessGame::MouseMove(int xPos, int yPos){
		
	if(!gameOver){
		if(rButtonDown){										// Якщо опущена права кнопка мишки
			cam.RotateX((xPos - OldPos.x) * SPEED_CAM_MOVE);			// Міняємо позицію камери по зміщеню курсору
			cam.RotateY((yPos - OldPos.y) * SPEED_CAM_MOVE);
				
			POINT p;
			GetCursorPos(&p);									// Встановлюємо курсор на стару позицію
			SetCursorPos(p.x - (xPos - OldPos.x), p.y - (yPos - OldPos.y));

		} else {
			// Якщо права кнопка миші не нажата, то шукаємо на яку клітинку вказує мишка
			D3DXVECTOR3 RayStart, RayDirct;

			Render->GetRay(xPos, yPos, &RayStart, &RayDirct);	// Отримуємо промінь з камери через курсор

			int newSelColumn = _cnull;							// Нова позиція вибраної курсором клітинки
			int newSelRow = _rnull;
				
			int directionColumn, directionRow;					// Направлення обходу
			int baseColumn, baseRow;							// Базові клітинки
			int currentColumn, currentRow;						// Поточні клітинки для перевірки

			if(OnBoard(&RayStart, &RayDirct)){					// Веревіряємо чи промінь пересікає дошку

				if(selColumn != _cnull || selRow != _rnull){	// Якщо нам відома "стара" виділена клітинка
															
					// Перевіряємо чи курсор не вказує на "стару" виділену клітинку
					if(!SelectedCell(selColumn, selRow, &RayStart, &RayDirct)){

						directionColumn = (selColumn < 4)? 1 : -1;
						directionRow = (selRow < 4)? 1 : -1;
						
						baseColumn = selColumn + directionColumn;
						baseRow = selRow + directionRow;

						// Робимо обхід квадратами починаючи від поточної кітинки
						for(int i = 2; newSelColumn == _cnull && newSelRow == _rnull; i += 2){
							
							for(int j = 0; j < i; j++){
								
								currentColumn = baseColumn;
								currentRow = baseRow - (directionRow * j);

								if(SelectedCell(currentColumn, currentRow, &RayStart, &RayDirct)){ 
									newSelColumn = currentColumn; 
									newSelRow = currentRow;
									break;
								}
																
								currentColumn = (baseColumn + directionColumn * (-1 -j));
								currentRow = baseRow;

								if(SelectedCell(currentColumn, currentRow, &RayStart, &RayDirct)){ 
									newSelColumn = currentColumn; 
									newSelRow = currentRow;
									break;
								}
																							
								currentColumn = (baseColumn - directionColumn * j);
								currentRow = (baseRow - (directionRow * i));

								if(SelectedCell(currentColumn, currentRow, &RayStart, &RayDirct)){ 
									newSelColumn = currentColumn; 
									newSelRow = currentRow;
									break;
								}
							
								currentColumn = (baseColumn - directionColumn * i);
								currentRow = (baseRow - directionRow * (1 + j));

								if(SelectedCell(currentColumn, currentRow, &RayStart, &RayDirct)){ 
									newSelColumn = currentColumn; 
									newSelRow = currentRow;
									break;
								}
							}

							// Перевіряємо чи не виходимо ми за дошку
							if((baseColumn == 0 || baseColumn >= 7) && (baseRow == 0 || baseRow >= 7)){
								break;
							}

							// Збільшуємо прямокутник пошуку
							if((baseColumn > 0 && baseColumn < 8)){
								baseColumn = baseColumn + directionColumn;
							}

							if((baseRow > 0 && baseRow < 8)){
								baseRow = baseRow + directionRow;
							}
						
						}
						
						// Встановлюємо нові координати виділеної клітинки
						selColumn = newSelColumn;
						selRow = newSelRow;
					}

				}
				else{
					// Якщо ми незнаємо "старої" виділеної клітинки, то пошуком по всій дошці її шукаємо
					for(int i = 0; i < 8 && newSelColumn == _cnull && newSelRow == _rnull; i++){
						for(int j = 0; j < 8 && newSelColumn == _cnull && newSelRow == _rnull; j++){
							
							if(SelectedCell(i, j, &RayStart, &RayDirct)){
								newSelColumn = i;
								newSelRow = j;
							}
						}
					}

					// Встановлюємо нові координати виділеної клітинки
					selColumn = newSelColumn;
					selRow = newSelRow;
				}

			} else{
				// Якщо курсор не вказує на дошку, то вказуємо, що немає виділеної клітинки
				selColumn = _cnull;
				selRow = _rnull;
			}
		}
	}
};

void ChessGame::WindowActive(int state){
	if(!gameOver){
		// Якщо вікно стало неактивним і встановлений прапор натиснутої правої кнопки миші
		if(state == WA_INACTIVE && rButtonDown == true){
			rButtonDown = false;									// Скидаємо прапор натиснутої кнопки
			ClipCursor(NULL);										// Скидаємо область обмеження переміщення курсору
			ShowCursor(true);										// Показуємо курсор
		}
	}
};

void ChessGame::LBtnDblClk(int xPos, int yPos){
	if(!gameOver){
		secondClick = false;
		
		// Очищюємо підсвічування
		ZeroMemory(&highlight, sizeof(highlight));
	}
};

	// Підпрограма обробки натиснутих клавіш
void ChessGame::KeyDown(int key){
	if(!gameOver){
		switch(key){
		
		case VK_LEFT:
		case VK_NUMPAD4:
			movingCam = false;			// Скидуємо прапор повороту камери
			cam.RotateX(0.1f);			// Повертаємо камеру вліво
			break;

		case VK_RIGHT:
		case VK_NUMPAD6:
			movingCam = false;
			cam.RotateX(-0.1f);			// Повертаємо камеру вправо
			break;

		case VK_DOWN:
		case VK_NUMPAD2:
			movingCam = false;
			cam.RotateY(-0.1f);			// Опускаємо камеру
			break;

		case VK_UP:
		case VK_NUMPAD8:
			movingCam = false;
			cam.RotateY(0.1f);			// Піднімаємо камеру
			break;

		case VK_ADD:
			movingCam = false;
			cam.ChangeDistance(0.1f);	// Зменшуємо дистанцію камери
			break;

		case  VK_SUBTRACT:
			movingCam = false;
			cam.ChangeDistance(-0.1f);	// Збільшуємо дистанцію камери
			break;
		}
	}
};

void ChessGame::Resize(int width, int height){
	background->Update(width, height);
	foreground->Update(width, height);
	RECT area;

	area.left = area.top = 0;
	area.right = width;
	area.bottom = height;
	text.SetArea(area);
	text.SetSize(height / TEXT2D_SCALING);
};

void ChessGame::BeforeResetDevice(){
	text.Unload();
};

void ChessGame::AfterResetDevice(){
	text.Reload();
};

void ChessGame::SetParameter(int parametrID, int parametrValue){
	
	switch(parametrID){
	
	case GAME_CHANGE_THEME:
		
		switch(parametrValue){
		case THEME_WHITE:
			delete background;
			background = new WhiteBackground(direct3DDevice, hWnd);
			board->SetTheme(THEME_WHITE);
			break;

		case THEME_COLORED:
			delete background;
			background = new ColoredBackground(direct3DDevice, hWnd);
			board->SetTheme(THEME_COLORED);
			break;

		default:
			break;
		};

		break;
	
	default:
		break;
	};
};

int ChessGame::GetParameter(int parametrID){
	
	switch(parametrID){
	case GAME_END:
		return ((gameOver)? GAME_YES : GAME_NO);
			
	default:
		return GAME_WRONG_PARAM;
	}
};

ChessGame::~ChessGame(){
	for(int i = 0; i < 8; i++)	{
		for(int j = 0; j < 8; j++)	{
			delete figures[i][j];
		}
	}

	delete board;
	delete background;
	delete foreground;
};

LocalChessGame::LocalChessGame(LPDIRECT3DDEVICE9 device, HWND handle):ChessGame(device, handle){
	unsigned field[8][8], color[8][8];

	game = new LocalGame();

	game->getChessboard(field, color);

	PlaceFigures(field, color);
};

void LocalChessGame::LBtnDown(int xPos, int yPos){
	if(!gameOver){
		// Перевіряємо чи перший раз клацнули("вибір фігури") і чи є координати клацання на дошці і обробленні всі переміщення
		if(secondClick == false && (selColumn != _cnull && selRow != _rnull) && motions.size() == 0){
			
			// Запитуємо список можливих ходів, і підсвітки для вказаної фігури
			resultMoving = game->getMoves(selRow, selColumn, highlight, moves);
			
			// Розбираємо код поверненого результату
			switch(resultMoving){

			// Успіх
			case SUCCESS_GET_MOVES:
				secondClick = true;					// Переходимо до етапу "вибору куди ходити"
				break;

			// Неправильна позиція
			case ERROR_GET_MOVES_WRONG_POSITION:
				hint->Show(TEXT("Вибрано порожнью клітинку"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
				break;

			// Фігура не того кольору
			case ERROR_GET_MOVES_WRONG_COLOR:
				hint->Show(TEXT("Ви вибрали фігуру суперника"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
				break;

			// Фігура не має ходів
			case ERROR_GET_MOVES_CANT_MOVE:
				hint->Show(TEXT("Дана фігура не може бути переміщена"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
				break;
			};

		}
		else{	
			// Перевірка чи дійсна позиція і дійсний етап "вибору куди ходити"
			if(selColumn != _cnull && selRow != _rnull && secondClick){
				
				secondClick = false;									// Скидаємо прапор "вибору куди ходити"

				// Запитуємо на можливість ходу фігури по вказаним координатам
				std::vector<MoveStruct> movestruct;
				resultMoving = game->Move(moves[selRow][selColumn], &movestruct);
				
				// Розбір значень результату
				switch(resultMoving){

				// Успіх, прохід до краю дошки(заміна фігури), пат(нічия)
				case SUCCESS_MOVE:
				case SUCCESS_MOVE_PROMOTION:
				case SUCCESS_MOVE_DRAW:

					// Переглядаємо всі необхідні ходи і добавляємо до них мітки часу(час початку і кінця руху фігури)
					for(unsigned int i = 0; i < movestruct.size(); i++){
					
						MoveData md;
						md.startRow = movestruct[i].startRow;						// Початкові координати
						md.startColumn = movestruct[i].startColumn;

						md.endRow = movestruct[i].endRow;							// Кінцеві координати
						md.endColumn = movestruct[i].endColumn;

						md.startTime = GetTickCount();								// Мітка часу початку руху

						// Мітка часу кінця руху
						if(md.endRow == _rnull || md.endColumn == _cnull) md.movingTime = DELETING_TIME;
						else{
							FLOAT intervalRow = ((FLOAT)movestruct[i].endRow - movestruct[i].startRow) * CS_FIGURE_SIZE;
							FLOAT intervalColumn = ((FLOAT)movestruct[i].endColumn - movestruct[i].startColumn) * CS_FIGURE_SIZE;
							FLOAT distanceMoving = sqrt((pow((intervalRow), 2) + pow(intervalColumn, 2)));

							md.movingTime = int(MOVING_TIME * distanceMoving);
						}

						// Перевіряємо як здійснювати переміщення фігури, "по низу" чи "по верху"
						md.typeMove = MOVING_BOTTOM;								// Переміщаємо "по низу"

						// Якщо рухаємося не по вертикалі, не по горизонталі, і не по діагоналі
						if(!((movestruct[i].startRow - movestruct[i].endRow) == 0 ||
							(movestruct[i].startColumn - movestruct[i].endColumn) == 0 ||
							abs(int(movestruct[i].startRow - movestruct[i].endRow)) == abs(int(movestruct[i].startColumn - movestruct[i].endColumn))))
						{
								
							// Вираховуємо стартові позиції перевірки
							int rows = abs((int)movestruct[i].endRow - (int)movestruct[i].startRow);
							int columns = abs((int)movestruct[i].endColumn - (int)movestruct[i].startColumn);

							unsigned findRowStart = min(movestruct[i].startRow, movestruct[i].endRow);
							unsigned findColumnStart = min(movestruct[i].startColumn, movestruct[i].endColumn);
								
							if(rows > columns){
								if(figures[findRowStart + 1][findColumnStart] != NULL ||
									figures[findRowStart + 1][findColumnStart + 1] != NULL){
									md.typeMove = MOVING_TOP;
								}
							}
							else{
								if(figures[findRowStart + 1][findColumnStart + 1] != NULL ||
									figures[findRowStart][findColumnStart + 1] != NULL){
									md.typeMove = MOVING_TOP;
								}
							}
								
						};
						
						// Перевірка на рокіровку
						if((highlight[selRow][selColumn] == SHORT_CASTLING || 
							highlight[selRow][selColumn] == LONG_CASTLING) &&
							i > 0)
						{
							md.typeMove = MOVING_TOP;							// Встановлюємо флаг "по верху"
						}

						motions.push_back(md);
					}
					
					ZeroMemory(&highlight, sizeof(highlight));						// Скидуємо підсвічування

					checkRow = _rnull;												// Скидаємо координати шаху
					checkColunm = _cnull;											// якщо звичайно він був на попередньому кроці
						
					if(movingCam){
						movingCam = false;
					}
					else{
						Render->StartAnimation();
					}

					break;

				// Шах, шах і мат
				case SUCCESS_MOVE_CHECK:
				case SUCCESS_MOVE_CHECKMATE:
					
					// Витягуємо з вектора крайню структуру, в ній міститься координати клітинки
					// на якій стоїть король якому поставлений шах або шах і мат 
					checkColunm = (*(movestruct.end() - 1)).startColumn;
					checkRow = (*(movestruct.end() - 1)).startRow;

					movestruct.erase(movestruct.end() - 1);

					for(unsigned int i = 0; i < movestruct.size(); i++){
					
						MoveData md;
						md.startRow = movestruct[i].startRow;
						md.startColumn = movestruct[i].startColumn;

						md.endRow = movestruct[i].endRow;
						md.endColumn = movestruct[i].endColumn;

						md.startTime = GetTickCount();
						if(md.endRow == _rnull || md.endColumn == _cnull) md.movingTime = DELETING_TIME;
						else{
							FLOAT intervalRow = ((FLOAT)movestruct[i].endRow - movestruct[i].startRow) * CS_FIGURE_SIZE;
							FLOAT intervalColumn = ((FLOAT)movestruct[i].endColumn - movestruct[i].startColumn) * CS_FIGURE_SIZE;
							FLOAT distanceMoving = sqrt((pow((intervalRow), 2) + pow(intervalColumn, 2)));

							md.movingTime = int(MOVING_TIME * distanceMoving);
						}

						// Перевіряємо як здійснювати переміщення фігури, "по низу" чи "по верху"
						md.typeMove = MOVING_BOTTOM;

						if(!((movestruct[i].startRow - movestruct[i].endRow) == 0 ||
							(movestruct[i].startColumn - movestruct[i].endColumn) == 0 ||
							abs(int(movestruct[i].startRow - movestruct[i].endRow)) == abs(int(movestruct[i].startColumn - movestruct[i].endColumn))))
						{
							// Вираховуємо стартові позиції перевірки
							int rows = abs((int)movestruct[i].endRow - (int)movestruct[i].startRow);
							int columns = abs((int)movestruct[i].endColumn - (int)movestruct[i].startColumn);

							unsigned findRowStart = min(movestruct[i].startRow, movestruct[i].endRow);
							unsigned findColumnStart = min(movestruct[i].startColumn, movestruct[i].endColumn);
								
							if(rows > columns){
								if(figures[findRowStart + 1][findColumnStart] != NULL ||
									figures[findRowStart + 1][findColumnStart + 1] != NULL){
									md.typeMove = MOVING_TOP;
								}
							}
							else{
								if(figures[findRowStart + 1][findColumnStart + 1] != NULL ||
									figures[findRowStart][findColumnStart + 1] != NULL){
									md.typeMove = MOVING_TOP;
								}
							}
						};

						if((highlight[selRow][selColumn] == SHORT_CASTLING || 
							highlight[selRow][selColumn] == LONG_CASTLING) &&
							i > 0)
						{
							md.typeMove = MOVING_TOP;
						}

						motions.push_back(md);
					}
					
					ZeroMemory(&highlight, sizeof(highlight));
						
					if(movingCam){
						movingCam = false;
					}
					else{
						Render->StartAnimation();
					}

					break;

				case ERROR_MOVE_WRONG_POSITION:
					
					// Перевіряємо чи не клацнули по тій самій фігурі ще раз
					if(highlight[selRow][selColumn] != MOVE_CURPOS){
						
						// Перевіряємо чи перший раз клацнули("вибір фігури") і чи є координати клацання на дошці
						if(selColumn != _cnull && selRow != _rnull){
			
							// Запитуємо список можливих ходів, і підсвітки для вказаної фігури
							resultMoving = game->getMoves(selRow, selColumn, highlight, moves);
			
							// Розбираємо код поверненого результату
							switch(resultMoving){

							// Успіх
							case SUCCESS_GET_MOVES:
								secondClick = true;					// Переходимо до етапу "вибору куди ходити"
								break;

							// Неправильна позиція
							case ERROR_GET_MOVES_WRONG_POSITION:
								
							// Фігура не того кольору
							case ERROR_GET_MOVES_WRONG_COLOR:
								
								hint->Show(TEXT("Ви неможете перемістити сюди фігуру"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
								
								// Очищюємо підсвічування
								ZeroMemory(&highlight, sizeof(highlight));
								break;

							// Фігура не має ходів
							case ERROR_GET_MOVES_CANT_MOVE:
								
								hint->Show(TEXT("Дана фігура не може бути переміщена"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
								
								// Очищюємо підсвічування
								ZeroMemory(&highlight, sizeof(highlight));
								break;
							};
						}

					}
					else{
						// Очищюємо підсвічування
						ZeroMemory(&highlight, sizeof(highlight));
					}
					break;
				};

			}else{
				secondClick = false;
				
				// Очищюємо підсвічування
				ZeroMemory(&highlight, sizeof(highlight));
			}
		}
	}
};

void LocalChessGame::Timer(int time){
	if(!gameOver){
		if(motions.size() == 0){

			if(resultMoving == SUCCESS_MOVE_PROMOTION){
				std::vector<CLButton> buttons;
				CLWindow *selectFigure;
				CLButton button;
				HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

				selectFigure = new CLWindow(hWnd, hInst);

				button.BtnID = ID_BUTTON_Q;
				button.BtnText = TEXT("Королева (Ферзь)");
				button.BtnNote = TEXT("Претворити пішака в королеву");
				button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_QUEEN));
				buttons.push_back(button);
				button.BtnID = ID_BUTTON_R;
				button.BtnText = TEXT("Тура");
				button.BtnNote = TEXT("Претворити пішака в туру");
				button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_ROOK));
				buttons.push_back(button);
				button.BtnID = ID_BUTTON_B;
				button.BtnText = TEXT("Офіцер (Слон)");
				button.BtnNote = TEXT("Претворити пішака в офіцера");
				button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_BISHOP));
				buttons.push_back(button);
				button.BtnID = ID_BUTTON_N;
				button.BtnText = TEXT("Кінь");
				button.BtnNote = TEXT("Претворити пішака в коня");
				button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_KNIGHT));
				buttons.push_back(button);

				int figType = selectFigure->Show(TEXT("Перетворення пішака"), buttons, false);
				delete selectFigure;

				std::vector<MoveStruct> movestruct;
							
				switch(figType){
				case ID_BUTTON_Q:
					movestruct.clear();
					resultMoving = game->Promotion(PROM_QUEEN, &movestruct);
					figures[movestruct[0].startRow][movestruct[0].startColumn]->ChangeModel(CS_QUEEN);
					break;

				case ID_BUTTON_R:
					resultMoving = game->Promotion(PROM_ROCK, &movestruct);
					figures[movestruct[0].startRow][movestruct[0].startColumn]->ChangeModel(CS_ROOK);
					break;

				case ID_BUTTON_B:
					resultMoving = game->Promotion(PROM_BISHOP, &movestruct);
					figures[movestruct[0].startRow][movestruct[0].startColumn]->ChangeModel(CS_BISHOP);
					break;

				case ID_BUTTON_N:
					resultMoving = game->Promotion(PROM_KNIGHT, &movestruct);
					figures[movestruct[0].startRow][movestruct[0].startColumn]->ChangeModel(CS_KNIGHT);
					break;
				}

				switch(resultMoving){

				case SUCCESS_MOVE:
				case SUCCESS_MOVE_PROMOTION:
				case SUCCESS_MOVE_DRAW:
					break;


				case SUCCESS_MOVE_CHECK:
				case SUCCESS_MOVE_CHECKMATE:

					ZeroMemory(&highlight, sizeof(highlight));
					checkColunm = (*(movestruct.end() - 1)).startColumn;
					checkRow = (*(movestruct.end() - 1)).startRow;
					movestruct.erase(movestruct.end() - 1);
					break;

				case ERROR_PROMOTION_WRONG_TYPE:

					ZeroMemory(&highlight, sizeof(highlight));
					hint->Show(TEXT("Ви вказали неправильну фігуру"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
					break;
				};

				startTimeMovingCam = GetTickCount();
				startCamPos = cam;
				movingCam = true;
			}

			if(resultMoving == SUCCESS_MOVE_DRAW){

				RECT windowClient;
				GetClientRect(hWnd, &windowClient);
				text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, LOCAL_DRAW, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
				gameOver = true;
				selRow = _rnull;
				selColumn = _cnull;
			}

			if(resultMoving == SUCCESS_MOVE_CHECKMATE){
				RECT windowClient;
				GetClientRect(hWnd, &windowClient);
				if(game->getTurn() == WHITE){
					text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, LOCAL_BLACK_WIN, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
				}
				else{
					text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, LOCAL_WHITE_WIN, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
				}
				gameOver = true;
				selRow = _rnull;
				selColumn = _cnull;
			}
		}
		
		for(unsigned int i = 0; i < motions.size(); i++){
			if( time < motions[i].startTime + motions[i].movingTime){
				if(motions[i].endRow == _rnull || motions[i].endColumn == _cnull){
					if(figures[motions[i].startRow][motions[i].startColumn] != NULL){	// Якщо фігура вже встигла переміститися на нову позицію
						if(transperentRow == _rnull && transperentColumn == _cnull){
							transperentRow = motions[i].startRow;
							transperentColumn = motions[i].startColumn;
						}
						if(transperentRow == motions[i].startRow && transperentColumn == motions[i].startColumn){
							figures[motions[i].startRow][motions[i].startColumn]->SetTransparency(1.0f - ( (float)time - motions[i].startTime ) / (float)DELETING_TIME);
						}
					}
				}
				else{
					Coordinates strtPos = Pos[motions[i].startRow][motions[i].startColumn];
					Coordinates endPos = Pos[motions[i].endRow][motions[i].endColumn];
			
					// Вираховуємо проміжні положення фігури
					// позиція_фігури = поч_позиція + ( кін_позиція - поч_позиція ) * ( ( поточний_час - початковий_час ) / час_анімації )
					Coordinates curPos;
					FLOAT position = ( ( (FLOAT)time - motions[i].startTime ) / (FLOAT)motions[i].movingTime);

					curPos.x = strtPos.x + ( endPos.x - strtPos.x ) * position;
					curPos.z = strtPos.z + ( endPos.z - strtPos.z ) * position;

					if(motions[i].typeMove == MOVING_BOTTOM){
						curPos.y = strtPos.y;
					}
					else{
						curPos.y = 4 * position * (1 - position);
					}

					D3DXMATRIX m;
					D3DXMatrixTranslation(&m, curPos.x, curPos.y, curPos.z);
					figures[motions[i].startRow][motions[i].startColumn]->SetWorldMatrix(&m);
				}
			}
			else{
				if(motions[i].endRow == _rnull || motions[i].endColumn == _cnull){
					if(figures[motions[i].startRow][motions[i].startColumn] != NULL){
						if(transperentRow == motions[i].startRow && transperentColumn == motions[i].startColumn){
							transperentRow = _rnull;
							transperentColumn = _cnull;
						}
						delete figures[motions[i].startRow][motions[i].startColumn];
						figures[motions[i].startRow][motions[i].startColumn] = NULL;
						motions.erase(motions.begin() + i);
					}
				}
				else{
					if(figures[motions[i].endRow][motions[i].endColumn] == NULL){
					
						Coordinates curPos = Pos[motions[i].endRow][motions[i].endColumn];

						D3DXMATRIX m;
						D3DXMatrixTranslation(&m, curPos.x, curPos.y, curPos.z);
						figures[motions[i].startRow][motions[i].startColumn]->SetWorldMatrix(&m);

						figures[motions[i].endRow][motions[i].endColumn] = figures[motions[i].startRow][motions[i].startColumn];
						figures[motions[i].startRow][motions[i].startColumn] = NULL;
						motions.erase(motions.begin() + i);
					
					}
				}

				if(motions.size() == 0){
					startTimeMovingCam = GetTickCount();							// Початковий час переміщення камери
					startCamPos = cam;												// Початкове положення камери
					movingCam = true;												// Переміщуємо камеру іншому гравцю
				}
			}
		}

		if(movingCam){
			
			// Отримуємо гравця, який ходить
			int player = game->getTurn();
			
			// Отримуємо кінцеві параметри позиції камери
			FLOAT endX = (player == WHITE)? WHITE_CAM_ANGLE_X : BLACK_CAM_ANGLE_X ;
			FLOAT endY = (player == WHITE)? WHITE_CAM_ANGLE_Y : BLACK_CAM_ANGLE_Y ;
			FLOAT endDistance = (player == WHITE)? WHITE_CAM_DIST : BLACK_CAM_DIST ;

			// Отримуємо початкові(збережені) параметри позиції камери
			FLOAT startX = startCamPos.GetAngelX();
			FLOAT startY = startCamPos.GetAngelY();
			FLOAT startDistance = startCamPos.GetDistance();

			// Повертаємо в найменшу сторону
			if(startX > ((player == WHITE)? WHITE_CAM_ANGLE_X : BLACK_CAM_ANGLE_X) + D3DXToRadian(180.0f)){
				startX = startX - D3DXToRadian(360.0f);
			}
			if(startX < ((player == WHITE)? WHITE_CAM_ANGLE_X : BLACK_CAM_ANGLE_X) - D3DXToRadian(180.0f)){
				startX = startX + D3DXToRadian(360.0f);
			}
			
			// Знаходимо найбільшу дистанцію повороту камери
			FLOAT maxAngle = max(abs(endX - abs(startX)), abs(endY - abs(startY)));
			maxAngle = max(maxAngle, abs(endDistance - abs(startDistance)));
			
			// Ділимо дистанцію на "одиничний кут"
			maxAngle = maxAngle / TIME_PER_ANGLE;

			// Перевіряємо, чи не закінчився час повороту камери
			// Час_повороту = maxAngle * MOVING_CAMERA
			if(time <= startTimeMovingCam + maxAngle * MOVING_CAMERA){
				
				// Вираховуємо пройдений час в діапазоні від 0 до 1 (початок і кінець відповідно)
				FLOAT shift = (((FLOAT)time - (FLOAT)startTimeMovingCam) / (FLOAT)(maxAngle * MOVING_CAMERA));
				
				// Передаємо пройдений час "функції повороту камери"
				FLOAT koeficient = MOVING_CAM_FUNCTION(shift);
				
				// Поточне положення вираховуємо по формулі: 
				// початкове_положення + (кінцеве_положення - початкове_положення) * коефіцієнт_повороту_за_пройдений_час
				FLOAT deltaX = startX + (endX - startX) * koeficient;
				FLOAT deltaY = startY + (endY - startY)  * koeficient;
				FLOAT deltaDist = startDistance + (endDistance - startDistance)  * koeficient;
				
				// Встановлюємо нові значення камери
				cam.SetAngleX(deltaX);
				cam.SetAngleY(deltaY);
				cam.SetDistance(deltaDist);
			}
			else{
				// Якщо час вийшов, то встановлюємо кінцеві параметри положення камери
				cam.SetAngleX(endX);
				cam.SetAngleY(endY);
				cam.SetDistance(endDistance);
				
				// Скидуємо прапор повороту
				movingCam = false;

				// Отримуємо положення курсору
				POINT p;
				GetCursorPos(&p);
				ScreenToClient(hWnd, &p);

				// Підсвічуємо клітинку на яку вказує курсор пілся повороту дошки
				MouseMove(p.x, p.y);
				Render->EndAnimation();
			}
		}
	}
	else{
		cam.RotateX(-0.001f);
	}
};

LocalChessGame::~LocalChessGame(){
	delete game;
};

NetChessGame::NetChessGame(LPDIRECT3DDEVICE9 device, HWND handle, Color playerColor):ChessGame(device, handle){

	game = new NetworkGame(playerColor);

	unsigned field[8][8], color[8][8];

	game->getChessboard(field, color);

	PlaceFigures(field, color);

	autoRotationCam = false;
	promotion = 0;
	promotionColumn = _cnull;
	promotionRow = _rnull;
};

void NetChessGame::LBtnDown(int xPos, int yPos){
	if(!gameOver){
		// Перевіряємо чи перший раз клацнули("вибір фігури") і чи є координати клацання на дошці і обробленні всі переміщення
		if(secondClick == false && (selColumn != _cnull && selRow != _rnull) && motions.size() == 0){
			
			// Запитуємо список можливих ходів, і підсвітки для вказаної фігури
			resultMoving = game->getMoves(selRow, selColumn, highlight, moves);
			
			// Розбираємо код поверненого результату
			switch(resultMoving){

			// Успіх
			case SUCCESS_GET_MOVES:
				secondClick = true;					// Переходимо до етапу "вибору куди ходити"
				break;

			// Неправильна позиція
			case ERROR_GET_MOVES_WRONG_POSITION:
				hint->Show(TEXT("Вибрано порожнью клітинку"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
				break;

			// Фігура не того кольору
			case ERROR_GET_MOVES_WRONG_COLOR:
				hint->Show(TEXT("Ви вибрали фігуру суперника"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
				break;

			// Фігура не має ходів
			case ERROR_GET_MOVES_CANT_MOVE:
				hint->Show(TEXT("Дана фігура не може бути переміщена"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
				break;
			};

		}
		else{	
			// Перевірка чи дійсна позиція і дійсний етап "вибору куди ходити"
			if(selColumn != _cnull && selRow != _rnull && secondClick){
				
				secondClick = false;									// Скидаємо прапор "вибору куди ходити"

				char *data;
				unsigned dataLength;
				// Запитуємо на можливість ходу фігури по вказаним координатам
				std::vector<MoveStruct> movestruct;
				resultMoving = game->Move(moves[selRow][selColumn], &movestruct, data, dataLength);
				
				if(dataLength != 0){
					if(client != NULL){
						client->SendData(data, dataLength);
					}
					else{
						server->SendData(data, dataLength);
					}
				}
				// Розбір значень результату
				switch(resultMoving){

				// Успіх, прохід до краю дошки(заміна фігури), пат(нічия)
				case SUCCESS_MOVE:
				case SUCCESS_MOVE_PROMOTION:
				case SUCCESS_MOVE_DRAW:

					// Переглядаємо всі необхідні ходи і добавляємо до них мітки часу(час початку і кінця руху фігури)
					for(unsigned int i = 0; i < movestruct.size(); i++){
					
						MoveData md;
						md.startRow = movestruct[i].startRow;						// Початкові координати
						md.startColumn = movestruct[i].startColumn;

						md.endRow = movestruct[i].endRow;							// Кінцеві координати
						md.endColumn = movestruct[i].endColumn;

						md.startTime = GetTickCount();								// Мітка часу початку руху

						// Мітка часу кінця руху
						if(md.endRow == _rnull || md.endColumn == _cnull) md.movingTime = DELETING_TIME;
						else{
							FLOAT intervalRow = ((FLOAT)movestruct[i].endRow - movestruct[i].startRow) * CS_FIGURE_SIZE;
							FLOAT intervalColumn = ((FLOAT)movestruct[i].endColumn - movestruct[i].startColumn) * CS_FIGURE_SIZE;
							FLOAT distanceMoving = sqrt((pow((intervalRow), 2) + pow(intervalColumn, 2)));

							md.movingTime = int(MOVING_TIME * distanceMoving);
						}

						// Перевіряємо як здійснювати переміщення фігури, "по низу" чи "по верху"
						md.typeMove = MOVING_BOTTOM;								// Переміщаємо "по низу"

						// Якщо рухаємося не по вертикалі, не по горизонталі, і не по діагоналі
						if(!((movestruct[i].startRow - movestruct[i].endRow) == 0 ||
							(movestruct[i].startColumn - movestruct[i].endColumn) == 0 ||
							abs(int(movestruct[i].startRow - movestruct[i].endRow)) == abs(int(movestruct[i].startColumn - movestruct[i].endColumn))))
						{
								
							// Вираховуємо стартові позиції перевірки
							int rows = abs((int)movestruct[i].endRow - (int)movestruct[i].startRow);
							int columns = abs((int)movestruct[i].endColumn - (int)movestruct[i].startColumn);

							unsigned findRowStart = min(movestruct[i].startRow, movestruct[i].endRow);
							unsigned findColumnStart = min(movestruct[i].startColumn, movestruct[i].endColumn);
								
							if(rows > columns){
								if(figures[findRowStart + 1][findColumnStart] != NULL ||
									figures[findRowStart + 1][findColumnStart + 1] != NULL){
									md.typeMove = MOVING_TOP;
								}
							}
							else{
								if(figures[findRowStart + 1][findColumnStart + 1] != NULL ||
									figures[findRowStart][findColumnStart + 1] != NULL){
									md.typeMove = MOVING_TOP;
								}
							}
								
						};
						
						// Перевірка на рокіровку
						if((highlight[selRow][selColumn] == SHORT_CASTLING || 
							highlight[selRow][selColumn] == LONG_CASTLING) &&
							i > 0)
						{
							md.typeMove = MOVING_TOP;							// Встановлюємо флаг "по верху"
						}

						motions.push_back(md);
					}
					
					ZeroMemory(&highlight, sizeof(highlight));						// Скидуємо підсвічування

					checkRow = _rnull;												// Скидаємо координати шаху
					checkColunm = _cnull;											// якщо звичайно він був на попередньому кроці
						
					if(movingCam){
						movingCam = false;
					}
					else{
						Render->StartAnimation();
					}

					break;

				// Шах, шах і мат
				case SUCCESS_MOVE_CHECK:
				case SUCCESS_MOVE_CHECKMATE:
					
					// Витягуємо з вектора крайню структуру, в ній міститься координати клітинки
					// на якій стоїть король якому поставлений шах або шах і мат 
					checkColunm = (*(movestruct.end() - 1)).startColumn;
					checkRow = (*(movestruct.end() - 1)).startRow;

					movestruct.erase(movestruct.end() - 1);

					for(unsigned int i = 0; i < movestruct.size(); i++){
					
						MoveData md;
						md.startRow = movestruct[i].startRow;
						md.startColumn = movestruct[i].startColumn;

						md.endRow = movestruct[i].endRow;
						md.endColumn = movestruct[i].endColumn;

						md.startTime = GetTickCount();
						if(md.endRow == _rnull || md.endColumn == _cnull) md.movingTime = DELETING_TIME;
						else{
							FLOAT intervalRow = ((FLOAT)movestruct[i].endRow - movestruct[i].startRow) * CS_FIGURE_SIZE;
							FLOAT intervalColumn = ((FLOAT)movestruct[i].endColumn - movestruct[i].startColumn) * CS_FIGURE_SIZE;
							FLOAT distanceMoving = sqrt((pow((intervalRow), 2) + pow(intervalColumn, 2)));

							md.movingTime = int(MOVING_TIME * distanceMoving);
						}

						// Перевіряємо як здійснювати переміщення фігури, "по низу" чи "по верху"
						md.typeMove = MOVING_BOTTOM;

						if(!((movestruct[i].startRow - movestruct[i].endRow) == 0 ||
							(movestruct[i].startColumn - movestruct[i].endColumn) == 0 ||
							abs(int(movestruct[i].startRow - movestruct[i].endRow)) == abs(int(movestruct[i].startColumn - movestruct[i].endColumn))))
						{
							// Вираховуємо стартові позиції перевірки
							int rows = abs((int)movestruct[i].endRow - (int)movestruct[i].startRow);
							int columns = abs((int)movestruct[i].endColumn - (int)movestruct[i].startColumn);

							unsigned findRowStart = min(movestruct[i].startRow, movestruct[i].endRow);
							unsigned findColumnStart = min(movestruct[i].startColumn, movestruct[i].endColumn);
								
							if(rows > columns){
								if(figures[findRowStart + 1][findColumnStart] != NULL ||
									figures[findRowStart + 1][findColumnStart + 1] != NULL){
									md.typeMove = MOVING_TOP;
								}
							}
							else{
								if(figures[findRowStart + 1][findColumnStart + 1] != NULL ||
									figures[findRowStart][findColumnStart + 1] != NULL){
									md.typeMove = MOVING_TOP;
								}
							}
						};

						if((highlight[selRow][selColumn] == SHORT_CASTLING || 
							highlight[selRow][selColumn] == LONG_CASTLING) &&
							i > 0)
						{
							md.typeMove = MOVING_TOP;
						}

						motions.push_back(md);
					}
					
					ZeroMemory(&highlight, sizeof(highlight));
						
					if(movingCam){
						movingCam = false;
					}
					else{
						Render->StartAnimation();
					}

					break;

				case ERROR_MOVE_WRONG_POSITION:
					
					// Перевіряємо чи не клацнули по тій самій фігурі ще раз
					if(highlight[selRow][selColumn] != MOVE_CURPOS){
						
						// Перевіряємо чи перший раз клацнули("вибір фігури") і чи є координати клацання на дошці
						if(selColumn != _cnull && selRow != _rnull){
			
							// Запитуємо список можливих ходів, і підсвітки для вказаної фігури
							resultMoving = game->getMoves(selRow, selColumn, highlight, moves);
			
							// Розбираємо код поверненого результату
							switch(resultMoving){

							// Успіх
							case SUCCESS_GET_MOVES:
								secondClick = true;					// Переходимо до етапу "вибору куди ходити"
								break;

							// Неправильна позиція
							case ERROR_GET_MOVES_WRONG_POSITION:
								
							// Фігура не того кольору
							case ERROR_GET_MOVES_WRONG_COLOR:
								
								hint->Show(TEXT("Ви неможете перемістити сюди фігуру"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
								
								// Очищюємо підсвічування
								ZeroMemory(&highlight, sizeof(highlight));
								break;

							// Фігура не має ходів
							case ERROR_GET_MOVES_CANT_MOVE:
								
								hint->Show(TEXT("Дана фігура не може бути переміщена"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
								
								// Очищюємо підсвічування
								ZeroMemory(&highlight, sizeof(highlight));
								break;
							};
						}

					}
					else{
						// Очищюємо підсвічування
						ZeroMemory(&highlight, sizeof(highlight));
					}
					break;
				};

			}else{
				secondClick = false;
				
				// Очищюємо підсвічування
				ZeroMemory(&highlight, sizeof(highlight));
			}
		}
	}
};

void NetChessGame::Timer(int time){
	if(!gameOver){
		if(motions.size() == 0){

			if(resultMoving == SUCCESS_MOVE_PROMOTION){
				std::vector<CLButton> buttons;
				CLWindow *selectFigure;
				CLButton button;
				HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

				selectFigure = new CLWindow(hWnd, hInst);

				button.BtnID = ID_BUTTON_Q;
				button.BtnText = TEXT("Королева (Ферзь)");
				button.BtnNote = TEXT("Претворити пішака в королеву");
				button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_QUEEN));
				buttons.push_back(button);
				button.BtnID = ID_BUTTON_R;
				button.BtnText = TEXT("Тура");
				button.BtnNote = TEXT("Претворити пішака в туру");
				button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_ROOK));
				buttons.push_back(button);
				button.BtnID = ID_BUTTON_B;
				button.BtnText = TEXT("Офіцер (Слон)");
				button.BtnNote = TEXT("Претворити пішака в офіцера");
				button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_BISHOP));
				buttons.push_back(button);
				button.BtnID = ID_BUTTON_N;
				button.BtnText = TEXT("Кінь");
				button.BtnNote = TEXT("Претворити пішака в коня");
				button.BtnIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_KNIGHT));
				buttons.push_back(button);

				int figType = selectFigure->Show(TEXT("Перетворення пішака"), buttons, false);
				delete selectFigure;

				std::vector<MoveStruct> movestruct;
							
				char *data;
				unsigned dataLength;

				switch(figType){
				case ID_BUTTON_Q:
					movestruct.clear();
					resultMoving = game->Promotion(PROM_QUEEN, &movestruct, data, dataLength);
					figures[movestruct[0].startRow][movestruct[0].startColumn]->ChangeModel(CS_QUEEN);
					break;

				case ID_BUTTON_R:
					resultMoving = game->Promotion(PROM_ROCK, &movestruct, data, dataLength);
					figures[movestruct[0].startRow][movestruct[0].startColumn]->ChangeModel(CS_ROOK);
					break;

				case ID_BUTTON_B:
					resultMoving = game->Promotion(PROM_BISHOP, &movestruct, data, dataLength);
					figures[movestruct[0].startRow][movestruct[0].startColumn]->ChangeModel(CS_BISHOP);
					break;

				case ID_BUTTON_N:
					resultMoving = game->Promotion(PROM_KNIGHT, &movestruct, data, dataLength);
					figures[movestruct[0].startRow][movestruct[0].startColumn]->ChangeModel(CS_KNIGHT);
					break;
				}

				if(dataLength != 0){
					if(client != NULL){
						client->SendData(data, dataLength);
					}
					else{
						server->SendData(data, dataLength);
					}
				}

				switch(resultMoving){

				case SUCCESS_MOVE:
				case SUCCESS_MOVE_PROMOTION:
				case SUCCESS_MOVE_DRAW:
					break;


				case SUCCESS_MOVE_CHECK:
				case SUCCESS_MOVE_CHECKMATE:

					ZeroMemory(&highlight, sizeof(highlight));
					checkColunm = (*(movestruct.end() - 1)).startColumn;
					checkRow = (*(movestruct.end() - 1)).startRow;
					movestruct.erase(movestruct.end() - 1);
					break;

				case ERROR_PROMOTION_WRONG_TYPE:

					ZeroMemory(&highlight, sizeof(highlight));
					hint->Show(TEXT("Ви вказали неправильну фігуру"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
					break;
				};
			}

			if(promotion != 0 && promotionColumn != _cnull && promotionRow != _rnull){
				switch(promotion){
				case PROM_QUEEN:
					figures[promotionRow][promotionColumn]->ChangeModel(CS_QUEEN);
					break;
				case PROM_ROCK:
					figures[promotionRow][promotionColumn]->ChangeModel(CS_ROOK);
					break;
				case PROM_BISHOP:
					figures[promotionRow][promotionColumn]->ChangeModel(CS_BISHOP);
					break;
				case PROM_KNIGHT:
					figures[promotionRow][promotionColumn]->ChangeModel(CS_KNIGHT);
					break;
				};

				promotion = 0;
				promotionColumn = _cnull;
				promotionRow = _rnull;
			}

			if(resultMoving == SUCCESS_MOVE_DRAW){

				RECT windowClient;
				GetClientRect(hWnd, &windowClient);
				text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, NET_DRAW, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
				gameOver = true;
				selRow = _rnull;
				selColumn = _cnull;
			}

			if(resultMoving == SUCCESS_MOVE_CHECKMATE){
				RECT windowClient;
				GetClientRect(hWnd, &windowClient);
				if(game->getTurn() == WHITE){
					if(game->getSide() == BLACK){
						text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, NET_YOU_WIN, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
					}
					else{
						text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, NET_YOU_LOSE, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
					}
				}
				else{
					if(game->getSide() == BLACK){
						text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, NET_YOU_LOSE, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
					}
					else{
						text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, NET_YOU_WIN, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
					}
				}
				gameOver = true;
				selRow = _rnull;
				selColumn = _cnull;
			}

			if(!gameOver && !movingCam){
				if(autoRotationCam){
					startTimeMovingCam = GetTickCount();							// Початковий час переміщення камери
					startCamPos = cam;												// Початкове положення камери
					movingCam = true;												// Переміщуємо камеру іншому гравцю
				}
				else {
					Render->EndAnimation();
				}
			}
		}
		
		for(unsigned int i = 0; i < motions.size(); i++){
			if( time < motions[i].startTime + motions[i].movingTime){
				if(motions[i].endRow == _rnull || motions[i].endColumn == _cnull){
					if(figures[motions[i].startRow][motions[i].startColumn] != NULL){	// Якщо фігура вже встигла переміститися на нову позицію
						if(transperentRow == _rnull && transperentColumn == _cnull){
							transperentRow = motions[i].startRow;
							transperentColumn = motions[i].startColumn;
						}
						if(transperentRow == motions[i].startRow && transperentColumn == motions[i].startColumn){
							figures[motions[i].startRow][motions[i].startColumn]->SetTransparency(1.0f - ( (float)time - motions[i].startTime ) / (float)DELETING_TIME);
						}
					}
				}
				else{
					Coordinates strtPos = Pos[motions[i].startRow][motions[i].startColumn];
					Coordinates endPos = Pos[motions[i].endRow][motions[i].endColumn];
			
					// Вираховуємо проміжні положення фігури
					// позиція_фігури = поч_позиція + ( кін_позиція - поч_позиція ) * ( ( поточний_час - початковий_час ) / час_анімації )
					Coordinates curPos;
					FLOAT position = ( ( (FLOAT)time - motions[i].startTime ) / (FLOAT)motions[i].movingTime);

					curPos.x = strtPos.x + ( endPos.x - strtPos.x ) * position;
					curPos.z = strtPos.z + ( endPos.z - strtPos.z ) * position;

					if(motions[i].typeMove == MOVING_BOTTOM){
						curPos.y = strtPos.y;
					}
					else{
						curPos.y = 4 * position * (1 - position);
					}

					D3DXMATRIX m;
					D3DXMatrixTranslation(&m, curPos.x, curPos.y, curPos.z);
					figures[motions[i].startRow][motions[i].startColumn]->SetWorldMatrix(&m);
				}
			}
			else{
				if(motions[i].endRow == _rnull || motions[i].endColumn == _cnull){
					if(figures[motions[i].startRow][motions[i].startColumn] != NULL){
						if(transperentRow == motions[i].startRow && transperentColumn == motions[i].startColumn){
							transperentRow = _rnull;
							transperentColumn = _cnull;
						}
						delete figures[motions[i].startRow][motions[i].startColumn];
						figures[motions[i].startRow][motions[i].startColumn] = NULL;
						motions.erase(motions.begin() + i);
					}
				}
				else{
					if(figures[motions[i].endRow][motions[i].endColumn] == NULL){
					
						Coordinates curPos = Pos[motions[i].endRow][motions[i].endColumn];

						D3DXMATRIX m;
						D3DXMatrixTranslation(&m, curPos.x, curPos.y, curPos.z);
						figures[motions[i].startRow][motions[i].startColumn]->SetWorldMatrix(&m);

						figures[motions[i].endRow][motions[i].endColumn] = figures[motions[i].startRow][motions[i].startColumn];
						figures[motions[i].startRow][motions[i].startColumn] = NULL;
						motions.erase(motions.begin() + i);
					
					}
				}
			}
		}

		if(movingCam){
			
			// Отримуємо гравця, який ходить
			int player = game->getSide();
			
			// Отримуємо кінцеві параметри позиції камери
			FLOAT endX = (player == WHITE)? WHITE_CAM_ANGLE_X : BLACK_CAM_ANGLE_X ;
			FLOAT endY = (player == WHITE)? WHITE_CAM_ANGLE_Y : BLACK_CAM_ANGLE_Y ;
			FLOAT endDistance = (player == WHITE)? WHITE_CAM_DIST : BLACK_CAM_DIST ;

			// Отримуємо початкові(збережені) параметри позиції камери
			FLOAT startX = startCamPos.GetAngelX();
			FLOAT startY = startCamPos.GetAngelY();
			FLOAT startDistance = startCamPos.GetDistance();

			// Повертаємо в найменшу сторону
			if(startX > ((player == WHITE)? WHITE_CAM_ANGLE_X : BLACK_CAM_ANGLE_X) + D3DXToRadian(180.0f)){
				startX = startX - D3DXToRadian(360.0f);
			}
			if(startX < ((player == WHITE)? WHITE_CAM_ANGLE_X : BLACK_CAM_ANGLE_X) - D3DXToRadian(180.0f)){
				startX = startX + D3DXToRadian(360.0f);
			}
			
			// Знаходимо найбільшу дистанцію повороту камери
			FLOAT maxAngle = max(abs(endX - abs(startX)), abs(endY - abs(startY)));
			maxAngle = max(maxAngle, abs(endDistance - abs(startDistance)));
			
			// Ділимо дистанцію на "одиничний кут"
			maxAngle = maxAngle / TIME_PER_ANGLE;

			// Перевіряємо, чи не закінчився час повороту камери
			// Час_повороту = maxAngle * MOVING_CAMERA
			if(time <= startTimeMovingCam + maxAngle * MOVING_CAMERA){
				
				// Вираховуємо пройдений час в діапазоні від 0 до 1 (початок і кінець відповідно)
				FLOAT shift = (((FLOAT)time - (FLOAT)startTimeMovingCam) / (FLOAT)(maxAngle * MOVING_CAMERA));
				
				// Передаємо пройдений час "функції повороту камери"
				FLOAT koeficient = MOVING_CAM_FUNCTION(shift);
				
				// Поточне положення вираховуємо по формулі: 
				// початкове_положення + (кінцеве_положення - початкове_положення) * коефіцієнт_повороту_за_пройдений_час
				FLOAT deltaX = startX + (endX - startX) * koeficient;
				FLOAT deltaY = startY + (endY - startY)  * koeficient;
				FLOAT deltaDist = startDistance + (endDistance - startDistance)  * koeficient;
				
				// Встановлюємо нові значення камери
				cam.SetAngleX(deltaX);
				cam.SetAngleY(deltaY);
				cam.SetDistance(deltaDist);
			}
			else{
				// Якщо час вийшов, то встановлюємо кінцеві параметри положення камери
				cam.SetAngleX(endX);
				cam.SetAngleY(endY);
				cam.SetDistance(endDistance);
				
				// Скидуємо прапор повороту
				movingCam = false;

				// Отримуємо положення курсору
				POINT p;
				GetCursorPos(&p);
				ScreenToClient(hWnd, &p);

				// Підсвічуємо клітинку на яку вказує курсор пілся повороту дошки
				MouseMove(p.x, p.y);
				Render->EndAnimation();
			}
		}
	}
	else{
		cam.RotateX(-0.001f);
	}
};

void NetChessGame::SendData(char *data, int len){
	
	std::vector<MoveStruct> movestruct;
	
	resultMoving = game->dispatchMove(&movestruct, promotion, data, len);

	if(resultMoving == SUCCESS_MOVE_CHECK || resultMoving == SUCCESS_MOVE_CHECKMATE){
		
		// Витягуємо з вектора крайню структуру, в ній міститься координати клітинки
		// на якій стоїть король якому поставлений шах або шах і мат 
		checkColunm = (*(movestruct.end() - 1)).startColumn;
		checkRow = (*(movestruct.end() - 1)).startRow;

		movestruct.erase(movestruct.end() - 1);
	
	}

	if(promotion != 0){

		promotionColumn = (*(movestruct.end() - 1)).startColumn;
		promotionRow = (*(movestruct.end() - 1)).startRow;

		movestruct.erase(movestruct.end() - 1);
	}

	// Розбір значень результату
	switch(resultMoving){

	// Успіх, прохід до краю дошки(заміна фігури), пат(нічия)
	case SUCCESS_MOVE:
	case SUCCESS_MOVE_PROMOTION:
	case SUCCESS_MOVE_DRAW:

		// Переглядаємо всі необхідні ходи і добавляємо до них мітки часу(час початку і кінця руху фігури)
		for(unsigned int i = 0; i < movestruct.size(); i++){
					
			MoveData md;
			md.startRow = movestruct[i].startRow;						// Початкові координати
			md.startColumn = movestruct[i].startColumn;

			md.endRow = movestruct[i].endRow;							// Кінцеві координати
			md.endColumn = movestruct[i].endColumn;

			md.startTime = GetTickCount();								// Мітка часу початку руху

			// Мітка часу кінця руху
			if(md.endRow == _rnull || md.endColumn == _cnull) md.movingTime = DELETING_TIME;
			else{
				FLOAT intervalRow = ((FLOAT)movestruct[i].endRow - movestruct[i].startRow) * CS_FIGURE_SIZE;
				FLOAT intervalColumn = ((FLOAT)movestruct[i].endColumn - movestruct[i].startColumn) * CS_FIGURE_SIZE;
				FLOAT distanceMoving = sqrt((pow((intervalRow), 2) + pow(intervalColumn, 2)));

				md.movingTime = int(MOVING_TIME * distanceMoving);
			}

			// Перевіряємо як здійснювати переміщення фігури, "по низу" чи "по верху"
			md.typeMove = MOVING_BOTTOM;								// Переміщаємо "по низу"

			// Якщо рухаємося не по вертикалі, не по горизонталі, і не по діагоналі
			if(!((movestruct[i].startRow - movestruct[i].endRow) == 0 ||
				(movestruct[i].startColumn - movestruct[i].endColumn) == 0 ||
				abs(int(movestruct[i].startRow - movestruct[i].endRow)) == abs(int(movestruct[i].startColumn - movestruct[i].endColumn))))
			{
								
				// Вираховуємо стартові позиції перевірки
				int rows = abs((int)movestruct[i].endRow - (int)movestruct[i].startRow);
				int columns = abs((int)movestruct[i].endColumn - (int)movestruct[i].startColumn);

				unsigned findRowStart = min(movestruct[i].startRow, movestruct[i].endRow);
				unsigned findColumnStart = min(movestruct[i].startColumn, movestruct[i].endColumn);
								
				if(rows > columns){
					if(figures[findRowStart + 1][findColumnStart] != NULL ||
						figures[findRowStart + 1][findColumnStart + 1] != NULL){
						md.typeMove = MOVING_TOP;
					}
				}
				else{
					if(figures[findRowStart + 1][findColumnStart + 1] != NULL ||
						figures[findRowStart][findColumnStart + 1] != NULL){
						md.typeMove = MOVING_TOP;
					}
				}
								
			};
						
			// Перевірка на рокіровку
			if((highlight[selRow][selColumn] == SHORT_CASTLING || 
				highlight[selRow][selColumn] == LONG_CASTLING) &&
				i > 0)
			{
				md.typeMove = MOVING_TOP;							// Встановлюємо флаг "по верху"
			}

			motions.push_back(md);
		}
					
		ZeroMemory(&highlight, sizeof(highlight));						// Скидуємо підсвічування

		checkRow = _rnull;												// Скидаємо координати шаху
		checkColunm = _cnull;											// якщо звичайно він був на попередньому кроці
						
		if(movingCam){
			movingCam = false;
		}
		else{
			Render->StartAnimation();
		}

		break;

	// Шах, шах і мат
	case SUCCESS_MOVE_CHECK:
	case SUCCESS_MOVE_CHECKMATE:
					
		

		for(unsigned int i = 0; i < movestruct.size(); i++){
					
			MoveData md;
			md.startRow = movestruct[i].startRow;
			md.startColumn = movestruct[i].startColumn;

			md.endRow = movestruct[i].endRow;
			md.endColumn = movestruct[i].endColumn;

			md.startTime = GetTickCount();
			if(md.endRow == _rnull || md.endColumn == _cnull) md.movingTime = DELETING_TIME;
			else{
				FLOAT intervalRow = ((FLOAT)movestruct[i].endRow - movestruct[i].startRow) * CS_FIGURE_SIZE;
				FLOAT intervalColumn = ((FLOAT)movestruct[i].endColumn - movestruct[i].startColumn) * CS_FIGURE_SIZE;
				FLOAT distanceMoving = sqrt((pow((intervalRow), 2) + pow(intervalColumn, 2)));

				md.movingTime = int(MOVING_TIME * distanceMoving);
			}

			// Перевіряємо як здійснювати переміщення фігури, "по низу" чи "по верху"
			md.typeMove = MOVING_BOTTOM;

			if(!((movestruct[i].startRow - movestruct[i].endRow) == 0 ||
				(movestruct[i].startColumn - movestruct[i].endColumn) == 0 ||
				abs(int(movestruct[i].startRow - movestruct[i].endRow)) == abs(int(movestruct[i].startColumn - movestruct[i].endColumn))))
			{
				// Вираховуємо стартові позиції перевірки
				int rows = abs((int)movestruct[i].endRow - (int)movestruct[i].startRow);
				int columns = abs((int)movestruct[i].endColumn - (int)movestruct[i].startColumn);

				unsigned findRowStart = min(movestruct[i].startRow, movestruct[i].endRow);
				unsigned findColumnStart = min(movestruct[i].startColumn, movestruct[i].endColumn);
								
				if(rows > columns){
					if(figures[findRowStart + 1][findColumnStart] != NULL ||
						figures[findRowStart + 1][findColumnStart + 1] != NULL){
						md.typeMove = MOVING_TOP;
					}
				}
				else{
					if(figures[findRowStart + 1][findColumnStart + 1] != NULL ||
						figures[findRowStart][findColumnStart + 1] != NULL){
						md.typeMove = MOVING_TOP;
					}
				}
			};

			if((highlight[selRow][selColumn] == SHORT_CASTLING || 
				highlight[selRow][selColumn] == LONG_CASTLING) &&
				i > 0)
			{
				md.typeMove = MOVING_TOP;
			}

			motions.push_back(md);
		}
					
		ZeroMemory(&highlight, sizeof(highlight));
						
		if(movingCam){
			movingCam = false;
		}
		else{
			Render->StartAnimation();
		}

		break;

	case ERROR_MOVE_WRONG_POSITION:
					
		// Перевіряємо чи не клацнули по тій самій фігурі ще раз
		if(highlight[selRow][selColumn] != MOVE_CURPOS){
						
			// Перевіряємо чи перший раз клацнули("вибір фігури") і чи є координати клацання на дошці
			if(selColumn != _cnull && selRow != _rnull){
			
				// Запитуємо список можливих ходів, і підсвітки для вказаної фігури
				resultMoving = game->getMoves(selRow, selColumn, highlight, moves);
			
				// Розбираємо код поверненого результату
				switch(resultMoving){

				// Успіх
				case SUCCESS_GET_MOVES:
					secondClick = true;					// Переходимо до етапу "вибору куди ходити"
					break;

				// Неправильна позиція
				case ERROR_GET_MOVES_WRONG_POSITION:
								
				// Фігура не того кольору
				case ERROR_GET_MOVES_WRONG_COLOR:
								
					hint->Show(TEXT("Ви неможете перемістити сюди фігуру"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
								
					// Очищюємо підсвічування
					ZeroMemory(&highlight, sizeof(highlight));
					break;

				// Фігура не має ходів
				case ERROR_GET_MOVES_CANT_MOVE:
								
					hint->Show(TEXT("Дана фігура не може бути переміщена"), TEXT("Помилка"), LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)));
								
					// Очищюємо підсвічування
					ZeroMemory(&highlight, sizeof(highlight));
					break;
				};
			}

		}
		else{
			// Очищюємо підсвічування
			ZeroMemory(&highlight, sizeof(highlight));
		}
		break;
	};
};

void NetChessGame::SetParameter(int parametrID, int parametrValue){

	switch(parametrID){
	case GAME_AUTOROTATE_CAM:
		autoRotationCam = (parametrValue == GAME_YES);
		break;

	case GAME_DISCONNECTION:
		if(parametrValue = GAME_YES && !gameOver){
			RECT windowClient;
			GetClientRect(hWnd, &windowClient);

			text.Load(direct3DDevice, windowClient.bottom / TEXT2D_SCALING, NET_DISCONECTION, windowClient, TEXT_HV_CENTER, D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF));
				
			gameOver = true;
			selRow = _rnull;
			selColumn = _cnull;
			Render->StartAnimation();
		}
		break;

	default:
		ChessGame::SetParameter(parametrID, parametrValue);
		break;
	}
};

NetChessGame::~NetChessGame(){
	delete game;
};