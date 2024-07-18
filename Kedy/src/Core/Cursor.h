#pragma once

namespace Kedy {

    struct CursorPosition {
        size_t line;
        size_t column;
    };

    class Cursor {
    public:
        Cursor();
        ~Cursor();

        void MoveLeft(size_t amount = 1);
        void MoveRight(size_t maxPos, size_t amount = 1);
        void MoveUp(size_t amount = 1);
        void MoveDown(size_t amount = 1);
        void SetPosition(CursorPosition pos);
        CursorPosition GetPosition() const;

    private:
        CursorPosition m_Position;
    };

}