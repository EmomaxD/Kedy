#include "PieceTable.h"

namespace Kedy {

    PieceTable::PieceTable(const std::string& text) {
        m_OriginalBuffer.assign(text.begin(), text.end());
        m_Pieces.emplace_back(ORIGINAL, 0, text.length());
    }

    PieceTable::~PieceTable() {}

    void PieceTable::Insert(size_t pos, const std::string& text) {
        size_t currentPos = 0; // Use size_t for currentPos
        for (size_t i = 0; i < m_Pieces.size(); ++i) {
            Piece& piece = m_Pieces[i];
            if (currentPos <= pos && pos < currentPos + piece.length) {
                SplitPiece(i, pos - currentPos);

                m_AddBuffer.insert(m_AddBuffer.end(), text.begin(), text.end());
                m_Pieces.insert(m_Pieces.begin() + i + 1, Piece(ADD, m_AddBuffer.size() - text.size(), text.size()));

                return;
            }
            currentPos += piece.length;
        }

        // If position is at the end of the text
        if (pos == currentPos) {
            m_AddBuffer.insert(m_AddBuffer.end(), text.begin(), text.end());
            m_Pieces.emplace_back(ADD, m_AddBuffer.size() - text.size(), text.size());
        }
    }

    void PieceTable::DeleteText(size_t pos, size_t length) {
        size_t currentPos = 0; // Use size_t for currentPos
        for (size_t i = 0; i < m_Pieces.size(); ++i) {
            Piece& piece = m_Pieces[i];
            if (currentPos <= pos && pos < currentPos + piece.length) {
                SplitPiece(i, pos - currentPos);

                size_t deleteEnd = pos + length; // Use size_t for deleteEnd
                while (i < m_Pieces.size() && deleteEnd > currentPos) {
                    Piece& currentPiece = m_Pieces[i];
                    size_t pieceEnd = currentPos + currentPiece.length;

                    if (deleteEnd <= pieceEnd) {
                        SplitPiece(i, deleteEnd - currentPos);
                        m_Pieces.erase(m_Pieces.begin() + i);
                        break;
                    } else {
                        m_Pieces.erase(m_Pieces.begin() + i);
                    }

                    currentPos += currentPiece.length;
                }

                return;
            }
            currentPos += piece.length;
        }
    }

    std::string PieceTable::GetText() const {
        std::string result;
        for (const Piece& piece : m_Pieces) {
            const std::vector<char>& buffer = (piece.bufferType == ORIGINAL) ? m_OriginalBuffer : m_AddBuffer;
            result.append(buffer.begin() + piece.start, buffer.begin() + piece.start + piece.length);
        }
        return result;
    }

    void PieceTable::SplitPiece(size_t pieceIndex, size_t pos) {
        Piece piece = m_Pieces[pieceIndex];
        if (pos > 0 && pos < piece.length) {
            m_Pieces[pieceIndex] = Piece(piece.bufferType, piece.start, pos);
            m_Pieces.insert(m_Pieces.begin() + pieceIndex + 1, Piece(piece.bufferType, piece.start + pos, piece.length - pos));
        }
    }
}
