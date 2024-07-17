#pragma once

namespace Kedy {

    class Selection {
    public:
        Selection();
        ~Selection();

        void SetStart(size_t pos);
        void SetEnd(size_t pos);
        size_t GetStart() const;
        size_t GetEnd() const;
        bool IsValid() const;

    private:
        size_t m_Start;
        size_t m_End;
    };

}