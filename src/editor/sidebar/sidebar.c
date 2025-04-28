#include "sidebar.h"
#include "../../abstractions/rguiabs.h"
#include "../../abstractions/error.h"
#include "../../external/tinydir/tinydir.h"
#include <stdlib.h>
#include "../text/text.h"
#include "../topbar/topbar.h"

static char s_Filepath[2560] = ".";

static inline int CheckHowManyFilesPerDirectory(Error* err, const char* directory){
    tinydir_dir dir;
    int result = tinydir_open_sorted(&dir, directory);
    if(result){
        ErrCreateError(err, "Failed to Open Directory");
        return 0;
    }
    int amount = dir.n_files;
    tinydir_close(&dir);
    ErrCreatePass(err);
    return amount;
}

static inline void PrintFileSystem(const char* directory){
    Error err;
    int length = CheckHowManyFilesPerDirectory(&err, directory);
    if(err.hasFailed == true){
        ErrCreateErrorWindow(err);
        return;
    }
    tinydir_dir dir;
    tinydir_open_sorted(&dir, directory);
    int amount = dir.n_files;
    for(int i = 0; i < amount; i++){
        tinydir_file file;
        tinydir_readfile_n(&dir, &file, i);
        int res = RGUIDrawButton(0, 0 + 140 + (i * 50), 200, 50, file.name);
        if(res == 1){
            if(file.is_dir == true){
                sprintf(s_Filepath, "%s/%s", s_Filepath, file.name);
            } else {
                char filepath[512];
                sprintf(filepath, "%s/%s", s_Filepath, file.name);
                EditorTopBarSetSave(filepath);
                EditorTextLoadFileContentIntoTextbox(filepath);
            }
        }
    }
    
}

void EditorSidebarRenderSideBar(){
    static bool init = false;
    static bool prevtime = 0;
    if(init == false){
        PrintFileSystem(".");
        prevtime = GetTime();
        init = true;
    }
    Color col = RGUIGetApplicationColor();
    col.b += 15;
    col.g -= 15;

    DrawRectangle(0, 0 + 90, 300, GetScreenHeight() - 90, col);
    RGUIDrawText("Files", 10, 0 + 100, 30, WHITE);
    DrawRectangle(0, 0 + 130, 300, 2, WHITE);
    if(GetTime() - prevtime > 0.1){
        PrintFileSystem(s_Filepath);
        prevtime = GetTime();
    }   
    
    
}