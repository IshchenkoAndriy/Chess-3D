#ifndef _KING_H
#define _KING_H

#include "board.h"

namespace chess {
	class King : public Figure {
	protected:
		Figure* SelfCopy(const Board*);
	public:
		King(Color, const Board*, bool = false);
		FigureType getType();
		void getMoves(std::list<BoardMove>&, const BoardPosition&);
		~King();
	public:
		friend class Board;
	};
};

#endif /* _KING_H */