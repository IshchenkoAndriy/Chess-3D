#ifndef _KINGHT_H
#define _KINGHT_H

#include "board.h"

namespace chess {
	class Knight : public Figure {
	protected:
		Figure* SelfCopy(const Board*);
	public:
		Knight(Color, const Board*, bool = false);
		FigureType getType();
		void getMoves(std::list<BoardMove>&, const BoardPosition&);
		~Knight();
	public:
		friend class Board;
	};
};

#endif /* _KINGHT_H */