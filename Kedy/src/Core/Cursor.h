#pragma once

namespace Kedy {

    class Cursor {
    public:
        Cursor();
        ~Cursor();

        void MoveLeft(size_t amount = 1);
        void MoveRight(size_t maxPos, size_t amount = 1);
        void MoveUp(size_t amount = 1);
        void MoveDown(size_t amount = 1);
        void SetPosition(size_t pos);
        size_t GetPosition() const;

    private:
        size_t m_Position;
    };

}