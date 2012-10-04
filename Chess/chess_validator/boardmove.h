#ifndef _BOARDMOVE_H
#define _BOARDMOVE_H

#include "boardposition.h"

namespace chess {
	class BoardMove {
	public:
		BoardPosition startPos;
		BoardPosition endPos;
		MoveType moveType;
	public:
		BoardMove(BoardPosition, BoardPosition, MoveType);
		BoardMove(const BoardMove&);
		BoardMove& operator=(const BoardMove&);
		bool operator==(const BoardMove&);
		bool isValid();
		~BoardMove();
	};
};

#endif /* _BOARDMOVE_H */