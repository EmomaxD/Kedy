#include "Kedy.h"

int main() {

#if 0
    Kedy::TextEditor editor((std::string)"Hello, world!");
    
    editor.MoveCursorRight(0, 7);
    editor.Insert("beautiful ");
    std::cout << editor.GetText() << std::endl; // Outputs: Hello, beautiful world!


    editor.DeleteText(10);
    std::cout << editor.GetText() << std::endl; // Outputs: Hello, world!

    editor.PrintEditorState();
#endif

#if 1
    Kedy::TextEditor editor((std::filesystem::path)"Demo.txt");

    editor.PrintText();

    editor.PrintDocumentInfo();

    editor.PrintPositionInfo();

#endif

    return 0;
}
