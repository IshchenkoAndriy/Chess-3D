#include "bishop.h"

namespace chess {
	Bishop::Bishop(Color color, const Board* board, bool isMoved) : Figure(color, board, isMoved) {
	};
	
	Figure* Bishop::SelfCopy(const Board* board) {
		Figure* tmpFigure = new Bishop(this->color, board, this->isMoved);
		return tmpFigure;
	};
	
	FigureType Bishop::getType() {
		return BISHOP;
	};
	
	void Bishop::getMoves(std::list<BoardMove>& movelist, const BoardPosition& position) {
		BoardPosition curPos(position.row + 1, position.column + 1);
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
	
	Bishop::~Bishop() {
	};
};