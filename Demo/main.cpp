#include "Kedy.h"

int main() {
    Kedy::TextEditor editor("Hello, world!");
    
    editor.MoveCursorRight(0, 7);
    editor.Insert("beautiful ");
    std::cout << editor.GetText() << std::endl; // Outputs: Hello, beautiful world!


    editor.DeleteText(10);
    std::cout << editor.GetText() << std::endl; // Outputs: Hello, world!

    editor.PrintEditorState();

    return 0;
}
