#ifndef _QUEEN_H
#define _QUEEN_H

#include "board.h"

namespace chess {
	class Queen : public Figure {
	protected:
		Figure* SelfCopy(const Board*);
	public:
		Queen(Color, const Board*, bool = false);
		FigureType getType();
		void getMoves(std::list<BoardMove>&, const BoardPosition&);
		~Queen();
	public:
		friend class Board;
	};
};

#endif /* _QUEEN_H */