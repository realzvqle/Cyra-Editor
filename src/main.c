#include "abstractions/error.h"
#include "abstractions/file.h"
#include "abstractions/rguiabs.h"
#include "editor/editor.h"
#include "editor/sidebar/sidebar.h"
#include "editor/text/text.h"
#include "editor/topbar/topbar.h"
#include "raylib/raylib.h"





int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(1600, 900, "Cyra-Editor");
    RGUIInit();
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        EditorTextCreateMainTextBox(300, 90, GetScreenWidth() + 300, GetScreenHeight() - 90, 30);
        EditorTopBarRenderTopbar();
        EditorSidebarRenderSideBar();
        ErrRenderAllErrorWindows();
        ClearBackground(BLACK);
        EndDrawing();
    }
    // complains about a memory leak on linux when ASAN is enabled, but seems like a bug on linux instead (????)
    CloseWindow();
    return 0;
}