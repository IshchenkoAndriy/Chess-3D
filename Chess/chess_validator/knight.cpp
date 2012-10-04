#include "knight.h"

namespace chess {
	Knight::Knight(Color color, const Board* board, bool isMoved) : Figure(color, board, isMoved) {
	};
	
	Figure* Knight::SelfCopy(const Board* board) {
		Figure* tmpFigure = new Knight(this->color, board, this->isMoved);
		return tmpFigure;
	};
	
	FigureType Knight::getType() {
		return KNIGHT;
	};
	
	void Knight::getMoves(std::list<BoardMove>& movelist, const BoardPosition& position) {
		BoardPosition curPos(position.row + 2, position.column + 1);
		if (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column + 2;
		if (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column + 2;
		if (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
		}
		
		curPos.row = position.row - 2;
		curPos.column = position.column + 1;
		if (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
		}
		
		curPos.row = position.row - 2;
		curPos.column = position.column - 1;
		if (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
		}
		
		curPos.row = position.row - 1;
		curPos.column = position.column - 2;
		if (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
		}
		
		curPos.row = position.row + 1;
		curPos.column = position.column - 2;
		if (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
		}
		
		curPos.row = position.row + 2;
		curPos.column = position.column - 1;
		if (curPos.isValid()) {
			if (this->board->getFigureAt(curPos) != NULL) {
				if (this->board->getFigureAt(curPos)->color != this->color) {
					movelist.push_back(BoardMove(position, curPos, ATTACK));
				}
			}
			else {
				movelist.push_back(BoardMove(position, curPos, MOVE));
			}
		}
	};
	
	Knight::~Knight() {
	};
};