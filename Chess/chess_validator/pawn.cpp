#include "pawn.h"

namespace chess {
	Pawn::Pawn(Color color, const Board* board, bool isMoved) : Figure(color, board, isMoved) {
	};
	
	Figure* Pawn::SelfCopy(const Board* board) {
		Figure* tmpFigure = new Pawn(this->color, board, this->isMoved);
		return tmpFigure;
	};
	
	FigureType Pawn::getType() {
		return PAWN;
	};
	
	void Pawn::getMoves(std::list<BoardMove>& movelist, const BoardPosition& position) {
		if (this->color == WHITE) {
			BoardPosition curPos(position.row + 1, position.column);
			if (curPos.isValid()) {
				if (this->board->getFigureAt(curPos) == NULL) {
					if (curPos.row == _8) {
						movelist.push_back(BoardMove(position, curPos, MOVE_PROMOTION));
					}
					else {
						movelist.push_back(BoardMove(position, curPos, MOVE));
					}
					if (!this->isMoved) {
						curPos.row++;
						if (this->board->getFigureAt(curPos) == NULL) {
							movelist.push_back(BoardMove(position, curPos, MOVE_INPASSING));
						}
					}
				}
			}
			
			curPos.row = position.row + 1;
			curPos.column = position.column + 1;
			if (curPos.isValid()) {
				if (this->board->getFigureAt(curPos) != NULL) {
					if (this->board->getFigureAt(curPos)->color == BLACK) {
						if (curPos.row == _8) {
							movelist.push_back(BoardMove(position, curPos, ATTACK_PROMOTION));
						}
						else {
							movelist.push_back(BoardMove(position, curPos, ATTACK));
						}
					}
				}
				else if (this->board->inpassing != NULL) {
					if (curPos == *this->board->inpassing) {
						movelist.push_back(BoardMove(position, curPos, ATTACK_INPASSING));
					}
				}
			}
			
			curPos.row = position.row + 1;
			curPos.column = position.column - 1;
			if (curPos.isValid()) {
				if (this->board->getFigureAt(curPos) != NULL) {
					if (this->board->getFigureAt(curPos)->color == BLACK) {
						if (curPos.row == _8) {
							movelist.push_back(BoardMove(position, curPos, ATTACK_PROMOTION));
						}
						else {
							movelist.push_back(BoardMove(position, curPos, ATTACK));
						}
					}
				}
				else if (this->board->inpassing != NULL) {
					if (curPos == *this->board->inpassing) {
						movelist.push_back(BoardMove(position, curPos, ATTACK_INPASSING));
					}
				}
			}
		}
		else {
			BoardPosition curPos(position.row - 1, position.column);
			if (curPos.isValid()) {
				if (this->board->getFigureAt(curPos) == NULL) {
					if (curPos.row == _1) {
						movelist.push_back(BoardMove(position, curPos, MOVE_PROMOTION));
					}
					else {
						movelist.push_back(BoardMove(position, curPos, MOVE));
					}
					if (!this->isMoved) {
						curPos.row--;
						if (this->board->getFigureAt(curPos) == NULL) {
							movelist.push_back(BoardMove(position, curPos, MOVE_INPASSING));
						}
					}
				}
			}
			
			curPos.row = position.row - 1;
			curPos.column = position.column + 1;
			if (curPos.isValid()) {
				if (this->board->getFigureAt(curPos) != NULL) {
					if (this->board->getFigureAt(curPos)->color == WHITE) {
						if (curPos.row == _1) {
							movelist.push_back(BoardMove(position, curPos, ATTACK_PROMOTION));
						}
						else {
							movelist.push_back(BoardMove(position, curPos, ATTACK));
						}
					}
				}
				else if (this->board->inpassing != NULL) {
					if (curPos == *this->board->inpassing) {
						movelist.push_back(BoardMove(position, curPos, ATTACK_INPASSING));
					}
				}
			}
			
			curPos.row = position.row - 1;
			curPos.column = position.column - 1;
			if (curPos.isValid()) {
				if (this->board->getFigureAt(curPos) != NULL) {
					if (this->board->getFigureAt(curPos)->color == WHITE) {
						if (curPos.row == _1) {
							movelist.push_back(BoardMove(position, curPos, ATTACK_PROMOTION));
						}
						else {
							movelist.push_back(BoardMove(position, curPos, ATTACK));
						}
					}
				}
				else if (this->board->inpassing != NULL) {
					if (curPos == *this->board->inpassing) {
						movelist.push_back(BoardMove(position, curPos, ATTACK_INPASSING));
					}
				}
			}
		}
	};
	
	Pawn::~Pawn() {
	};
};