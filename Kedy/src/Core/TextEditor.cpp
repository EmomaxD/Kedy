#include "TextEditor.h"

#include <fstream>
#include <sstream>

namespace Kedy {

    TextEditor::TextEditor(const std::string& text)
        : m_PieceTable(text), m_ActiveCursorIndex(0) {
        AddCursor();  // Add an initial cursor
    }

    TextEditor::TextEditor(const std::filesystem::path& path)
        : m_PieceTable(""), m_ActiveCursorIndex(0) {
            AddCursor();
            ReadFromFile(path);
            FillDocumentInfo(path);
    }

    TextEditor::~TextEditor() {}

    void TextEditor::Insert(const std::string& text) {
        auto pos = m_Cursors[m_ActiveCursorIndex].GetPosition();
        m_PieceTable.Insert(pos, text);
        m_Cursors[m_ActiveCursorIndex].MoveRight(m_PieceTable.GetText().length(), text.length());
    }

    void TextEditor::DeleteText(int length) {
        auto pos = m_Cursors[m_ActiveCursorIndex].GetPosition();
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
                size_t start = selection.GetStart();
                size_t end = selection.GetEnd();

                size_t currentPos = 0;
                for (const Piece& piece : m_PieceTable.GetPieces()) {
                    size_t pieceEnd = currentPos + piece.length;
                    if (start < pieceEnd && end > currentPos) {
                        size_t pieceStart = std::max(start, currentPos) - currentPos;
                        size_t pieceLength = std::min(end, pieceEnd) - std::max(start, currentPos);
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

    std::string TextEditor::ReadFromFile(const std::filesystem::path& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath.string() << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string fileContent = buffer.str();

        m_PieceTable = PieceTable(fileContent);

        m_Cursors.clear();
        m_Selections.clear();
        m_ActiveCursorIndex = 0;

        size_t lineCount = 0;
        size_t charCount = 0;
        size_t whitespaceCount = 0;

        bool inLine = false;
        for (size_t i = 0; i < fileContent.length(); ++i) {
            char currentChar = fileContent[i];

            if (currentChar == '\n') {
                lineCount++;
                inLine = false;
                m_Document.eol = "LF";
            } else if (currentChar == '\r') {
                // Check for CRLF
                std::cout << "Found CRLF\n";
                if (i + 1 < fileContent.length() && fileContent[i + 1] == '\n') {
                    lineCount++;
                    i++; // Skip the next character
                    m_Document.eol = "CRLF";
                } else {
                    lineCount++;
                }
                inLine = false;
            } else {
                inLine = true;

                if (std::isspace(currentChar)) {
                    whitespaceCount++;
                } else {
                    charCount++;
                }
            }
        }

        if (inLine) {
            lineCount++;
        }

        m_Document.lineCount = lineCount;
        m_Document.charCount = charCount;
        m_Document.whiteSpaceCount = whitespaceCount;
        m_Document.totalLength = fileContent.length(); // Differs than charCount + whitespaceCount
        return fileContent;
    }


    void TextEditor::SaveToFile(const std::filesystem::path& filePath) const {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }

        file << m_PieceTable.GetText();
        if (!file) {
            std::cerr << "Failed to write to file: " << filePath << std::endl;
        }
    }

    void TextEditor::FillDocumentInfo(const std::filesystem::path& filePath){
        std::string name = filePath.filename().string();
        std::string extension = filePath.extension().string();

        m_Document.name = name;
        m_Document.extension = extension;
    }
}