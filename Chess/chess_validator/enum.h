#ifndef _ENUM_H
#define _ENUM_H

#define SUCCESS_GET_MOVES 101						// ������ ����� ������� �������
#define ERROR_GET_MOVES_CANT_MOVE 102				// ���� ������� ������ ������ (������� ������ ������ ��� ������ �������������)
#define ERROR_GET_MOVES_WRONG_COLOR 103				// �������� �������� ��������� �������
#define ERROR_GET_MOVES_WRONG_POSITION 104			// ������� ������ ������ ��� �������� ���������� ������ �� ������

#define SUCCESS_MOVE 201							// ������� ���
#define SUCCESS_MOVE_DRAW 202						// ��� (�����)
#define SUCCESS_MOVE_CHECK 203						// ����� ���������� ���� ����� ��� (��������� ������� ������� ��������� �� ������)
#define SUCCESS_MOVE_CHECKMATE 204					// ��� � ���
#define SUCCESS_MOVE_PROMOTION 205					// ����� ����� ���� �����, ��������� ������ ������ (���������|������������� ������� ������� ��������� �� ������� ������)

#define ERROR_MOVE_WRONG_POSITION 301				// ������� ������ ������ ������
#define ERROR_PROMOTION_WRONG_TYPE 302				// �������� ������ ��� ������ �����

#define ERROR_WRONG_CALL 401						// ����� �������� �������
#define ERROR_WRONG_DATA 402						// �������� �������� ������

namespace chess {
	enum Color {
		COLOR_NULL,
		WHITE, BLACK
	};
	
	enum Row {
		_1, _2, _3, _4, _5, _6, _7, _8, _rnull
	};
	
	enum Column {
		_a, _b, _c, _d, _e, _f, _g, _h, _cnull
	};
	
	enum MoveType {									// ��� ���� � ���������
		MOVE_NULL, MOVE_CURPOS,						// ���� ��������� � ������� ������� ������
		MOVE, ATTACK,								// ��� � ���
		MOVE_PROMOTION, ATTACK_PROMOTION,			// ��� � ���, ����� ������� ����� ������ ���� �����
		SHORT_CASTLING, LONG_CASTLING,				// ���������
		MOVE_INPASSING, ATTACK_INPASSING			// ��� ����� �� ��� ������, ������ �� �������
	};
	
	enum PromType {
		PROM_NULL,
		PROM_QUEEN, PROM_ROCK, PROM_BISHOP, PROM_KNIGHT
	};
	
	enum FigureType {
		FIGURE_NULL,
		PAWN, KNIGHT, ROCK, BISHOP, QUEEN, KING
	};
	
	struct MoveStruct {
		unsigned int startRow;
		unsigned int startColumn;
		unsigned int endRow;
		unsigned int endColumn;
	};
	
	struct SendStruct {
		char startRow;
		char startColumn;
		char endRow;
		char endColumn;
		char moveType;
		char promType;
	};
};

#endif  /* _ENUM_H */