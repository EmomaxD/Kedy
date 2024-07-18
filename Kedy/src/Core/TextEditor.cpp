#include "TextEditor.h"

#include <fstream>
#include <sstream>

namespace Kedy {

    TextEditor::TextEditor(const std::string& text)
        : m_PieceTable(text), m_ActiveCursorIndex(0) {
        AddCursor();
    }

    TextEditor::TextEditor(const std::filesystem::path& path)
        : m_PieceTable(""), m_ActiveCursorIndex(0) {
            AddCursor();
            std::string& buffer = ReadFromFile(path);
            m_PieceTable = PieceTable(buffer);
            FillDocumentInfo(path, buffer);
            FillPositionInfo(buffer);
    }

    TextEditor::~TextEditor() {}

    void TextEditor::Insert(const std::string& text) {
        auto cursorPosition = m_Cursors[m_ActiveCursorIndex].GetPosition();
        size_t position = m_PositionInfo[cursorPosition.line].first + cursorPosition.column;
        m_PieceTable.Insert(position, text);
        m_Cursors[m_ActiveCursorIndex].MoveRight(m_PieceTable.GetText().length(), text.length());
    }

    void TextEditor::DeleteText(int length) {
        auto cursorPosition = m_Cursors[m_ActiveCursorIndex].GetPosition();
        size_t position = m_PositionInfo[cursorPosition.line].first + cursorPosition.column;
        m_PieceTable.DeleteText(position - length, length);
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

        }
    }

    void TextEditor::UpdateSelection(int cursorIndex) {
        if (cursorIndex >= 0 && cursorIndex < m_Cursors.size()) {
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
            auto& pos = cursor.GetPosition();
            std::cout << "{ " << pos.line << ", " << pos.line << "} || "; 
        }
        std::cout << std::endl;
    }

    void TextEditor::PrintDocumentInfo() const {
        std::cout << "Path: " << m_Document.path << std::endl;
        std::cout << "Name: " << m_Document.name << std::endl; 
        std::cout << "Extension: " << m_Document.extension << std::endl;
        std::cout << "EOL: " << m_Document.eol << std::endl;
        std::cout << "Char count: " << m_Document.charCount << std::endl;
        std::cout << "WhiteSpace count: " << m_Document.whiteSpaceCount << std::endl;
        std::cout << "Total Length: " << m_Document.totalLength << std::endl;
        std::cout << "Line count: " << m_Document.lineCount << std::endl;
    }

    void TextEditor::PrintText() {
        std::cout << m_PieceTable.GetText() << std::endl;
    }

    std::string TextEditor::ReadFromFile(const std::filesystem::path& filePath) {
        std::ifstream file(filePath, std::ios::binary)   ;
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filePath.string() << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string fileContent = buffer.str();
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

    void TextEditor::CountChars(const std::string& buffer) {
        size_t charCount = 0;
        size_t lineCount = 1;
        size_t whitespaceCount = 0;
        std::string eol = "LF";

        for(int i = 0; i < buffer.length(); ++i) {

            char c = buffer[i];

            if(c == '\n')
                lineCount += 1;
            
            else if (c == '\r') {
                if(i + 1 < buffer.length() && buffer[i + 1] == '\n') {
                    eol = "CRLF";
                    lineCount += 1;
                    i += 1;
                }
            }

            else if (isspace(c))
                whitespaceCount += 1;

            else
                charCount += 1;

        }

        m_Document.charCount = charCount;
        m_Document.lineCount = lineCount;
        m_Document.whiteSpaceCount = whitespaceCount;
        m_Document.eol = eol;
        m_Document.totalLength = buffer.length();
    }

    void TextEditor::FillPositionInfo(const std::string& buffer) {

        size_t column = 1;
        size_t line = 0;
        size_t startPos = 1;
        size_t endPos = 0; // NOT INDEXES

        for(int i = 0; i < buffer.length(); ++i) {

            char c = buffer[i];

            std::string eol = m_Document.eol;
            auto eolSize = eol.length() / 2;

            if(c == '\n') {
                line += 1;
                endPos = startPos + column- 1;
                m_PositionInfo.insert({line, std::make_pair(startPos, endPos)});
                startPos = endPos + eolSize;
                column = 0;
            }
            
            else if (c == '\r') {
                if(i + 1 < buffer.length() && buffer[i + 1] == '\n') {
                    line += 1;
                    endPos = startPos + column - 1;
                    m_PositionInfo.insert({line, std::make_pair(startPos, endPos)});
                    startPos = endPos + eolSize;
                    column = 0;
                    i += 1; // Skip '\n'
                }
            }
            column += 1;
        }
        line += 1;
        endPos = startPos + column - 1;
        m_PositionInfo.insert({ line, std::make_pair(startPos, endPos) });
    }

    void TextEditor::FillDocumentInfo(const std::filesystem::path& filePath, const std::string& buffer){
        std::string name = filePath.filename().string();
        std::string extension = filePath.extension().string();

        m_Document.path = std::filesystem::absolute(filePath);
        m_Document.name = name;
        m_Document.extension = extension;

        CountChars(buffer);
    }

    void TextEditor::PrintPositionInfo() const {
        auto it = m_PositionInfo.begin();

        while(it != m_PositionInfo.end())
        {
            std::cout << "Line: " << it->first << " "; 
            std::cout << "Start Position: " << it->second.first << " ";
            std::cout << "End Position: " << it->second.second << std::endl;

            it++;
        }
    }

}