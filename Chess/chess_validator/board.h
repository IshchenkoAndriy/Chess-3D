#ifndef _BOARD_H
#define _BOARD_H

#include "figure.h"
#include "pawn.h"
#include "knight.h"
#include "rock.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

namespace chess {
	class Board {
	protected:
		Figure* matrix[8][8];
		Color turn;
		BoardPosition* inpassing;
		BoardPosition* promotion;
		BoardPosition wKing, bKing;
	private:
		Board(const Board&);
		void changeTurn();
		bool isCheck();
		bool isCheckMate();
		bool moveImpossible(const BoardMove&);
		bool underAttack(const BoardPosition&, Color);
		void setFigureAt(const BoardPosition&, Figure*);
	protected:
		bool canMove(const BoardMove&);
		Figure* getFigureAt(const BoardPosition&) const;
		unsigned int Move(const BoardMove&);
		unsigned int Promotion(PromType);
		unsigned int getMoves(std::list<BoardMove>&, const BoardPosition&);
	public:
		Board();
		~Board();
	public:
		friend class Figure;
		friend class Pawn;
		friend class Knight;
		friend class Rock;
		friend class Bishop;
		friend class Queen;
		friend class King;
		friend class LocalGame;
		friend class NetworkGame;
	};
};

#endif /* _BOARD_H */