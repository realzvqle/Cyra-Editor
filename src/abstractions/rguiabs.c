
/*
    Some Basic RayGUI Abstractions and extra stuff added on top of it which uses RaygUI
*/

#define RAYGUI_IMPLEMENTATION
#include "../raylib/raygui.h"

#include "rguiabs.h"


void RGUIInit(){
    GuiLoadStyle("resources/style/style.rgs");
    //GuiSetStyle(TEXTBOX, TEXT_, TEXT_ALIGN_BOTTOM);
}

Color RGUIGetApplicationColor(){
    return GetColor(GuiGetStyle(TEXTBOX, BASE_COLOR_PRESSED));;
}


int RGUICreateButton(int x, int y, int width, int height, const char* text){
    Rectangle rec = {x, y, width, height};
    return GuiButton(rec, text);
}

void RGUIDrawText(char* text, int x, int y, int fontsize, Color tint){
    Vector2 pos = {x, y};
    DrawTextEx(GuiGetFont(), text, pos, fontsize, 1, tint);
}

int RGUICreateMainTextBox(int x, int y, int width, int height, char* text, int* currentIndex, int fontSize, int textLimit){
    static bool isFocused = false;
    static bool isCaps = false;
    static bool init = false;
    static double blinkTime = 0;
    static int blinkX = 0;
    static int blinkY = 0;
    if(init == false){
        blinkTime = GetTime();
        blinkX = x;
        blinkY = y;
        init = true;
    }
    int returnvalue = 0;
    Rectangle rec = {x, y, width, height};
    Color col = RGUIGetApplicationColor();
    if(!isFocused) col.a = 155;
    else col.a = 255;
    DrawRectangleRec(rec, col);
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if(CheckCollisionPointRec(GetMousePosition(), rec)){ 
            isFocused = true;
            returnvalue = 1;
        } else {
            isFocused = false;
            returnvalue = 0;
        }
    }
    int curKey = GetKeyPressed();
    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    // where the string mess goes
    if(*currentIndex >= textLimit){
        return -1;
    }
    if(isFocused && curKey){
        if(!shift && !isCaps) curKey = tolower(curKey);
        switch(curKey){
            case KEY_BACKSPACE:
                if(*currentIndex == 0) break;
                text[*currentIndex - 1] = '\0';
                *currentIndex = *currentIndex - 1;
                char btemp[2];
                btemp[0] = ' ';
                btemp[1] = '\0';
                blinkX -= MeasureTextEx(GuiGetFont(), " ", fontSize, 1).x;
                break;
            case KEY_RIGHT_SHIFT:
            case KEY_LEFT_SHIFT:
                break;
            case KEY_CAPS_LOCK:
                if(isCaps == false) isCaps = true;
                else isCaps = false;
                break;
            case KEY_ENTER:
                blinkY = MeasureTextEx(GuiGetFont(), "P", fontSize, 1).y;
                blinkX = 0;
                text[*currentIndex] = '\n';
                text[*currentIndex + 1] = '\0';
                *currentIndex = *currentIndex + 1; 
                break;
            default:
                text[*currentIndex] = curKey;
                text[*currentIndex + 1] = '\0';
                *currentIndex = *currentIndex + 1; 
                char atemp[2];
                atemp[0] = curKey;
                atemp[1] = '\0';
                blinkX += MeasureTextEx(GuiGetFont(), atemp, fontSize, 1).x;
                break;
        } 
        printf("Text - %c\n", text[*currentIndex - 1]);
    }
SKIPTEXTADD:
    if(text != NULL) RGUIDrawText(text, x, y, fontSize, WHITE);
    if(GetTime() - blinkTime >= 0.5){
        RGUIDrawText("|", blinkX, 
                blinkY, fontSize, WHITE);
        if(GetTime() - blinkTime >= 1){
            blinkTime = GetTime();
        }
    }
    return returnvalue;
}






