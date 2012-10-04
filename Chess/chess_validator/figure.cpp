#include "figure.h"

namespace chess {
	Figure::Figure(Color color, const Board* board, bool isMoved) {
		this->color = color;
		this->board = board;
		this->isMoved = isMoved;
	};
	
	Figure::~Figure() {
	};
};