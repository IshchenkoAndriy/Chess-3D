#ifndef _LOCALGAME_H
#define _LOCALGAME_H

#include <vector>
#include "board.h"

namespace chess {
	class LocalGame {
	private:
		Board chessboard;
		std::list<BoardMove> movelist;
		unsigned int status;
	public:
		LocalGame();
		void getChessboard(unsigned int[8][8], unsigned int[8][8]);
		unsigned int getTurn() const;
		unsigned int Move(unsigned int, std::vector<MoveStruct>*);
		unsigned int Promotion(unsigned int, std::vector<MoveStruct>*);
		unsigned int getMoves(unsigned int, unsigned int, unsigned int[8][8], unsigned int[8][8]);
		~LocalGame();
	};
};

#endif /* _LOCALGAME_H */