#include "sidebar.h"
#include "../../abstractions/rguiabs.h"




void EditorSidebarRenderSideBar(){
    Color col = RGUIGetApplicationColor();
    col.b += 15;
    col.g -= 15;

    DrawRectangle(0, 0 + 90, 300, GetScreenHeight() - 90, col);
    RGUIDrawText("Files", 10, 0 + 100, 30, WHITE);
    DrawRectangle(0, 0 + 130, 300, 2, WHITE);

}