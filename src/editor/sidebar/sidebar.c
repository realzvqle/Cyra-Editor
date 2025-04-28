#include "sidebar.h"
#include "../../abstractions/rguiabs.h"
#include "../../abstractions/error.h"
#include "../../external/tinydir/tinydir.h"
#include <stdlib.h>
#include "../text/text.h"
#include "../topbar/topbar.h"

static char s_Filepath[25600] = ".";
static char s_CurrentFile[256] = "Untitled";

static int s_PosY = 0;
static int s_Offset = 0;

static inline void CheckIfDirectoryExists(Error* err, const char* directory){
    tinydir_dir dir;
    int result = tinydir_open_sorted(&dir, directory);
    if(result){
        ErrCreateError(err, "Failed to Open Directory");
        return;
    }
    tinydir_close(&dir);
    ErrCreatePass(err);
    return;
}

static inline void PrintFileSystem(const char* directory){
    Error err;
    CheckIfDirectoryExists(&err, directory);
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
        // allocating because if theres a directory we need to add a '/' 
        int length = strlen(file.name);
        char* filenameplusslash = (char*)calloc(length + 10,  sizeof(char));
        if(file.is_dir == true){
            sprintf(filenameplusslash, "(DIR) %s/", file.name);
        } else {
            sprintf(filenameplusslash, "(FILE) %s", file.name);
        }
        int res = RGUIDrawButton(0, (s_PosY + 50) + (i * 50) + s_Offset, 200, 50, filenameplusslash);
        free(filenameplusslash);
        if(res == 1){
            if(file.is_dir == true){
                char filepath[25600];
                sprintf(filepath, "%s/%s", s_Filepath, file.name);
                CheckIfDirectoryExists(&err, filepath);
                if(err.hasFailed == true){
                    ErrCreateErrorWindow(err);
                    return;
                }
                sprintf(s_Filepath, "%s", filepath);

            } else {
                memset(s_CurrentFile, '\0', 256);
                sprintf(s_CurrentFile, "%s", file.name);
                char filepath[512];
                sprintf(filepath, "%s/%s", s_Filepath, file.name);
                EditorTopBarSetSave(filepath);
                EditorTextLoadFileContentIntoTextbox(filepath);
            }
        }
    }
    
}

static inline void EditorSidebarOffset(int amount){
    if(s_Offset > 0){
        s_Offset = 0;
        return;
    }
    s_Offset += (amount * 10);
    
}

void EditorSidebarRenderSideBar(){
    static bool init = false;
    if(init == false){
        s_PosY = 0 + 90;
    }
    Color col = RGUIGetApplicationColor();
    col.b += 15;
    col.g -= 15;
    Rectangle rec = {0, s_PosY, 300, GetScreenHeight() - 90};
    if(CheckCollisionPointRec(GetMousePosition(), rec)){
        EditorSidebarOffset(GetMouseWheelMove());
    }
    
    DrawRectangleRec(rec, col);
    RGUIDrawText("Files", 10, (s_PosY + 10) + s_Offset, 30, RGUIGetTextColor());
    DrawRectangle(0, (s_PosY + 40) + s_Offset, 300, 2, RGUIGetTextColor());
    PrintFileSystem(s_Filepath);
    
    
}


char* EditorSidebarReturnCurrentFile(){
    return s_CurrentFile;
}