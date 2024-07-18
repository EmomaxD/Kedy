#include "Cursor.h"

namespace Kedy {

    Cursor::Cursor() : m_Position{0, 0} {}

    Cursor::~Cursor() {}

    void Cursor::MoveLeft(size_t amount) {    
        m_Position.column -= amount;
    }

    void Cursor::MoveRight(size_t maxPos, size_t amount) {
        m_Position.column += amount;
    }

    void Cursor::MoveUp(size_t amount) {
        m_Position.line -= amount;
    }

    void Cursor::MoveDown(size_t amount) {
        m_Position.line += amount;
    }

    void Cursor::SetPosition(CursorPosition pos) {
        m_Position = pos;
    }

    CursorPosition Cursor::GetPosition() const {
        return m_Position;
    }

}