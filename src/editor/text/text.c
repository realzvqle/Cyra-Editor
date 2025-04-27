#include "text.h"
#include "../../abstractions/rguiabs.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char* s_EditorsText = NULL;
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
    s_EditorsText[s_EditorsTextIndex - 1] = '\0';
    s_EditorsTextIndex = s_EditorsTextIndex - 1;
    s_Length--;
}

static inline void AddNewline(){
    s_EditorsText[s_EditorsTextIndex] = '\n';
    s_EditorsText[s_EditorsTextIndex + 1] = '\0';
    s_EditorsTextIndex = s_EditorsTextIndex + 1; 
    s_Length++;
}

static inline void HandleBlinker(){
    // rewrite blinker implem later
}

static inline void AddCharacter(char curKey){
    if(s_Length >= s_Capacity){
        s_Capacity *= 2;
        printf("Reallocating Space to %d\n", s_Capacity);
    REALLOCATE:
        s_EditorsText = (char*)realloc(s_EditorsText, s_Capacity * sizeof(char));
        if(s_EditorsText == NULL){
            printf("Failed Reallocating Memory, Reallocating....\n");
            goto REALLOCATE;
        }
        memset(s_EditorsText + s_Length, '\0', (s_Capacity - s_Length) * sizeof(char));
    }
    s_EditorsText[s_EditorsTextIndex] = curKey;
    s_EditorsText[s_EditorsTextIndex + 1] = '\0';
    s_EditorsTextIndex = s_EditorsTextIndex + 1; 
    s_Length++;
}



char* EditorTextReturnText(){
    return s_EditorsText;
}

void EditorTextCanWriteToTextbox(bool canwrite){
    s_CanWrite = canwrite;
}

int EditorTextCreateMainTextBox(int x, int y, int width, int height, int fontSize){ 
    if(s_EditorsTextInit == false){
        s_EditorsText = (char*)calloc(s_Capacity, sizeof(char));
        if(s_EditorsText == NULL){
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
        printf("Text - %d\n", curKey);
    }
    
SKIPTEXTADD:
    if(s_EditorsText != NULL) RGUIDrawText(s_EditorsText, s_TextboxX, s_TextBoxY, s_Fontsize, WHITE);
    HandleBlinker();
    return returnvalue;
}

