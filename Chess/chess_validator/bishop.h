#ifndef _BISHOP_H
#define _BISHOP_H

#include "board.h"

namespace chess {
	class Bishop : public Figure {
	protected:
		Figure* SelfCopy(const Board*);
	public:
		Bishop(Color, const Board*, bool = false);
		FigureType getType();
		void getMoves(std::list<BoardMove>&, const BoardPosition&);
		~Bishop();
	public:
		friend class Board;
	};
};

#endif /* _BISHOP_H */