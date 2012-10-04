#include "networkgame.h"

namespace chess {
	NetworkGame::NetworkGame(unsigned int color) {
		movelist.clear();
		side = (color == WHITE) ? WHITE : BLACK;
		status = 0;
	};
	
	void NetworkGame::getChessboard(unsigned int figures[8][8], unsigned int colors[8][8]) {
		for (unsigned int i = _1; i <= _8; i++) {
			for (unsigned int j = _a; j <= _h; j++) {
				if (chessboard.matrix[i][j] != NULL) {
					switch (chessboard.matrix[i][j]->getType()) {
						case PAWN:
							figures[i][j] = PAWN;
							colors[i][j] = (chessboard.matrix[i][j]->color == WHITE) ? WHITE : BLACK;
							break;
						case KNIGHT:
							figures[i][j] = KNIGHT;
							colors[i][j] = (chessboard.matrix[i][j]->color == WHITE) ? WHITE : BLACK;
							break;
						case ROCK:
							figures[i][j] = ROCK;
							colors[i][j] = (chessboard.matrix[i][j]->color == WHITE) ? WHITE : BLACK;
							break;
						case BISHOP:
							figures[i][j] = BISHOP;
							colors[i][j] = (chessboard.matrix[i][j]->color == WHITE) ? WHITE : BLACK;
							break;
						case QUEEN:
							figures[i][j] = QUEEN;
							colors[i][j] = (chessboard.matrix[i][j]->color == WHITE) ? WHITE : BLACK;
							break;
						case KING:
							figures[i][j] = KING;
							colors[i][j] = (chessboard.matrix[i][j]->color == WHITE) ? WHITE : BLACK;
							break;
					}
				}
				else {
					figures[i][j] = FIGURE_NULL;
					colors[i][j] = COLOR_NULL;
				}
			}
		}
	};
	
	unsigned int NetworkGame::getTurn() const {
		return chessboard.turn;
	};
	
	unsigned int NetworkGame::getSide() const {
		return side;
	};
	
	unsigned int NetworkGame::dispatchMove(std::vector<MoveStruct>* movestruct, unsigned int& promotion, char* buffer, unsigned int size) {
		if (chessboard.turn == side) {
			return ERROR_WRONG_CALL;
		}
		
		if ((status == SUCCESS_MOVE_DRAW) || (status == SUCCESS_MOVE_CHECKMATE)) {
			return ERROR_WRONG_CALL;
		}
		
		if (size != 4) {
			return ERROR_WRONG_DATA;
		}
		
		if (buffer[0] != 0x4e) {
			return ERROR_WRONG_DATA;
		}
		
		sendstruct.startRow = (buffer[1] >> 4) & 0x0f;
		sendstruct.startColumn = buffer[1] & 0x0f;
		sendstruct.endRow = (buffer[2] >> 4) & 0x0f;
		sendstruct.endColumn = buffer[2] & 0x0f;
		sendstruct.moveType = (buffer[3] >> 4) & 0x0f;
		sendstruct.promType = buffer[3] & 0x0f;
		
		BoardMove curMove(BoardPosition(sendstruct.startRow, sendstruct.startColumn), BoardPosition(sendstruct.endRow, sendstruct.endColumn), (MoveType)sendstruct.moveType);
		if (!curMove.isValid()) {
			return ERROR_WRONG_DATA;
		}
		
		if (!chessboard.canMove(curMove)) {
			return ERROR_WRONG_DATA;
		}
		
		if ((curMove.moveType == MOVE_PROMOTION) || (curMove.moveType == ATTACK_PROMOTION)) {
			switch (sendstruct.promType) {
				case PROM_QUEEN:
				case PROM_ROCK:
				case PROM_BISHOP:
				case PROM_KNIGHT:
					break;
				default:
					return ERROR_WRONG_DATA;
			}
		}
		
		status = chessboard.Move(curMove);
		
		MoveStruct tmp;
		if ((curMove.moveType == ATTACK) || (curMove.moveType == ATTACK_PROMOTION) || (curMove.moveType == ATTACK_INPASSING)) {
			if (curMove.moveType == ATTACK_INPASSING) {
				tmp.startRow = (chessboard.turn == WHITE) ? (curMove.endPos.row + 1) : (curMove.endPos.row - 1);
			}
			else {
				tmp.startRow = curMove.endPos.row;
			}
			tmp.startColumn = curMove.endPos.column;
			tmp.endRow = _rnull;
			tmp.endColumn = _cnull;
			movestruct->push_back(tmp);
		}
		
		tmp.startRow = curMove.startPos.row;
		tmp.startColumn = curMove.startPos.column;
		tmp.endRow = curMove.endPos.row;
		tmp.endColumn = curMove.endPos.column;
		movestruct->push_back(tmp);
		
		if ((curMove.moveType == SHORT_CASTLING) || (curMove.moveType == LONG_CASTLING)) {
			tmp.startRow = curMove.endPos.row;
			tmp.endRow = curMove.startPos.row;
			if (curMove.moveType == SHORT_CASTLING) {
				tmp.startColumn = curMove.endPos.column + 1;
				tmp.endColumn = curMove.startPos.column + 1;
			}
			else {
				tmp.startColumn = curMove.endPos.column - 2;
				tmp.endColumn = curMove.startPos.column - 1;
			}
			movestruct->push_back(tmp);
		}
		
		if (status == SUCCESS_MOVE_PROMOTION) {
			promotion = sendstruct.promType;
			
			status = chessboard.Promotion((PromType)sendstruct.promType);
			
			tmp.startRow = chessboard.promotion->row;
			tmp.startColumn = chessboard.promotion->column;
			tmp.endRow = chessboard.promotion->row;
			tmp.endColumn = chessboard.promotion->column;
			movestruct->push_back(tmp);
		}
		else {
			promotion = PROM_NULL;
		}
		
		if ((status == SUCCESS_MOVE_CHECK) || (status == SUCCESS_MOVE_CHECKMATE)) {
			if (chessboard.turn == WHITE) {
				tmp.startRow = chessboard.wKing.row;
				tmp.startColumn = chessboard.wKing.column;
				tmp.endRow = chessboard.wKing.row;
				tmp.endColumn = chessboard.wKing.column;
			}
			else {
				tmp.startRow = chessboard.bKing.row;
				tmp.startColumn = chessboard.bKing.column;
				tmp.endRow = chessboard.bKing.row;
				tmp.endColumn = chessboard.bKing.column;
			}
			movestruct->push_back(tmp);
		}
		
		return status;
	};
	
	unsigned int NetworkGame::getMoves(unsigned int row, unsigned int column, unsigned int highlight[8][8], unsigned int moves[8][8]) {
		BoardPosition movePos(row, column);
		
		if (chessboard.turn != side) {
			return ERROR_WRONG_CALL;
		}
		
		if ((status == SUCCESS_MOVE_DRAW) || (status == SUCCESS_MOVE_CHECKMATE) || (status == SUCCESS_MOVE_PROMOTION)) {
			return ERROR_WRONG_CALL;
		}
		
		if (!movePos.isValid()) {
			return ERROR_GET_MOVES_WRONG_POSITION;
		}
		
		status = chessboard.getMoves(movelist, movePos);
		
		if (status == SUCCESS_GET_MOVES) {
			for (unsigned int i = _1; i <= _8; i++) {
				for (unsigned int j = _a; j <= _h; j++) {
					highlight[i][j] = MOVE_NULL;
				}
			}
			
			highlight[row][column] = MOVE_CURPOS;
			for (std::list<BoardMove>::iterator i = movelist.begin(); i != movelist.end(); i++) {
				highlight[(*i).endPos.row][(*i).endPos.column] = (*i).moveType;
			}
			
			for (unsigned int i = _1; i <= _8; i++) {
				for (unsigned int j = _a; j <= _h; j++) {
					moves[i][j] = 0;
				}
			}
			
			unsigned int j = 1;
			for (std::list<BoardMove>::iterator i = movelist.begin(); i != movelist.end(); i++) {
				moves[(*i).endPos.row][(*i).endPos.column] = j;
				j++;
			}
		}
		
		return status;
	};
	
	unsigned int NetworkGame::Move(unsigned int movenumber, std::vector<MoveStruct>* movestruct, char*& buffer, unsigned int& size) {
		size = 0;
		buffer = NULL;
		
		if (chessboard.turn != side) {
			return ERROR_WRONG_CALL;
		}
		
		if (status != SUCCESS_GET_MOVES) {
			return ERROR_WRONG_CALL;
		}
		
		if ((movenumber == 0) || (movenumber > movelist.size())) {
			return ERROR_MOVE_WRONG_POSITION;
		}
		
		unsigned int curnumber = 1;
		std::list<BoardMove>::iterator i = movelist.begin();
		while (curnumber < movenumber) {
			curnumber++;
			i++;
		}
		
		status = chessboard.Move(*i);
		
		sendstruct.startRow = (*i).startPos.row;
		sendstruct.startColumn = (*i).startPos.column;
		sendstruct.endRow = (*i).endPos.row;
		sendstruct.endColumn = (*i).endPos.column;
		sendstruct.moveType = (*i).moveType;
		sendstruct.promType = PROM_NULL;
		
		if (status != SUCCESS_MOVE_PROMOTION) {
			size = 4;
			buffer = new char[4];
			buffer[0] = 0x4e;
			buffer[1] = ((sendstruct.startRow & 0x0f) << 4) + (sendstruct.startColumn & 0x0f);
			buffer[2] = ((sendstruct.endRow & 0x0f) << 4) + (sendstruct.endColumn & 0x0f);
			buffer[3] = ((sendstruct.moveType & 0x0f) << 4) + (sendstruct.promType & 0x0f);
		}
		
		MoveStruct tmp;
		if (((*i).moveType == ATTACK) || ((*i).moveType == ATTACK_PROMOTION) || ((*i).moveType == ATTACK_INPASSING)) {
			if ((*i).moveType == ATTACK_INPASSING) {
				tmp.startRow = (chessboard.turn == WHITE) ? ((*i).endPos.row + 1) : ((*i).endPos.row - 1);
			}
			else {
				tmp.startRow = (*i).endPos.row;
			}
			tmp.startColumn = (*i).endPos.column;
			tmp.endRow = _rnull;
			tmp.endColumn = _cnull;
			movestruct->push_back(tmp);
		}
		
		tmp.startRow = (*i).startPos.row;
		tmp.startColumn = (*i).startPos.column;
		tmp.endRow = (*i).endPos.row;
		tmp.endColumn = (*i).endPos.column;
		movestruct->push_back(tmp);
		
		if (((*i).moveType == SHORT_CASTLING) || ((*i).moveType == LONG_CASTLING)) {
			tmp.startRow = (*i).endPos.row;
			tmp.endRow = (*i).startPos.row;
			if ((*i).moveType == SHORT_CASTLING) {
				tmp.startColumn = (*i).endPos.column + 1;
				tmp.endColumn = (*i).startPos.column + 1;
			}
			else {
				tmp.startColumn = (*i).endPos.column - 2;
				tmp.endColumn = (*i).startPos.column - 1;
			}
			movestruct->push_back(tmp);
		}
		
		if ((status == SUCCESS_MOVE_CHECK) || (status == SUCCESS_MOVE_CHECKMATE)) {
			if (chessboard.turn == WHITE) {
				tmp.startRow = chessboard.wKing.row;
				tmp.startColumn = chessboard.wKing.column;
				tmp.endRow = chessboard.wKing.row;
				tmp.endColumn = chessboard.wKing.column;
			}
			else {
				tmp.startRow = chessboard.bKing.row;
				tmp.startColumn = chessboard.bKing.column;
				tmp.endRow = chessboard.bKing.row;
				tmp.endColumn = chessboard.bKing.column;
			}
			movestruct->push_back(tmp);
		}
		
		return status;
	};
	
	unsigned int NetworkGame::Promotion(unsigned int promtype, std::vector<MoveStruct>* movestruct, char*& buffer, unsigned int& size) {
		size = 0;
		buffer = NULL;
		
		if (chessboard.turn != side) {
			return ERROR_WRONG_CALL;
		}
		
		if (status != SUCCESS_MOVE_PROMOTION) {
			return ERROR_WRONG_CALL;
		}
		
		if ((promtype != PROM_QUEEN) && (promtype != PROM_ROCK) && (promtype != PROM_BISHOP) && (promtype != PROM_KNIGHT)) {
			return ERROR_PROMOTION_WRONG_TYPE;
		}
		
		status = chessboard.Promotion((PromType)promtype);
		
		sendstruct.promType = promtype;
		
		size = 4;
		buffer = new char[4];
		buffer[0] = 0x4e;
		buffer[1] = ((sendstruct.startRow & 0x0f) << 4) + (sendstruct.startColumn & 0x0f);
		buffer[2] = ((sendstruct.endRow & 0x0f) << 4) + (sendstruct.endColumn & 0x0f);
		buffer[3] = ((sendstruct.moveType & 0x0f) << 4) + (sendstruct.promType & 0x0f);
		
		MoveStruct tmp;
		tmp.startRow = chessboard.promotion->row;
		tmp.startColumn = chessboard.promotion->column;
		tmp.endRow = chessboard.promotion->row;
		tmp.endColumn = chessboard.promotion->column;
		movestruct->push_back(tmp);
		
		if ((status == SUCCESS_MOVE_CHECK) || (status == SUCCESS_MOVE_CHECKMATE)) {
			if (chessboard.turn == WHITE) {
				tmp.startRow = chessboard.wKing.row;
				tmp.startColumn = chessboard.wKing.column;
				tmp.endRow = chessboard.wKing.row;
				tmp.endColumn = chessboard.wKing.column;
			}
			else {
				tmp.startRow = chessboard.bKing.row;
				tmp.startColumn = chessboard.bKing.column;
				tmp.endRow = chessboard.bKing.row;
				tmp.endColumn = chessboard.bKing.column;
			}
			movestruct->push_back(tmp);
		}
		
		return status;
	};
	
	NetworkGame::~NetworkGame() {
	};
};