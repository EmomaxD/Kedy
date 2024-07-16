#pragma once

namespace Kedy {

    class Cursor {
    public:
        Cursor();
        ~Cursor();

        void MoveLeft(int amount = 1);
        void MoveRight(int maxPos, int amount = 1);
        void MoveUp(int amount = 1);
        void MoveDown(int amount = 1);
        void SetPosition(int pos);
        int GetPosition() const;

    private:
        int m_Position;
    };

}