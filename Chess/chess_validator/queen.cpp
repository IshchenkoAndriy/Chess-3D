#include "queen.h"

namespace chess {
	Queen::Queen(Color color, const Board* board, bool isMoved) : Figure(color, board, isMoved) {
	};
	
	Figure* Queen::SelfCopy(const Board* board) {
		Figure* tmpFigure = new Queen(this->color, board, this->isMoved);
		return tmpFigure;
	};
	
	FigureType Queen::getType() {
		return QUEEN;
	};
	
	void Queen::getMoves(std::list<BoardMove>& movelist, const BoardPosition& position) {
		BoardPosition curPos(position.row + 1, position.column);
		while (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
				break;
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
			curPos.row++;
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column;
		while (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
				break;
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
			curPos.row--;
		}
		
		curPos.row = position.row;
		curPos.column = position.column + 1;
		while (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
				break;
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
			curPos.column++;
		}
		
		curPos.row = position.row;
		curPos.column = position.column - 1;
		while (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
				break;
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
			curPos.column--;
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column + 1;
		while (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
				break;
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
			curPos.row++;
			curPos.column++;
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column - 1;
		while (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
				break;
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
			curPos.row--;
			curPos.column--;
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column - 1;
		while (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
				break;
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
			curPos.row++;
			curPos.column--;
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column + 1;
		while (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
				break;
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
			curPos.row--;
			curPos.column++;
		}
	};
	
	Queen::~Queen() {
	};
};