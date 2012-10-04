#include "boardposition.h"

namespace chess {
	BoardPosition::BoardPosition(unsigned int row, unsigned int column) {
		this->row = row;
		this->column = column;
	};
	
	BoardPosition::BoardPosition(const BoardPosition& position) {
		this->row = position.row;
		this->column = position.column;
	};
	
	BoardPosition& BoardPosition::operator=(const BoardPosition& position) {
		this->row = position.row;
		this->column = position.column;
		return *this;
	};
	
	bool BoardPosition::operator==(const BoardPosition& position) {
		if (this->row != position.row) {
			return false;
		}
		if (this->column != position.column) {
			return false;
		}
		return true;
	};
	
	bool BoardPosition::isValid() {
		if (!((this->row >= _1) && (this->row <= _8))) {
			return false;
		}
		if (!((this->column >= _a) && (this->column <= _h))) {
			return false;
		}
		return true;
	};
	
	BoardPosition::~BoardPosition() {
	};
};