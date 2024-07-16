#include "Cursor.h"

namespace Kedy {

    Cursor::Cursor() : m_Position(0) {}

    Cursor::~Cursor() {}

    void Cursor::MoveLeft(int amount) {
        if (m_Position - amount >= 0) {
            m_Position -= amount;
        }
    }

    void Cursor::MoveRight(int maxPos, int amount) {
        if (m_Position + amount <= maxPos) {
            m_Position += amount;
        }
    }

    void Cursor::MoveUp(int amount) {
        // Implement based on line logic
    }

    void Cursor::MoveDown(int amount) {
        // Implement based on line logic
    }

    void Cursor::SetPosition(int pos) {
        m_Position = pos;
    }

    int Cursor::GetPosition() const {
        return m_Position;
    }

}