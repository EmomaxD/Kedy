#include "Selection.h"

namespace Kedy {

    Selection::Selection() : m_Start(-1), m_End(-1) {}

    Selection::~Selection() {}

    void Selection::SetStart(int pos) {
        m_Start = pos;
    }

    void Selection::SetEnd(int pos) {
        m_End = pos;
    }

    int Selection::GetStart() const {
        return m_Start;
    }

    int Selection::GetEnd() const {
        return m_End;
    }

    bool Selection::IsValid() const {
        return m_Start != -1 && m_End != -1 && m_Start <= m_End;
    }

}