#ifndef _ENUM_H
#define _ENUM_H

#define SUCCESS_GET_MOVES 101						// Список ходов успешно получен
#define ERROR_GET_MOVES_CANT_MOVE 102				// Этой фигурой нельзя ходить (откроем своего короля или фигура заблокирована)
#define ERROR_GET_MOVES_WRONG_COLOR 103				// Пытаемся походить вражеской фигурой
#define ERROR_GET_MOVES_WRONG_POSITION 104			// Выбрали пустую клетку или переданы координаты клетки за доской

#define SUCCESS_MOVE 201							// Удачный ход
#define SUCCESS_MOVE_DRAW 202						// Пат (ничья)
#define SUCCESS_MOVE_CHECK 203						// После выполнения хода будет шах (последний элемент вектора указывает на короля)
#define SUCCESS_MOVE_CHECKMATE 204					// Шах и мат
#define SUCCESS_MOVE_PROMOTION 205					// Пешка дошла края доски, требуется замена фигуры (последний|предпоследний элемент вектора указывает на позицию замены)

#define ERROR_MOVE_WRONG_POSITION 301				// Попытка ходить против правил
#define ERROR_PROMOTION_WRONG_TYPE 302				// Неверная фигура для замены пешки

#define ERROR_WRONG_CALL 401						// Вызов неверной функции
#define ERROR_WRONG_DATA 402						// Переданы неверные данные

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
	
	enum MoveType {									// Тип хода и подсветки
		MOVE_NULL, MOVE_CURPOS,						// Нету подсветки и текущая позиция фигуры
		MOVE, ATTACK,								// Ход и бой
		MOVE_PROMOTION, ATTACK_PROMOTION,			// Ход и бой, после которых пешка дойдет края доски
		SHORT_CASTLING, LONG_CASTLING,				// Рокировки
		MOVE_INPASSING, ATTACK_INPASSING			// Ход пешки на две клетки, взятие на проходе
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