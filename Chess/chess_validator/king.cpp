#include "king.h"

namespace chess {
	King::King(Color color, const Board* board, bool isMoved) : Figure(color, board, isMoved) {
	};
	
	Figure* King::SelfCopy(const Board* board) {
		Figure* tmpFigure = new King(this->color, board, this->isMoved);
		return tmpFigure;
	};
	
	FigureType King::getType() {
		return KING;
	};
	
	void King::getMoves(std::list<BoardMove>& movelist, const BoardPosition& position) {
		BoardPosition curPos(position.row + 1, position.column);
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
		curPos.column = position.column;
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
		
		curPos.row = position.row;
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
		
		curPos.row = position.row;
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
		
		curPos.row = position.row + 1;
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
		
		curPos.row = position.row - 1;
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
		
		curPos.row = position.row + 1;
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
		
		if (!this->isMoved) {
			curPos.row = position.row;
			curPos.column = position.column + 1;
			if (this->board->getFigureAt(curPos) == NULL) {
				curPos.column++;
				if (this->board->getFigureAt(curPos) == NULL) {
					curPos.column++;
					if (this->board->getFigureAt(curPos) != NULL) {
						if (!this->board->getFigureAt(curPos)->isMoved) {
							if (this->board->getFigureAt(curPos)->getType() == ROCK) {
								if (this->board->getFigureAt(curPos)->color == this->color) {
									curPos.column--;
									movelist.push_back(BoardMove(position, curPos, SHORT_CASTLING));
								}
							}
						}
					}
				}
			}
			
			curPos.row = position.row;
			curPos.column = position.column - 1;
			if (this->board->getFigureAt(curPos) == NULL) {
				curPos.column--;
				if (this->board->getFigureAt(curPos) == NULL) {
					curPos.column--;
					if (this->board->getFigureAt(curPos) == NULL) {
						curPos.column--;
						if (this->board->getFigureAt(curPos) != NULL) {
							if (!this->board->getFigureAt(curPos)->isMoved) {
								if (this->board->getFigureAt(curPos)->getType() == ROCK) {
									if (this->board->getFigureAt(curPos)->color == this->color) {
										curPos.column++;
										curPos.column++;
										movelist.push_back(BoardMove(position, curPos, LONG_CASTLING));
									}
								}
							}
						}
					}
				}
			}
		}
	};
	
	King::~King() {
	};
};