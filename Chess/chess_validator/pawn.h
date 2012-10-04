#ifndef _PAWN_H
#define _PAWN_H

#include "board.h"

namespace chess {
	class Pawn : public Figure {
	protected:
		Figure* SelfCopy(const Board*);
	public:
		Pawn(Color, const Board*, bool = false);
		FigureType getType();
		void getMoves(std::list<BoardMove>&, const BoardPosition&);
		~Pawn();
	public:
		friend class Board;
	};
};

#endif /* _PAWN_H */