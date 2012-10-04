#ifndef _BOARDPOSITION_H
#define _BOARDPOSITION_H

#include "enum.h"

namespace chess {
	class BoardPosition {
	public:
		unsigned int row;
		unsigned int column;
	public:
		BoardPosition(unsigned int = _rnull, unsigned int = _cnull);
		BoardPosition(const BoardPosition&);
		BoardPosition& operator=(const BoardPosition&);
		bool operator==(const BoardPosition&);
		bool isValid();
		~BoardPosition();
	};
};

#endif /* _BOARDPOSITION_H */