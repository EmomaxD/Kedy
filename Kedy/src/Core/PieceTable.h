#pragma once

#include "Piece.h"

#include <vector>
#include <string>
#include <iostream>

namespace Kedy {

	class PieceTable {
		public:
		PieceTable(const std::string& text);
		~PieceTable();

		void Insert(int pos, const std::string& text);
		void DeleteText(int pos, int length);
		std::string GetText() const;

	private:
		std::vector<char> m_OriginalBuffer;
		std::vector<char> m_AddBuffer;
		std::vector<Piece> m_Pieces;

		void SplitPiece(int pieceIndex, int pos);
	};
}
