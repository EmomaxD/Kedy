#include <iostream>
#include <vector>
#include <string>

#include "PieceTable.h"
#include "Cursor.h"
#include "Selection.h"

namespace Kedy {

    class TextEditor {
    public:
        TextEditor(const std::string& text);
        ~TextEditor();

        void Insert(const std::string& text);
        void DeleteText(int length);
        std::string GetText() const;

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

    private:
        PieceTable m_PieceTable;
        std::vector<Cursor> m_Cursors;
        std::vector<Selection> m_Selections;
        int m_ActiveCursorIndex;
    };
}