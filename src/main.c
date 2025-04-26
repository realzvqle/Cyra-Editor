#include "abstractions/rguiabs.h"
#include "raylib/raylib.h"
#include <stdio.h>






int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "h");
    RGUIInit();
    char buffer[512];
    int i = 0;
    while(!WindowShouldClose()){
        BeginDrawing();
        RGUICreateMainTextBox(0, 90, GetScreenWidth(), GetScreenHeight() - 90, buffer, &i, 30, 512);
        //RGUICreateButton(10, 10, 200, 90, "Click Me!");
        RGUIDrawText("Cyra-Editor: Copyright zvqlifed", 10, 10, 30, WHITE);
        ClearBackground(BLACK);
        EndDrawing();
    }
}