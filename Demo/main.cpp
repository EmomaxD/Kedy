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

    std::cout << editor.GetText() << std::endl;

    std::cout << "\nChar count: " << editor.GetCharCount() << std::endl;
    std::cout << "WhiteSpace count: " << editor.GetWhiteSpaceCount() << std::endl;
    std::cout << "Total Length: " << editor.GetTotalLength() << std::endl;
    std::cout << "Line count: " << editor.GetLineCount() << std::endl;
    std::cout << "EOL: " << editor.GetEndOfLine() << std::endl;
    std::cout << "Extension: " << editor.GetExtension() << std::endl;

#endif

    return 0;
}
