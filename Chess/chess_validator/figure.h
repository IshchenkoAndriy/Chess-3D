#ifndef _FIGURE_H
#define _FIGURE_H

#include <list>
#include "boardmove.h"

namespace chess {
	class Board;
	class Figure {
	protected:
		const Board* board;
	public:
		Color color;
		bool isMoved;
	protected:
		virtual Figure* SelfCopy(const Board*) = 0;
	public:
		Figure(Color, const Board*, bool = false);
		virtual FigureType getType() = 0;
		virtual void getMoves(std::list<BoardMove>&, const BoardPosition&) = 0;
		virtual ~Figure();
	public:
		friend class Board;
	};
};

#endif /* _FIGURE_H */