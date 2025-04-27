#include "abstractions/rguiabs.h"
#include "editor/text/text.h"
#include "editor/topbar/topbar.h"
#include "raylib/raylib.h"
#include <stdio.h>






int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "h");
    RGUIInit();
    SetTargetFPS(60);
    char* buffer;
    int i = 0;
    while(!WindowShouldClose()){
        BeginDrawing();
        EditorTextCreateMainTextBox(0, 90, GetScreenWidth(), GetScreenHeight() - 90, 30);
        EditorRenderTopbar();
        ClearBackground(WHITE);
        EndDrawing();
    }
}