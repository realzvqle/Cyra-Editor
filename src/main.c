#include "abstractions/error.h"
#include "abstractions/rguiabs.h"
#include "editor/editor.h"
#include "editor/text/text.h"
#include "editor/topbar/topbar.h"
#include "raylib/raylib.h"






int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(1600, 900, "Cyra-Editor");
    RGUIInit();
    SetTargetFPS(60);
    char* buffer;
    int i = 0;
    while(!WindowShouldClose()){
        BeginDrawing();
        EditorTextCreateMainTextBox(0, 90, GetScreenWidth(), GetScreenHeight() - 90, 30);
        EditorTopBarRenderTopbar();
        ErrRenderAllErrorWindows();
        ClearBackground(WHITE);
        EndDrawing();
    }
    EditorCleanUp();
    CloseWindow();
    return 0;
}