#include "board.h"

namespace chess {
	Board::Board() {
		for (unsigned int i = _1; i <= _8; i++) {
			for (unsigned int j = _a; j <= _h; j++) {
				matrix[i][j] = NULL;
			}
		}
		
		for (unsigned int i = _a; i <= _h; i++) {
			matrix[_2][i] = new Pawn(WHITE, this);
			matrix[_7][i] = new Pawn(BLACK, this);
		}
		
		matrix[_1][_b] = new Knight(WHITE, this);
		matrix[_1][_g] = new Knight(WHITE, this);
		matrix[_8][_b] = new Knight(BLACK, this);
		matrix[_8][_g] = new Knight(BLACK, this);
		
		matrix[_1][_a] = new Rock(WHITE, this);
		matrix[_1][_h] = new Rock(WHITE, this);
		matrix[_8][_a] = new Rock(BLACK, this);
		matrix[_8][_h] = new Rock(BLACK, this);
		
		matrix[_1][_c] = new Bishop(WHITE, this);
		matrix[_1][_f] = new Bishop(WHITE, this);
		matrix[_8][_c] = new Bishop(BLACK, this);
		matrix[_8][_f] = new Bishop(BLACK, this);
		
		matrix[_1][_d] = new Queen(WHITE, this);
		matrix[_8][_d] = new Queen(BLACK, this);
		
		matrix[_1][_e] = new King(WHITE, this);
		matrix[_8][_e] = new King(BLACK, this);
		
		turn = WHITE;
		inpassing = NULL;
		promotion = NULL;
		wKing = BoardPosition(_1, _e);
		bKing = BoardPosition(_8, _e);
	};
	
	Board::Board(const Board& board) {
		for (unsigned int i = _1; i <= _8; i++) {
			for (unsigned int j = _a; j <= _h; j++) {
				matrix[i][j] = (board.matrix[i][j] != NULL) ? board.matrix[i][j]->SelfCopy(this) : NULL;
			}
		}
		
		turn = board.turn;
		
		inpassing = (board.inpassing != NULL) ? new BoardPosition(*board.inpassing) : NULL;
		promotion = (board.promotion != NULL) ? new BoardPosition(*board.promotion) : NULL;
		
		wKing = board.wKing;
		bKing = board.bKing;
	};
	
	void Board::setFigureAt(const BoardPosition& position, Figure* figure) {
		matrix[position.row][position.column] = figure;
	};
	
	Figure* Board::getFigureAt(const BoardPosition& position) const {
		return matrix[position.row][position.column];
	};
	
	void Board::changeTurn() {
		turn = (turn == WHITE) ? BLACK : WHITE;
	};
	
	bool Board::isCheck() {
		return (turn == WHITE) ? underAttack(wKing, WHITE) : underAttack(bKing, BLACK);
	};
	
	bool Board::isCheckMate() {
		std::list<BoardMove> movelist;
		
		for (unsigned int i = _1; i <= _8; i++) {
			for (unsigned int j = _a; j <= _h; j++) {
				if (matrix[i][j] != NULL) {
					if (matrix[i][j]->color == turn) {
						matrix[i][j]->getMoves(movelist, BoardPosition(i, j));
					}
				}
			}
		}
		
		std::list<BoardMove>::iterator i = movelist.begin();
		while (i != movelist.end()) {
			if (moveImpossible(*i)) {
				i = movelist.erase(i);
				continue;
			}
			i++;
		}
		
		return (movelist.empty()) ? true : false;
	};
	
	bool Board::canMove(const BoardMove& move) {
		std::list<BoardMove> movelist;
		
		if (getMoves(movelist, move.startPos) != SUCCESS_GET_MOVES) {
			return false;
		}
		
		std::list<BoardMove>::iterator i = movelist.begin();
		while (i != movelist.end()) {
			if ((*i) == move) {
				return true;
			}
			i++;
		}
		
		return false;
	};
	
	bool Board::moveImpossible(const BoardMove& move) {
		Board tmpBoard(*this);
		
		if (tmpBoard.getFigureAt(move.startPos)->getType() == KING) {
			(tmpBoard.turn == WHITE) ? tmpBoard.wKing = move.endPos : tmpBoard.bKing = move.endPos;
		}
		
		if (move.moveType == ATTACK_INPASSING) {
			if (tmpBoard.turn == WHITE) {
				delete tmpBoard.getFigureAt(BoardPosition(move.endPos.row - 1, move.endPos.column));
				tmpBoard.setFigureAt(BoardPosition(move.endPos.row - 1, move.endPos.column), NULL);
			}
			else {
				delete tmpBoard.getFigureAt(BoardPosition(move.endPos.row + 1, move.endPos.column));
				tmpBoard.setFigureAt(BoardPosition(move.endPos.row + 1, move.endPos.column), NULL);
			}
		}
		
		if ((move.moveType == ATTACK) || (move.moveType == ATTACK_PROMOTION)) {
			delete tmpBoard.getFigureAt(move.endPos);
		}
		
		tmpBoard.getFigureAt(move.startPos)->isMoved = true;
		tmpBoard.setFigureAt(move.endPos, tmpBoard.getFigureAt(move.startPos));
		tmpBoard.setFigureAt(move.startPos, NULL);
		
		if (move.moveType == SHORT_CASTLING) {
			return tmpBoard.moveImpossible(BoardMove(BoardPosition(move.endPos.row, move.endPos.column + 1), BoardPosition(move.startPos.row, move.startPos.column + 1), MOVE));
		}
		if (move.moveType == LONG_CASTLING) {
			return tmpBoard.moveImpossible(BoardMove(BoardPosition(move.endPos.row, move.endPos.column - 2), BoardPosition(move.startPos.row, move.startPos.column - 1), MOVE));
		}
		
		return tmpBoard.isCheck();
	};
	
	bool Board::underAttack(const BoardPosition& position, Color color) {
		Figure* tmpFigure;
		BoardPosition curPos;
		
		curPos.row = position.row + 2;
		curPos.column = position.column + 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KNIGHT) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column + 2;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KNIGHT) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column + 2;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KNIGHT) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row - 2;
		curPos.column = position.column + 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KNIGHT) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row - 2;
		curPos.column = position.column - 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KNIGHT) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column - 2;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KNIGHT) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column - 2;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KNIGHT) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row + 2;
		curPos.column = position.column - 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KNIGHT) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column;
		while (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if ((tmpFigure->getType() == ROCK) || (tmpFigure->getType() == QUEEN)) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
				break;
			}
			curPos.row++;
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column;
		while (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if ((tmpFigure->getType() == ROCK) || (tmpFigure->getType() == QUEEN)) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
				break;
			}
			curPos.row--;
		}
		
		curPos.row = position.row;
		curPos.column = position.column + 1;
		while (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if ((tmpFigure->getType() == ROCK) || (tmpFigure->getType() == QUEEN)) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
				break;
			}
			curPos.column++;
		}
		
		curPos.row = position.row;
		curPos.column = position.column - 1;
		while (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if ((tmpFigure->getType() == ROCK) || (tmpFigure->getType() == QUEEN)) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
				break;
			}
			curPos.column--;
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column + 1;
		while (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if ((tmpFigure->getType() == BISHOP) || (tmpFigure->getType() == QUEEN)) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
				break;
			}
			curPos.row++;
			curPos.column++;
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column - 1;
		while (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if ((tmpFigure->getType() == BISHOP) || (tmpFigure->getType() == QUEEN)) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
				break;
			}
			curPos.row--;
			curPos.column--;
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column - 1;
		while (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if ((tmpFigure->getType() == BISHOP) || (tmpFigure->getType() == QUEEN)) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
				break;
			}
			curPos.row++;
			curPos.column--;
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column + 1;
		while (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if ((tmpFigure->getType() == BISHOP) || (tmpFigure->getType() == QUEEN)) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
				break;
			}
			curPos.row--;
			curPos.column++;
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KING) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KING) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row;
		curPos.column = position.column + 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KING) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row;
		curPos.column = position.column - 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KING) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column + 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KING) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column - 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KING) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column - 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KING) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column + 1;
		if (curPos.isValid()) {
			tmpFigure = getFigureAt(curPos);
			if (tmpFigure != NULL) {
				if (tmpFigure->getType() == KING) {
					if (tmpFigure->color != color) {
						return true;
					}
				}
			}
		}
		
		if (color == WHITE) {
			curPos.row = position.row + 1;
			curPos.column = position.column + 1;
			if (curPos.isValid()) {
				tmpFigure = getFigureAt(curPos);
				if (tmpFigure != NULL) {
					if (tmpFigure->color != color) {
						if (tmpFigure->getType() == PAWN) {
							return true;
						}
					}
				}
			}
			
			curPos.row = position.row + 1;
			curPos.column = position.column - 1;
			if (curPos.isValid()) {
				tmpFigure = getFigureAt(curPos);
				if (tmpFigure != NULL) {
					if (tmpFigure->color != color) {
						if (tmpFigure->getType() == PAWN) {
							return true;
						}
					}
				}
			}
		}
		else {
			curPos.row = position.row - 1;
			curPos.column = position.column + 1;
			if (curPos.isValid()) {
				tmpFigure = getFigureAt(curPos);
				if (tmpFigure != NULL) {
					if (tmpFigure->color != color) {
						if (tmpFigure->getType() == PAWN) {
							return true;
						}
					}
				}
			}
			
			curPos.row = position.row - 1;
			curPos.column = position.column - 1;
			if (curPos.isValid()) {
				tmpFigure = getFigureAt(curPos);
				if (tmpFigure != NULL) {
					if (tmpFigure->color != color) {
						if (tmpFigure->getType() == PAWN) {
							return true;
						}
					}
				}
			}
		}
		
		return false;
	};
	
	unsigned int Board::Move(const BoardMove& move) {
		if (getFigureAt(move.startPos)->getType() == KING) {
			(turn == WHITE) ? wKing = move.endPos : bKing = move.endPos;
		}
		
		if (move.moveType == ATTACK_INPASSING) {
			if (turn == WHITE) {
				delete getFigureAt(BoardPosition(move.endPos.row - 1, move.endPos.column));
				setFigureAt(BoardPosition(move.endPos.row - 1, move.endPos.column), NULL);
			}
			else {
				delete getFigureAt(BoardPosition(move.endPos.row + 1, move.endPos.column));
				setFigureAt(BoardPosition(move.endPos.row + 1, move.endPos.column), NULL);
			}
		}
		
		if ((move.moveType == ATTACK) || (move.moveType == ATTACK_PROMOTION)) {
			delete getFigureAt(move.endPos);
		}
		
		if (inpassing != NULL) {
			delete inpassing;
			inpassing = NULL;
		}
		if (promotion != NULL) {
			delete promotion;
			promotion = NULL;
		}
		
		if (move.moveType == MOVE_INPASSING) {
			inpassing = (turn == WHITE) ? new BoardPosition(move.endPos.row - 1, move.endPos.column) : new BoardPosition(move.endPos.row + 1, move.endPos.column);
		}
		
		getFigureAt(move.startPos)->isMoved = true;
		setFigureAt(move.endPos, getFigureAt(move.startPos));
		setFigureAt(move.startPos, NULL);
		
		if ((move.moveType == MOVE_PROMOTION) || (move.moveType == ATTACK_PROMOTION)) {
			promotion =  new BoardPosition(move.endPos);
			return SUCCESS_MOVE_PROMOTION;
		}
		
		if (move.moveType == SHORT_CASTLING) {
			return Move(BoardMove(BoardPosition(move.endPos.row, move.endPos.column + 1), BoardPosition(move.startPos.row, move.startPos.column + 1), MOVE));
		}
		if (move.moveType == LONG_CASTLING) {
			return Move(BoardMove(BoardPosition(move.endPos.row, move.endPos.column - 2), BoardPosition(move.startPos.row, move.startPos.column - 1), MOVE));
		}
		
		changeTurn();
		if (isCheckMate()) {
			return (isCheck()) ? SUCCESS_MOVE_CHECKMATE : SUCCESS_MOVE_DRAW;
		}
		else {
			return (isCheck()) ? SUCCESS_MOVE_CHECK : SUCCESS_MOVE;
		}
	};
	
	unsigned int Board::Promotion(PromType type) {
		Figure* tmpFigure;
		
		switch (type) {
			case PROM_QUEEN:
				tmpFigure = new Queen(getFigureAt(*promotion)->color, this);
				delete getFigureAt(*promotion);
				setFigureAt(*promotion, tmpFigure);
				break;
				
			case PROM_ROCK:
				tmpFigure = new Rock(getFigureAt(*promotion)->color, this);
				delete getFigureAt(*promotion);
				setFigureAt(*promotion, tmpFigure);
				break;
				
			case PROM_BISHOP:
				tmpFigure = new Bishop(getFigureAt(*promotion)->color, this);
				delete getFigureAt(*promotion);
				setFigureAt(*promotion, tmpFigure);
				break;
				
			case PROM_KNIGHT:
				tmpFigure = new Knight(getFigureAt(*promotion)->color, this);
				delete getFigureAt(*promotion);
				setFigureAt(*promotion, tmpFigure);
				break;
		}
		
		changeTurn();
		if (isCheckMate()) {
			return (isCheck()) ? SUCCESS_MOVE_CHECKMATE : SUCCESS_MOVE_DRAW;
		}
		else {
			return (isCheck()) ? SUCCESS_MOVE_CHECK : SUCCESS_MOVE;
		}
	};
	
	unsigned int Board::getMoves(std::list<BoardMove>& movelist, const BoardPosition& position) {
		movelist.clear();
		
		if (getFigureAt(position) != NULL) {
			if (getFigureAt(position)->color == turn) {
				getFigureAt(position)->getMoves(movelist, position);
			}
			else {
				return ERROR_GET_MOVES_WRONG_COLOR;
			}
		}
		else {
			return ERROR_GET_MOVES_WRONG_POSITION;
		}
		
		std::list<BoardMove>::iterator i = movelist.begin();
		while (i != movelist.end()) {
			if (moveImpossible(*i)) {
				i = movelist.erase(i);
				continue;
			}
			i++;
		}
		
		return (movelist.empty()) ? ERROR_GET_MOVES_CANT_MOVE : SUCCESS_GET_MOVES;
	};
	
	Board::~Board() {
		for (unsigned int i = _1; i <= _8; i++) {
			for (unsigned int j = _a; j <= _h; j++) {
				delete matrix[i][j];
			}
		}
		delete inpassing;
		delete promotion;
	};
}