#include "sidebar.h"
#include "../../abstractions/rguiabs.h"
#include "../../external/tinydir/tinydir.h"



void EditorSidebarRenderSideBar(){
    static bool init = false;
    static bool prevtime = 0;
    if(init == false){
        prevtime = GetTime();
        init = true;
    }
    Color col = RGUIGetApplicationColor();
    col.b += 15;
    col.g -= 15;

    DrawRectangle(0, 0 + 90, 300, GetScreenHeight() - 90, col);
    RGUIDrawText("Files", 10, 0 + 100, 30, WHITE);
    DrawRectangle(0, 0 + 130, 300, 2, WHITE);
    if(GetTime() - prevtime >= 10){
        tinydir_dir dir;
        tinydir_open_sorted(&dir, ".");
        for(int i = 0; i < dir.n_files; i++){
            tinydir_file file;
            tinydir_readfile_n(&dir, &file, i);
            if(file.is_dir){
                printf("%s\\\n", file.name);
            } else printf("%s\n", file.name);
        }
        prevtime = GetTime();
    }   
    
    
}