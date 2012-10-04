#include "boardmove.h"

namespace chess {
	BoardMove::BoardMove(BoardPosition start, BoardPosition end, MoveType type) {
		this->startPos = start;
		this->endPos = end;
		this->moveType = type;
	};
	
	BoardMove::BoardMove(const BoardMove& move) {
		this->startPos = move.startPos;
		this->endPos = move.endPos;
		this->moveType = move.moveType;
	};
	
	BoardMove& BoardMove::operator=(const BoardMove& move) {
		this->startPos = move.startPos;
		this->endPos = move.endPos;
		this->moveType = move.moveType;
		return *this;
	};
	
	bool BoardMove::operator==(const BoardMove& move) {
		if (!(this->startPos == move.startPos)) {
			return false;
		}
		if (!(this->endPos == move.endPos)) {
			return false;
		}
		if (this->moveType != move.moveType) {
			return false;
		}
		return true;
	};
	
	bool BoardMove::isValid() {
		if (!this->startPos.isValid()) {
			return false;
		}
		if (!this->endPos.isValid()) {
			return false;
		}
		switch (this->moveType) {
			case MOVE:
			case ATTACK:
			case LONG_CASTLING:
			case SHORT_CASTLING:
			case MOVE_PROMOTION:
			case ATTACK_PROMOTION:
			case MOVE_INPASSING:
			case ATTACK_INPASSING:
				break;
			default:
				return false;
		}
		return true;
	};
	
	BoardMove::~BoardMove() {
	};
};