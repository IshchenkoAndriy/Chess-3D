#ifndef _NETWORKGAME_H
#define _NETWORKGAME_H

#include <vector>
#include "board.h"

namespace chess {
	class NetworkGame {
	private:
		Color side;
		Board chessboard;
		std::list<BoardMove> movelist;
		unsigned int status;
		SendStruct sendstruct;
	public:
		NetworkGame(unsigned int = WHITE);
		void getChessboard(unsigned int[8][8], unsigned int[8][8]);
		unsigned int getTurn() const;
		unsigned int getSide() const;
		unsigned int dispatchMove(std::vector<MoveStruct>*, unsigned int&, char*, unsigned int);
		unsigned int Move(unsigned int, std::vector<MoveStruct>*, char*&, unsigned int&);
		unsigned int Promotion(unsigned int, std::vector<MoveStruct>*, char*&, unsigned int&);
		unsigned int getMoves(unsigned int, unsigned int, unsigned int[8][8], unsigned int[8][8]);
		~NetworkGame();
	};
};

#endif /* _NETWORKGAME_H */