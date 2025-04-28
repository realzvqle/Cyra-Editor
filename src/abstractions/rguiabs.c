
/*
    Some Basic RayGUI Abstractions and extra stuff added on top of it which uses RayGUI
*/

#define RAYGUI_IMPLEMENTATION
#include "../external/raylib/raygui.h"

#include "rguiabs.h"


void RGUIInit(){
    GuiLoadStyle("resources/style/style.rgs");
    //GuiSetStyle(TEXTBOX, TEXT_, TEXT_ALIGN_BOTTOM);
}

Color RGUIGetApplicationColor(){
    return GetColor(GuiGetStyle(TEXTBOX, BASE_COLOR_PRESSED));;
}


int RGUIDrawButton(int x, int y, int width, int height, const char* text){
    Rectangle rec = {x, y, width, height};
    return GuiButton(rec, text);
}

void RGUIDrawText(char* text, int x, int y, int fontsize, Color tint){
    Vector2 pos = {x, y};
    DrawTextEx(GuiGetFont(), text, pos, fontsize, 1, tint);
}


Font RGUIGetFont(){
    return GuiGetFont();
}

int RGUIDrawWindow(int x, int y, int width, int height, char* title){
    Rectangle rec = {x, y, width, height};
    return GuiWindowBox(rec, title);
}


int RGUIDrawTextBox(int x, int y, int width, int height, char* text, int textlim){
    Rectangle rec = {x, y, width, height};
    return GuiTextBox(rec, text, textlim, true);
}

