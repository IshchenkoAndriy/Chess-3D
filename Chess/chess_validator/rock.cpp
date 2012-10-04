#include "rock.h"

namespace chess {
	Rock::Rock(Color color, const Board* board, bool isMoved) : Figure(color, board, isMoved) {
	};
	
	Figure* Rock::SelfCopy(const Board* board) {
		Figure* tmpFigure = new Rock(this->color, board, this->isMoved);
		return tmpFigure;
	};
	
	FigureType Rock::getType() {
		return ROCK;
	};
	
	void Rock::getMoves(std::list<BoardMove>& movelist, const BoardPosition& position) {
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
	};
	
	Rock::~Rock() {
	};
};