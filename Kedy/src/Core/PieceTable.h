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

		void Insert(size_t pos, const std::string& text);
		void DeleteText(size_t pos, size_t length);
		std::string GetText() const;

		inline const std::vector<char>& GetOriginalBuffer() const { return m_OriginalBuffer; };
		inline const std::vector<char>& GetAddBuffer() const { return m_AddBuffer; };
		inline const std::vector<Piece>& GetPieces() const { return m_Pieces; };

	private:
		std::vector<char> m_OriginalBuffer;
		std::vector<char> m_AddBuffer;
		std::vector<Piece> m_Pieces;

		void SplitPiece(size_t pieceIndex, size_t pos);
	};
}
