/******************************************************************************************************
*
*	��� "����"				������� ������				���������: "����� ���"					2011
*	������, ���� ������ ��'�������, ���� � ��������� ��� ⳺� ���
*
*******************************************************************************************************/

#ifndef _GAME_
#define _GAME_

#include <vector>

#include "resource.h"
#include "engine\\engine.h"
#include "engine\\3d_objects.h"

#include "chess_validator\\localgame.h"
#include "chess_validator\\networkgame.h"
#include "chess_validator\\enum.h"
#include "CLWindow.cpp"
#include "hint.cpp"

using namespace chess;

extern Engine *Render;
extern Hint *hint;
extern TCPClient *client;
extern TCPServer *server;


#define GAME_WRONG_PARAM	-1
#define GAME_CHANGE_THEME	1
#define GAME_END			2
#define GAME_AUTOROTATE_CAM	3
#define GAME_DISCONNECTION	4

#define GAME_NO				0
#define GAME_YES			1

#define THEME_WHITE			0
#define THEME_COLORED		1

#define LOCAL_WHITE_WIN		TEXT("��� � ���\n��� �������")
#define LOCAL_BLACK_WIN		TEXT("��� � ���\n���� �������")
#define LOCAL_DRAW			TEXT("ͳ���")

#define NET_YOU_WIN			TEXT("��� � ���\n�� �������")
#define NET_YOU_LOSE		TEXT("��� � ���\n�� ��������")
#define NET_DRAW			TEXT("ͳ���")
#define NET_DISCONECTION	TEXT("�'������� ��������")

#define HIGHLIGHT_TEXTURES_COUNT 9

#define TEXTURE_NULL		0
#define TEXTURE_CURPOS		1
#define TEXTURE_MOVE		2
#define TEXTURE_ATTACK		3
#define TEXTURE_PROMOTION	4
#define TEXTURE_CASTLING	5
#define TEXTURE_CHECK		6
#define TEXTURE_CURSOR		7
#define TEXTURE_CURSOR2		8

#define ID_BUTTON_Q			8001
#define ID_BUTTON_R			8002
#define ID_BUTTON_B			8003
#define ID_BUTTON_N			8004

#define CS_FIGURE_SIZE	0.7f													// ����� ������� �� ������ �����
#define CS_FIGURE_HALF	CS_FIGURE_SIZE / 2.0f									// �������� �������

#define BOARD_BORDER_HSIZE CS_FIGURE_SIZE / 2.0f								// �������������� ����� ����� ������ �����
#define BOARD_BORDER_VSIZE CS_FIGURE_SIZE / 2.0f								// ������������ ����� ����� ������ �����

#define TOTAL_BOARD_SIZE 8.0f * CS_FIGURE_SIZE + 2.0f * BOARD_BORDER_HSIZE		// ����� ����� ����� � ������
#define HALF_BOARD_SIZE 4.0f * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE				// �������� ������ ����� ����� � ������
#define TEXTURE_COORD_BORDER (BOARD_BORDER_HSIZE) / (TOTAL_BOARD_SIZE)			// ³�������� ������ ����� ����� �� ������ �񳺿 �����
																				// ( ��������� ��� ���������� ���������� ��������� ��� ����� )

#define TEXT_SHIFT 0.15f														// ������� ������� � ���� ������� ������� ������
#define TEXT_BORDER_SHIFT 0.07f													// ������� ������� � ���� �� ���� �����
#define TEXT_SCALING 0.4f														// ������������ ������� � ����
#define TEXT_HEIGHT 0.09f														// ������ ( Z-����� ) ������� � ����

#define TEXT2D_SCALING 10														// ������������� 2D ������ �������� ������� �����

#define SPEED_CAM_MOVE 0.002f													// ���������� �������� ������ ��� 
#define MOVING_TIME 400															// ��� �� ���� ������ ����������� �� ���� �������(��)
#define DELETING_TIME (MOVING_TIME - 100)

#define MOVING_BOTTOM 0
#define MOVING_TOP 1

#define DELAY_FIRST_ROTATION 1200
#define TIME_PER_ANGLE D3DXToRadian(90.0f)
#define MOVING_CAMERA 100
#define MOVING_CAM_FUNCTION(X) (exp(X * 12.0f) / (exp(1.0f) * 70.0f + exp(X * 12.0f)))

#define MAX_CAM_ANGLE_Y D3DXToRadian(179.0f)
#define MIN_CAM_ANGLE_Y D3DXToRadian(90.0f)

#define MIN_CAM_DISTANCE -7.0f
#define MAX_CAM_DISTANCE MIN_CAM_DISTANCE * 2.0f

#define DEFAULT_CAM_DIST -8.0f
#define DEFAULT_CAM_ANGLE_X D3DXToRadian(90.0f)
#define DEFAULT_CAM_ANGLE_Y MIN_CAM_ANGLE_Y + D3DXToRadian(40.0f)

#define WHITE_CAM_DIST -8.0f
#define WHITE_CAM_ANGLE_X 0.0f
#define WHITE_CAM_ANGLE_Y MIN_CAM_ANGLE_Y + D3DXToRadian(40.0f)

#define BLACK_CAM_DIST -8.0f
#define BLACK_CAM_ANGLE_X D3DXToRadian(180.0f)
#define BLACK_CAM_ANGLE_Y MIN_CAM_ANGLE_Y + D3DXToRadian(40.0f)

struct MoveData:public MoveStruct{
	int startTime;
	int movingTime;
	int typeMove;
};

struct TextSettings{														// ���������, ��� ����� ������ �� ���� ��������� �� �����
	FLOAT rotationX;														// ������� ������� �� � (� ��������)
	FLOAT rotationZ;														// ������� ������� �� Z (� ��������)
	FLOAT shiftX;															// ������� �� �� � (�� ������ �����)
	FLOAT shiftZ;															// ������� �� �� Z (�� ������ �����)
	TCHAR character;														// ������
};

struct Coordinates{
	FLOAT x, y, z;
};

// ����� � ��������� � ��������� ��� �����������
const TextSettings TextOnBoard[] = {	{90.0f, 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE + TEXT_SHIFT), -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, TEXT('A')},
										{90.0f, 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE + TEXT_SHIFT), -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, TEXT('B')},
										{90.0f, 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE + TEXT_SHIFT), -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, TEXT('C')},
										{90.0f, 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE + TEXT_SHIFT), -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, TEXT('D')},
										{90.0f, 0.0f,  (CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE - TEXT_SHIFT), -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, TEXT('E')},
										{90.0f, 0.0f,  (CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE - TEXT_SHIFT), -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, TEXT('F')},
										{90.0f, 0.0f,  (CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE - TEXT_SHIFT), -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, TEXT('G')},
										{90.0f, 0.0f,  (CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE - TEXT_SHIFT), -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, TEXT('H')},

										{90.0f, 0.0f, -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE + TEXT_SHIFT), TEXT('1')},
										{90.0f, 0.0f, -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE + TEXT_SHIFT), TEXT('2')},
										{90.0f, 0.0f, -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE + TEXT_SHIFT), TEXT('3')},
										{90.0f, 0.0f, -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE + TEXT_SHIFT), TEXT('4')},
										{90.0f, 0.0f, -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT,  (CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE - TEXT_SHIFT), TEXT('5')},
										{90.0f, 0.0f, -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT,  (CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE - TEXT_SHIFT), TEXT('6')},
										{90.0f, 0.0f, -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT,  (CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE - TEXT_SHIFT), TEXT('7')},
										{90.0f, 0.0f, -(HALF_BOARD_SIZE) + TEXT_BORDER_SHIFT,  (CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE - TEXT_SHIFT), TEXT('8')},

										{90.0f, 180.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE - TEXT_SHIFT), (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, TEXT('A')},
										{90.0f, 180.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE - TEXT_SHIFT), (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, TEXT('B')},
										{90.0f, 180.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE - TEXT_SHIFT), (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, TEXT('C')},
										{90.0f, 180.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE - TEXT_SHIFT), (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, TEXT('D')},
										{90.0f, 180.0f,  (CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE + TEXT_SHIFT), (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, TEXT('E')},
										{90.0f, 180.0f,  (CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE + TEXT_SHIFT), (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, TEXT('F')},
										{90.0f, 180.0f,  (CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE + TEXT_SHIFT), (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, TEXT('G')},
										{90.0f, 180.0f,  (CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE + TEXT_SHIFT), (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, TEXT('H')},

										{90.0f, 180.0f, (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE - TEXT_SHIFT), TEXT('1')},
										{90.0f, 180.0f, (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE - TEXT_SHIFT), TEXT('2')},
										{90.0f, 180.0f, (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE - TEXT_SHIFT), TEXT('3')},
										{90.0f, 180.0f, (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE - TEXT_SHIFT), TEXT('4')},
										{90.0f, 180.0f, (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT,  (CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE + TEXT_SHIFT), TEXT('5')},
										{90.0f, 180.0f, (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT,  (CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE + TEXT_SHIFT), TEXT('6')},
										{90.0f, 180.0f, (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT,  (CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE + TEXT_SHIFT), TEXT('7')},
										{90.0f, 180.0f, (HALF_BOARD_SIZE) - TEXT_BORDER_SHIFT,  (CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE + TEXT_SHIFT), TEXT('8')}};

// ******************************* ������� ������� ����� ��� ����� *********************************

D3DMATERIAL9 CS_Theme1_Border = {{0.00f, 0.33f, 0.56f, 1.0f},		// ������� �����, �� �������� �� ��������
								{0.0f , 0.0f, 0.0f, 0.0f},			// ������� ��������� �����
								{0.11f , 0.11f, 0.11f, 0.0f},		// ������� �������� (����������) �����
								{0.33f , 0.33f, 0.33f, 0.0f},		// ������� ����������� ����� ���������
								100.0f};							// ��������� �����������

D3DMATERIAL9 CS_Theme2_Border = {{0.66f, 0.66f, 0.66f, 0.5f},
								{0.0f , 0.0f, 0.0f, 0.0f},	
								{0.11f , 0.11f, 0.11f, 0.0f},
								{0.33f , 0.33f, 0.33f, 0.0f},
								100.0f};	

D3DMATERIAL9 CS_Theme1_Text = {{0.00f, 0.33f, 0.56f, 1.0f},	
								{0.0f , 0.0f, 0.0f, 0.0f},	
								{0.0f , 0.0f, 0.0f, 0.0f},	
								{0.0f , 0.0f, 0.0f, 0.0f},
								0.0f};

// *********************************** �������� ������� ������� **************************************
// ������� ���� ������� ���� �1
D3DMATERIAL9 CS_Theme1_White = { {1.0f , 1.0f, 1.0f, 1.0f},	
								{1.0f , 1.0f, 1.0f, 1.0f},	
								{0.0f , 0.0f, 0.0f, 0.0f},	
								{0.2f , 0.2f, 0.2f, 0.0f},	
								0.0f};	

// ������� ������ ������� ���� �1
D3DMATERIAL9 CS_Theme1_Black = { {0.1f , 0.1f, 0.1f, 1.0f},	
								{0.1f , 0.1f, 0.1f, 0.0f},	
								{0.2f , 0.2f, 0.2f, 0.0f},	
								{0.0f , 0.0f, 0.0f, 0.0f},	
								10.0f};	

// ������� ���� ������� ���� �2
D3DMATERIAL9 CS_Theme2_White = { {1.0f , 1.0f, 1.0f, 1.0f},	
								{1.0f , 1.0f, 1.0f, 1.0f},	
								{1.0f , 1.0f, 1.0f, 1.0f},	
								{0.0f , 0.0f, 0.0f, 0.0f},	
								50.0f};						

// ������� ������ ������� ���� �2
D3DMATERIAL9 CS_Theme2_Black = { {0.1f , 0.1f, 0.1f, 1.0f},
								{0.0f , 0.0f, 0.0f, 1.0f},	
								{1.0f , 1.0f, 1.0f, 1.0f},	
								{0.0f , 0.0f, 0.0f, 0.0f},	
								50.0f};	

// ������� ������������� �������
D3DMATERIAL9 CS_Textured = { {1.0f , 1.0f, 1.0f, 1.0f},		
							{1.0f , 1.0f, 1.0f, 1.0f},		
							{1.0f , 1.0f, 1.0f, 0.0f},		
							{0.0f , 0.0f, 0.0f, 0.0f},		
							100.0f};
						
// ************************************** ������� ����� ��� ����� ***********************************************
D3DMATERIAL9 CS_Board = { {1.0f , 1.0f, 1.0f, 1.0f},
						{1.0f , 1.0f, 1.0f, 0.0f},	
						{0.0f , 0.0f, 0.0f, 0.0f},	
						{1.0f , 1.0f, 1.0f, 1.0f},
						0.0f};	


// ******************************************** ������� ����� �� ����� ********************************************
//								� - ����������						Y - ���������� 		Z - ����������
const Coordinates Pos[8][8] = {	{{-(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE)},
								 {-(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE)},
								 {-(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE)},
								 {-CS_FIGURE_HALF 						, 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF 						, 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE)}},

								{{-(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE)},
								 {-(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE)},
								 {-(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE)},
								 {-CS_FIGURE_HALF						, 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF						, 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE)}},

								{{-(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE)},
								 {-(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE)},
								 {-(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE)},
								 {-CS_FIGURE_HALF						, 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF						, 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE)}},

								{{-(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE)},
								 {-(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE)},
								 {-(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE), 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE)},
								 {-CS_FIGURE_HALF						, 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF						, 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE)},
								 { CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE	, 0.0f, -(CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE)}},

								{{-(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE},
								 {-(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE},
								 {-(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE},
								 {-CS_FIGURE_HALF						, 0.0f, CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF						, 0.0f, CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 0 * CS_FIGURE_SIZE}},

								{{-(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE},
								 {-(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE},
								 {-(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE},
								 {-CS_FIGURE_HALF						, 0.0f, CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF						, 0.0f, CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE}},
								
								{{-(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE},
								 {-(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE},
								 {-(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE},
								 {-CS_FIGURE_HALF						, 0.0f, CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF						, 0.0f, CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE}},

								{{-(CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE},
								 {-(CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE},
								 {-(CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE), 0.0f, CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE},
								 {-CS_FIGURE_HALF						, 0.0f, CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF						, 0.0f, CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 1 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 2 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE},
								 { CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE	, 0.0f, CS_FIGURE_HALF + 3 * CS_FIGURE_SIZE}}};

const Vertex3DNT boardVertex[] = {{ -4 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE, 0.0f, 1.0f, 0.0f, 0.000f, 0.000f},
									{  4 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE, 0.0f, 1.0f, 0.0f, 1.000f, 1.000f},
									{ -4 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE, 0.0f, 1.0f, 0.0f, 1.000f, 0.000f},

									{ -4 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE, 0.0f, 1.0f, 0.0f, 0.000f, 0.000f},
									{  4 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE, 0.0f, 1.0f, 0.0f, 0.000f, 1.000f},
									{  4 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE, 0.0f, 1.0f, 0.0f, 1.000f, 1.000f}};
// ******************************************** ���������� ������ ����� ********************************************
								//   X					Y				Z
const Coordinates Vertexs[] = {	{ -4 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{ -4 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{ -4 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{ -4 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{ -4 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{ -4 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{ -4 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{ -4 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{ -4 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE},

								{ -3 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{ -3 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{ -3 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{ -3 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{ -3 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{ -3 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{ -3 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{ -3 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{ -3 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE},

								{ -2 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{ -2 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{ -2 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{ -2 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{ -2 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{ -2 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{ -2 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{ -2 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{ -2 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE},

								{ -1 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{ -1 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{ -1 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{ -1 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{ -1 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{ -1 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{ -1 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{ -1 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{ -1 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE},

								{  0 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{  0 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{  0 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{  0 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{  0 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{  0 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{  0 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{  0 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{  0 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE},

								{  1 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{  1 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{  1 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{  1 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{  1 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{  1 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{  1 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{  1 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{  1 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE},

								{  2 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{  2 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{  2 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{  2 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{  2 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{  2 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{  2 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{  2 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{  2 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE},

								{  3 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{  3 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{  3 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{  3 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{  3 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{  3 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{  3 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{  3 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{  3 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE},

								{  4 * CS_FIGURE_SIZE,	0.0f,	-4 * CS_FIGURE_SIZE},
								{  4 * CS_FIGURE_SIZE,	0.0f,	-3 * CS_FIGURE_SIZE},
								{  4 * CS_FIGURE_SIZE,	0.0f,	-2 * CS_FIGURE_SIZE},
								{  4 * CS_FIGURE_SIZE,	0.0f,	-1 * CS_FIGURE_SIZE},
								{  4 * CS_FIGURE_SIZE,	0.0f,	 0 * CS_FIGURE_SIZE},
								{  4 * CS_FIGURE_SIZE,	0.0f,	 1 * CS_FIGURE_SIZE},
								{  4 * CS_FIGURE_SIZE,	0.0f,	 2 * CS_FIGURE_SIZE},
								{  4 * CS_FIGURE_SIZE,	0.0f,	 3 * CS_FIGURE_SIZE},
								{  4 * CS_FIGURE_SIZE,	0.0f,	 4 * CS_FIGURE_SIZE}};

#define TEX_X	0.2f
#define TEX_Y	((TOTAL_BOARD_SIZE) / (BOARD_BORDER_VSIZE)) * (TEX_X - STR_X)
#define STR_X	0.0f
#define STR_Y	0.0f
#define SIZE_Y	0.05f

// ����� � ��������� ����� �����
Vertex3DNT borderVertex[] = {
						//   X					Y				Z								NX    NY    NZ     Tu    						Tv
	// ������������ ����
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE,	0.0f,  4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 0.000f,						0.000f},
	{-4 * CS_FIGURE_SIZE,						0.0f,  4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, TEXTURE_COORD_BORDER,			TEXTURE_COORD_BORDER},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE,	0.0f, -4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 0.000f,						1.000f},

	{-4 * CS_FIGURE_SIZE,						0.0f,  4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, TEXTURE_COORD_BORDER,			TEXTURE_COORD_BORDER},
	{-4 * CS_FIGURE_SIZE,						0.0f, -4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, TEXTURE_COORD_BORDER,			1.0f - TEXTURE_COORD_BORDER},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE,	0.0f, -4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 0.000f,						1.000f},

	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE,	0.0f,  4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 0.000f,						0.000f},
	{ 4 * CS_FIGURE_SIZE,						0.0f,  4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, 1.0f - TEXTURE_COORD_BORDER,	TEXTURE_COORD_BORDER},
	{-4 * CS_FIGURE_SIZE,						0.0f,  4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, TEXTURE_COORD_BORDER,			TEXTURE_COORD_BORDER},
	
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE,	0.0f,  4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 0.000f,						0.000f},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE,	0.0f,  4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 1.000f,						0.000f},
	{ 4 * CS_FIGURE_SIZE,						0.0f,  4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, 1.0f - TEXTURE_COORD_BORDER,	TEXTURE_COORD_BORDER},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE,	0.0f,  4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 1.000f,						0.000f},
	{ 4 * CS_FIGURE_SIZE,						0.0f, -4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, 1.0f - TEXTURE_COORD_BORDER,	1.0f - TEXTURE_COORD_BORDER},
	{ 4 * CS_FIGURE_SIZE,						0.0f,  4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, 1.0f - TEXTURE_COORD_BORDER,	TEXTURE_COORD_BORDER},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE,	0.0f,  4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 1.000f,						0.000f},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE,	0.0f, -4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 1.000f,						1.000f},
	{ 4 * CS_FIGURE_SIZE,						0.0f, -4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, 1.0f - TEXTURE_COORD_BORDER,	1.0f - TEXTURE_COORD_BORDER},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE,	0.0f, -4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 1.000f,						1.000f},
	{-4 * CS_FIGURE_SIZE,						0.0f, -4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, TEXTURE_COORD_BORDER,			1.0f - TEXTURE_COORD_BORDER},
	{ 4 * CS_FIGURE_SIZE,						0.0f, -4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, 1.0f - TEXTURE_COORD_BORDER,	1.0f - TEXTURE_COORD_BORDER},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE,	0.0f, -4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 1.000f,						1.000f},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE,	0.0f, -4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 1.0f, 0.0f, 0.000f,						1.000f},
	{-4 * CS_FIGURE_SIZE,						0.0f, -4 * CS_FIGURE_SIZE,						0.0f, 1.0f, 0.0f, TEXTURE_COORD_BORDER,			1.0f - TEXTURE_COORD_BORDER},

	// ���������� ����
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, STR_X, STR_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, TEX_X, TEX_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, TEX_X, STR_Y},

	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, STR_X, STR_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, STR_X, TEX_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, TEX_X, TEX_Y},

	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, STR_X, STR_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, TEX_X, TEX_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, TEX_X, STR_Y},

	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, STR_X, STR_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, STR_X, TEX_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, TEX_X, TEX_Y},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, STR_X, STR_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, TEX_X, TEX_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, TEX_X, STR_Y},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, STR_X, STR_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, STR_X, TEX_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, TEX_X, TEX_Y},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, STR_X, STR_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, TEX_X, TEX_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, TEX_X, STR_Y},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, STR_X, STR_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, STR_X, TEX_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, TEX_X, TEX_Y},

	// ���������� ����
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, STR_X, STR_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, TEX_X, TEX_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, TEX_X, STR_Y},

	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, STR_X, STR_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, STR_X, TEX_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -1.0f, 0.0f, 0.0f, TEX_X, TEX_Y},

	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, STR_X, STR_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, TEX_X, TEX_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, TEX_X, STR_Y},

	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, STR_X, STR_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, STR_X, TEX_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 0.0f, 0.0f, -1.0f, TEX_X, TEX_Y},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, STR_X, STR_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, TEX_X, TEX_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, TEX_X, STR_Y},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,				-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, STR_X, STR_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, STR_X, TEX_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 1.0f, 0.0f, 0.0f, TEX_X, TEX_Y},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, STR_X, STR_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, TEX_X, TEX_Y},
	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, TEX_X, STR_Y},

	{ 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, -SIZE_Y,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, STR_X, STR_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -SIZE_Y,				 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, STR_X, TEX_Y},
	{-4 * CS_FIGURE_SIZE - BOARD_BORDER_HSIZE, -BOARD_BORDER_VSIZE,	 4 * CS_FIGURE_SIZE + BOARD_BORDER_HSIZE, 0.0f, 0.0f, 1.0f, TEX_X, TEX_Y}
};

// ������� ���� ��� ��������� ����
class Background: public Primitive{
protected:
	HWND hWnd;

public:
	Background(LPDIRECT3DDEVICE9 device, HWND handle):Primitive(device){
		hWnd = handle;
	};

	virtual void Update(int width, int height){};

	virtual void Draw() = 0;
};

// ���������� ����� ���
class ColoredBackground: public Background{
private:
	VertexBuffer2D vertex;

public:
	ColoredBackground(LPDIRECT3DDEVICE9 device, HWND handle);

	void Update(int width, int height);

	void Draw();
};

class WhiteBackground: public Background{
private:
	VertexBuffer2D vertex;

public:
	WhiteBackground(LPDIRECT3DDEVICE9 device, HWND handle);

	void Update(int width, int height);

	void Draw();
};

class Foreground: public Background{
private:
	VertexBuffer2D vertex;

public:
	Foreground(LPDIRECT3DDEVICE9 device, HWND handle);

	void Update(int width, int height);

	void Draw();
};


// Գ���� - �������� �����
class ChessBoard: public Primitive{
protected:
	VertexBuffer3DNT board;				// ��������� ����� �����
	VertexBuffer3DNT border;			// �������� ����� ����� �����
	Texture boardTexture;				// �������� ����� 
	
	Texture borderTexture[3];
	D3DMATERIAL9 *borderMaterial[3];

	Text3D text[32];					// ������� �� �����(A, B, C, ...; 0, 1, 2, ...)
	D3DXMATRIX textPositions[32];		// ������� �������
	D3DMATERIAL9 *textMaterial;
	Texture textTexture;

	D3DXMATRIX matrixWorld;				// ������� ��������� �����
	
public:
	ChessBoard(LPDIRECT3DDEVICE9 device);

	void SetTheme(int themeID);

	void Draw();
};


class ChessFigure: public Primitive{
private:
	Mesh model;
	Texture texture;
	D3DMATERIAL9 *material;

protected:
	D3DXMATRIX matrixWorld;

public:
	ChessFigure(LPDIRECT3DDEVICE9 device, int modelResID, D3DMATERIAL9 *newMaterial, int textureResID = 0);

	void ChangeModel(int resId);

	void ChangeTexture(int resID);

	// ���� ������� ���� ��'����
	virtual void SetWorldMatrix(D3DXMATRIX *newMatWorld);

	void SetMaterial(D3DMATERIAL9 *newMaterial);

	void SetTransparency(FLOAT value);

	virtual void Draw();

	virtual ~ChessFigure();

	virtual Color Who() = 0;
};

class WhiteFigure: public ChessFigure{
public:
	WhiteFigure(LPDIRECT3DDEVICE9 device, int modelResID, D3DMATERIAL9 *newMaterial, int textureResID = 0):ChessFigure(device, modelResID, newMaterial, textureResID){};
	
	virtual Color Who();
};

class BlackFigure: public ChessFigure{
private:
	D3DXMATRIX RotatedMatrx;
public:
	BlackFigure(LPDIRECT3DDEVICE9 device, int Type, D3DMATERIAL9 *newMaterial, int textureResID = 0);

	// ���� ������� ���� ��'����
	virtual void SetWorldMatrix(D3DXMATRIX *newMatWorld);

	virtual Color Who();

	virtual ~BlackFigure(){};
};


class ChessGame: public Layer{
protected:
	ChessFigure *figures[8][8];	// Գ���� �������� ���
	
	bool rButtonDown;		// ���� ��������� ����� ������ �����
	POINT OldPos;			// ������� ������� ��� ��������� ����� ������ �����

	D3DLIGHT9 light;		// ��� ���������
	Camera cam;				// ����, ���� �������� �������� � �������

	VertexBuffer3DNT highlightCells[8][8];
	D3DXMATRIX matrixHighlight;
	Texture textureHighlight[HIGHLIGHT_TEXTURES_COUNT];
	int checkColunm, checkRow;
	int transperentRow, transperentColumn;

	ChessBoard *board;		// Գ���� �������� �����
	
	int selColumn, selRow;
	bool secondClick;

	std::vector<MoveData> motions;

	unsigned int moves[8][8];
	unsigned int highlight[8][8];

	bool movingCam;
	int startTimeMovingCam;
	Camera startCamPos;
	int resultMoving;

	bool gameOver;

	Text2D text;
	
	Background *foreground;
	Background *background;

	bool SelectedCell(int column, int row, D3DXVECTOR3 *rayStart, D3DXVECTOR3 *rayDirection);

	bool OnBoard(D3DXVECTOR3 *rayStart, D3DXVECTOR3 *rayDirection);

	void PlaceFigures(unsigned int figures[8][8], unsigned int colors[8][8]);

public:
	ChessGame(LPDIRECT3DDEVICE9 device, HWND handle);

	virtual void Draw();

	// ϳ��������� ������� ��������� ��������� �����
	void Wheel(int delta);

	// ϳ��������� ������� ���������� ����� ������ ����
	void RBtnDown(int xPos, int yPos);

	// ϳ��������� ������� ��������� ����� ������ ����
	void RBtnUp(int xPos, int yPos);

	// ϳ��������� ������� ��������� �������� ����� ������ �����
	void RBtnDblClk(int xPos, int yPos);

	void MouseMove(int xPos, int yPos);

	void WindowActive(int state);

	void LBtnDblClk(int xPos, int yPos);

	// ϳ��������� ������� ���������� �����
	virtual void KeyDown(int key);

	virtual void Resize(int width, int height);

	virtual void BeforeResetDevice();

	virtual void AfterResetDevice();

	virtual void SetParameter(int parametrID, int parametrValue);

	virtual int GetParameter(int parametrID);

	virtual void LBtnDown(int xPos, int yPos) = 0;

	virtual void Timer(int time) = 0;

	~ChessGame();

};

class LocalChessGame: public ChessGame{
private:
	LocalGame *game;

public:

	LocalChessGame(LPDIRECT3DDEVICE9 device, HWND handle);

	virtual void LBtnDown(int xPos, int yPos);

	virtual void Timer(int time);

	~LocalChessGame();
};

class NetChessGame: public ChessGame{
private:
	NetworkGame *game;
	bool autoRotationCam;
	unsigned promotion;
	int promotionColumn, promotionRow;
public:

	NetChessGame(LPDIRECT3DDEVICE9 device, HWND handle, Color player);

	virtual void LBtnDown(int xPos, int yPos);

	virtual void Timer(int time);

	virtual void SendData(char *data, int len);

	virtual void SetParameter(int parametrID, int parametrValue);

	~NetChessGame();
};
#endif