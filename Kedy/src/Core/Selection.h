#pragma once

namespace Kedy {

    class Selection {
    public:
        Selection();
        ~Selection();

        void SetStart(int pos);
        void SetEnd(int pos);
        int GetStart() const;
        int GetEnd() const;
        bool IsValid() const;

    private:
        int m_Start;
        int m_End;
    };

}