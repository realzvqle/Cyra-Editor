#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED










#include "../../cyra.h"


char* EditorTextReturnText();
void EditorTextCanWriteToTextbox(bool canwrite);
int EditorTextCreateMainTextBox(int x, int y, int width, int height, int fontSize);
void EditorTextSetIndexLengthAndCapacity(int index, int length, int capacity);
void EditorTextCleanup();
void EditorTextManuallySetInitToTrue();
void EditorTextLoadFileContentIntoTextbox(char* title);
void EditorTextAddCharacterOffset(int amount);

#endif