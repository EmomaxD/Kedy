#include "TextEditor.h"

namespace Kedy {

    TextEditor::TextEditor(const std::string& text)
        : m_PieceTable(text), m_ActiveCursorIndex(0) {
        AddCursor();  // Add an initial cursor
    }

    TextEditor::~TextEditor() {}

    void TextEditor::Insert(const std::string& text) {
        int pos = m_Cursors[m_ActiveCursorIndex].GetPosition();
        m_PieceTable.Insert(pos, text);
        m_Cursors[m_ActiveCursorIndex].MoveRight(m_PieceTable.GetText().length(), text.length());
    }

    void TextEditor::DeleteText(int length) {
        int pos = m_Cursors[m_ActiveCursorIndex].GetPosition();
        m_PieceTable.DeleteText(pos - length, length);
        m_Cursors[m_ActiveCursorIndex].MoveLeft(length);
    }

    std::string TextEditor::GetText() const {
        return m_PieceTable.GetText();
    }

    void TextEditor::AddCursor() {
        m_Cursors.emplace_back();
    }

    void TextEditor::RemoveCursor(int cursorIndex) {
        if (cursorIndex >= 0 && cursorIndex < m_Cursors.size()) {
            m_Cursors.erase(m_Cursors.begin() + cursorIndex);
        }
    }

    void TextEditor::MoveCursorLeft(int cursorIndex, int amount) {
        if (cursorIndex >= 0 && cursorIndex < m_Cursors.size()) {
            m_Cursors[cursorIndex].MoveLeft(amount);
        }
    }

    void TextEditor::MoveCursorRight(int cursorIndex, int amount) {
        if (cursorIndex >= 0 && cursorIndex < m_Cursors.size()) {
            m_Cursors[cursorIndex].MoveRight(GetText().length(), amount);
        }
    }

    void TextEditor::MoveCursorUp(int cursorIndex, int amount) {
        // Implement based on line logic
    }

    void TextEditor::MoveCursorDown(int cursorIndex, int amount) {
        // Implement based on line logic
    }

    void TextEditor::StartSelection(int cursorIndex) {
        if (cursorIndex >= 0 && cursorIndex < m_Cursors.size()) {
            m_Selections.emplace_back();
            m_Selections.back().SetStart(m_Cursors[cursorIndex].GetPosition());
        }
    }

    void TextEditor::UpdateSelection(int cursorIndex) {
        if (cursorIndex >= 0 && cursorIndex < m_Cursors.size()) {
            m_Selections.back().SetEnd(m_Cursors[cursorIndex].GetPosition());
        }
    }

    std::string TextEditor::GetSelectedText(int selectionIndex) const {
        if (selectionIndex >= 0 && selectionIndex < m_Selections.size()) {
            const Selection& selection = m_Selections[selectionIndex];
            if (selection.IsValid()) {
                std::string result;
                int start = selection.GetStart();
                int end = selection.GetEnd();

                int currentPos = 0;
                for (const Piece& piece : m_PieceTable.GetPieces()) {
                    int pieceEnd = currentPos + piece.length;
                    if (start < pieceEnd && end > currentPos) {
                        int pieceStart = std::max(start, currentPos) - currentPos;
                        int pieceLength = std::min(end, pieceEnd) - std::max(start, currentPos);
                        const std::vector<char>& buffer = (piece.bufferType == ORIGINAL) ? m_PieceTable.GetOriginalBuffer() : m_PieceTable.GetAddBuffer();
                        result.append(buffer.begin() + piece.start + pieceStart, buffer.begin() + piece.start + pieceStart + pieceLength);
                    }
                    currentPos += piece.length;
                }
                return result;
            }
        }
        return "";
    }

    void TextEditor::PrintEditorState() const {
        std::cout << "Text: " << GetText() << std::endl;
        std::cout << "Cursors: ";
        for (const Cursor& cursor : m_Cursors) {
            std::cout << cursor.GetPosition() << " ";
        }
        std::cout << std::endl;
    }
}