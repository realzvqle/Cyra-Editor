#include "text.h"
#include "../../abstractions/rguiabs.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../../abstractions/error.h"
#include "../../abstractions/file.h"

char* g_EditorsText = NULL;
static int s_EditorsTextIndex;
static bool s_IsFocused = false;
static bool s_IsCaps = false;
static bool s_EditorsTextInit = false;
static bool s_CanWrite = true;
static int s_Capacity = 20;
static int s_Length = 0;
static int s_TextboxX = 0;
static int s_TextBoxY = 0;
static int s_Fontsize = 0;

static inline void RemoveCharacter(){
    if(s_EditorsTextIndex == 0) return;
    g_EditorsText[s_EditorsTextIndex - 1] = '\0';
    s_EditorsTextIndex = s_EditorsTextIndex - 1;
    s_Length--;
}

static inline void AddNewline(){
    g_EditorsText[s_EditorsTextIndex] = '\n';
    g_EditorsText[s_EditorsTextIndex + 1] = '\0';
    s_EditorsTextIndex = s_EditorsTextIndex + 1; 
    s_Length++;
}

static inline void HandleBlinker(){
    // rewrite blinker implem later
}

static inline void AddCharacter(char curKey){
    if(s_Length >= s_Capacity - 10){
        s_Capacity *= 2;
        printf("Reallocating Space to %d\n", s_Capacity);
    REALLOCATE:
        g_EditorsText = (char*)realloc(g_EditorsText, s_Capacity * sizeof(char));
        if(g_EditorsText == NULL){
            printf("Failed Reallocating Memory, Reallocating....\n");
            goto REALLOCATE;
        }
        memset(g_EditorsText + s_Length, '\0', (s_Capacity - s_Length) * sizeof(char));
    }
    g_EditorsText[s_EditorsTextIndex] = curKey;
    g_EditorsText[s_EditorsTextIndex + 1] = '\0';
    s_EditorsTextIndex = s_EditorsTextIndex + 1; 
    s_Length++;
}



char* EditorTextReturnText(){
    return g_EditorsText;
}

void EditorTextCanWriteToTextbox(bool canwrite){
    s_CanWrite = canwrite;
}

int EditorTextCreateMainTextBox(int x, int y, int width, int height, int fontSize){ 
    if(s_EditorsTextInit == false){
        g_EditorsText = (char*)calloc(s_Capacity, sizeof(char));
        if(g_EditorsText == NULL){
            printf("Couldn't Allocate memory!\n");
        }
        s_EditorsTextInit = true;
    }
    s_TextboxX = x;
    s_TextBoxY = y;
    s_Fontsize = fontSize;
    int returnvalue = 0;
    Rectangle rec = {x, y, width, height};
    Color col = RGUIGetApplicationColor();
    if(!s_IsFocused) col.a = 155;
    else col.a = 255;
    DrawRectangleRec(rec, col);
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if(CheckCollisionPointRec(GetMousePosition(), rec)){ 
            s_IsFocused = true;
            returnvalue = 1;
        } else {
            s_IsFocused = false;
            returnvalue = 0;
        }
    }
    if(s_CanWrite == false) goto SKIPTEXTADD;

    int curKey = GetKeyPressed();
    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    if(s_IsFocused && curKey){
        if(!shift && !s_IsCaps) curKey = tolower(curKey);
        switch(curKey){
            case KEY_BACKSPACE:
                RemoveCharacter();
                break;
            case KEY_RIGHT_SHIFT:
            case KEY_LEFT_SHIFT:
                break;
            case KEY_CAPS_LOCK:
                if(s_IsCaps == false) s_IsCaps = true;
                else s_IsCaps = false;
                break;
            case KEY_ENTER:
                AddNewline();
                break;
            default:
                AddCharacter(curKey);
                break;
        } 
        printf("Text - %s\n", g_EditorsText);
    }
    
SKIPTEXTADD:
    if(g_EditorsText != NULL) RGUIDrawText(g_EditorsText, s_TextboxX, s_TextBoxY, s_Fontsize, WHITE);
    HandleBlinker();
    return returnvalue;
}

void EditorTextFreeTextMemory(){
    free(g_EditorsText);
}

void EditorTextSetIndexLengthAndCapacity(int index, int length, int capacity){
    s_EditorsTextIndex = index;
    s_Capacity = capacity;
    s_Length = length;
}
void EditorTextCleanup(){
    free(g_EditorsText);
}

void EditorTextManuallySetInitToTrue(){
    s_EditorsTextInit = true;
}

void EditorTextLoadFileContentIntoTextbox(char* title){
    Error err;
    FileCheckIfFileExists(&err, title);
    if(err.hasFailed == true){
        ErrCreateErrorWindow(err);
        return;
    }
    free(g_EditorsText);
    int size = FileReadFileEx(&err, title, &g_EditorsText);
    if(err.hasFailed == true){
        ErrCreateErrorWindow(err);
        return;
    }
    EditorTextSetIndexLengthAndCapacity(strlen(g_EditorsText), size, size + 90);
    EditorTextManuallySetInitToTrue();
}