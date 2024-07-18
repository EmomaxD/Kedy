#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

#include "PieceTable.h"
#include "Cursor.h"
#include "Selection.h"

namespace Kedy {

    struct Document {
        std::filesystem::path path;
        std::string name;
        std::string extension;
        std::string eol;
        size_t lineCount;
        size_t charCount;
        size_t whiteSpaceCount;
        size_t totalLength;
    };

    class TextEditor {
    public:
        explicit TextEditor(const std::string& text);
        explicit TextEditor(const std::filesystem::path& path);

        ~TextEditor();

        void Insert(const std::string& text);
        void DeleteText(int length);
        std::string GetText() const;
        inline size_t GetLineCount() const { return m_Document.lineCount; }
        inline size_t GetCharCount() const { return m_Document.charCount; }
        inline size_t GetWhiteSpaceCount() const { return m_Document.whiteSpaceCount; }
        inline size_t GetTotalLength() const { return m_Document.totalLength; }
        inline std::string GetFileName() const { return m_Document.name; }
        inline std::string GetExtension() const { return m_Document.extension; }
        inline std::filesystem::path GetPath() const { return m_Document.path; }
        inline std::string GetEndOfLine() const { return m_Document.eol; }


        void AddCursor();
        void RemoveCursor(int cursorIndex);
        void MoveCursorLeft(int cursorIndex, int amount = 1);
        void MoveCursorRight(int cursorIndex, int amount = 1);
        void MoveCursorUp(int cursorIndex, int amount = 1);
        void MoveCursorDown(int cursorIndex, int amount = 1);
        void StartSelection(int cursorIndex);
        void UpdateSelection(int cursorIndex);
        std::string GetSelectedText(int selectionIndex) const;

        void PrintEditorState() const;
        void PrintDocumentInfo() const;
        void PrintText();

        void PrintPositionInfo() const;

    private:
        std::string ReadFromFile(const std::filesystem::path& filePath);
        void SaveToFile(const std::filesystem::path& filePath) const;
        void FillDocumentInfo(const std::filesystem::path& filePath, const std::string& buffer);

        void CountChars(const std::string& buffer);
        void FillPositionInfo(const std::string& buffer);


    private:
        PieceTable m_PieceTable;
        Document m_Document;
        std::vector<Cursor> m_Cursors;
        std::vector<Selection> m_Selections;
        std::unordered_map<size_t, std::pair<size_t, size_t>> m_PositionInfo; // line, {startingPosition, endPosition}
        int m_ActiveCursorIndex;
    };
}