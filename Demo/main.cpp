#include "Kedy.h"

int main() {
    Kedy::PieceTable Editor("Hello, world!");
    Editor.Insert(7, "beautiful ");
    std::cout << Editor.GetText() << std::endl; // Outputs: Hello, beautiful world!

    Editor.DeleteText(7, 10);
    std::cout << Editor.GetText() << std::endl; // Outputs: Hello, world!

    return 0;
}
