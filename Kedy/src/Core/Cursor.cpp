#include "Cursor.h"

namespace Kedy {

    Cursor::Cursor() : m_Position(0) {}

    Cursor::~Cursor() {}

    void Cursor::MoveLeft(size_t amount) {
        if (m_Position - amount >= 0) {
            m_Position -= amount;
        }
    }

    void Cursor::MoveRight(size_t maxPos, size_t amount) {
        if (m_Position + amount <= maxPos) {
            m_Position += amount;
        }
    }

    void Cursor::MoveUp(size_t amount) {
        // Implement based on line logic
    }

    void Cursor::MoveDown(size_t amount) {
        // Implement based on line logic
    }

    void Cursor::SetPosition(size_t pos) {
        m_Position = pos;
    }

    size_t Cursor::GetPosition() const {
        return m_Position;
    }

}