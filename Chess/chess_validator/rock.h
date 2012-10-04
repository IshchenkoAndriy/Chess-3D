#ifndef _ROCK_H
#define _ROCK_H

#include "board.h"

namespace chess {
	class Rock : public Figure {
	protected:
		Figure* SelfCopy(const Board*);
	public:
		Rock(Color, const Board*, bool = false);
		FigureType getType();
		void getMoves(std::list<BoardMove>&, const BoardPosition&);
		~Rock();
	public:
		friend class Board;
	};
};

#endif /* _ROCK_H */