#include "topbar.h"
#include "../../abstractions/rguiabs.h"
#include "../text/text.h"
#include <string.h>
#include "../../abstractions/error.h"
#include "../../abstractions/file.h"

static char s_CurrentSavedFile[255] = "\0";

// only used for FileOpenButton, normally use EditorTextReturnText() for getting the content for 
// the text
extern char* g_EditorsText;

static inline void FileOpenButton(){
    static char buffer[255] = {'\0'};
    static bool drawWindow = false;
    static bool failSave = false;
    
    int button = RGUIDrawButton(0, 0, 70, 50, "Open");
    if(button == 1){
        drawWindow = true;
    }
    if(drawWindow == true){
        EditorTextCanWriteToTextbox(false);
        int x = (GetScreenWidth() - 400) / 2;
        int y = (GetScreenHeight() - 200) / 2;
        int res = RGUIDrawWindow(x, y, 400, 200, 
                    "Open File");
        if(res == 1){
            memset(buffer, '\0', 255);
            EditorTextCanWriteToTextbox(true);
            drawWindow = false;

        }
        RGUIDrawText("Open File?", x + 10, y + 40, 20, WHITE);
        RGUIDrawTextBox(x + 10, y + 70, 320, 40, buffer, 255);
        int ress = RGUIDrawButton(x + 320, y + 150, 70, 40, " Open ");
        if(ress == 1){
            drawWindow = false;
            EditorTextLoadFileContentIntoTextbox(buffer);
            memset(s_CurrentSavedFile, '\0', 255);
            sprintf(s_CurrentSavedFile, "%s", buffer);
            memset(buffer, '\0', 255);
            EditorTextCanWriteToTextbox(true);
        }
    }
}

static inline void FileSaveAsButton(){
    static char buffer[255] = {'\0'};
    static bool drawWindow = false;
    static bool failSave = false;
    
    int button = RGUIDrawButton(140, 0, 70, 50, "Save As");
    if(button == 1){
        drawWindow = true;
    }
    if(drawWindow == true){
        EditorTextCanWriteToTextbox(false);
        int x = (GetScreenWidth() - 400) / 2;
        int y = (GetScreenHeight() - 200) / 2;
        int res = RGUIDrawWindow(x, y, 400, 200, 
                    "Save File");
        if(res == 1){
            memset(buffer, '\0', 255);
            EditorTextCanWriteToTextbox(true);
            drawWindow = false;

        }
        RGUIDrawText("Save File to?", x + 10, y + 40, 20, WHITE);
        RGUIDrawTextBox(x + 10, y + 70, 320, 40, buffer, 255);
        int ress = RGUIDrawButton(x + 320, y + 150, 70, 40, " Save ");
        if(ress == 1){
            drawWindow = false;
            Error err;
            FileWriteToFile(&err, buffer, EditorTextReturnText());
            if(err.hasFailed == true){
                memset(buffer, '\0', 255);
                ErrCreateErrorWindow(err);
                return;
            }
            memset(s_CurrentSavedFile, '\0', 255);
            sprintf(s_CurrentSavedFile, "%s", buffer);
            memset(buffer, '\0', 255);
            EditorTextCanWriteToTextbox(true);
        }
    }
}

static inline void FileSaveButton(){
    static int state = 0;
    int button = RGUIDrawButton(70, 0, 70, 50, "Save");
    if(button == 1){
        if(strcmp(s_CurrentSavedFile, "\0") == 0){
            state = 1;
        } else {
            state = 2;
        }
    }
    
    switch(state){
        case 1:{
            Error err = {true, "No file current, Please save the file using \"save as\" before saving!"};
            ErrCreateErrorWindow(err);
            state = 0;
            break;
        }
        case 2:{
            Error err;
            FileWriteToFile(&err, s_CurrentSavedFile, EditorTextReturnText());
            if(err.hasFailed == true){
                ErrCreateErrorWindow(err);
            }
            state = 0;
            break;
        }
        default:
            break;
    }

}

void EditorTopBarRenderTopbar(){
    FileOpenButton();
    FileSaveButton();
    FileSaveAsButton();
}