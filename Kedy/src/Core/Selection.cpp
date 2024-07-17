#include "Selection.h"

namespace Kedy {

    Selection::Selection() : m_Start(-1), m_End(-1) {}

    Selection::~Selection() {}

    void Selection::SetStart(size_t pos) {
        m_Start = pos;
    }

    void Selection::SetEnd(size_t pos) {
        m_End = pos;
    }

    size_t Selection::GetStart() const {
        return m_Start;
    }

    size_t Selection::GetEnd() const {
        return m_End;
    }

    bool Selection::IsValid() const {
        return m_Start != -1 && m_End != -1 && m_Start <= m_End;
    }

}