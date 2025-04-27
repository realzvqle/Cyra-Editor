#include "topbar.h"
#include "../../abstractions/rguiabs.h"
#include "../text/text.h"
#include <string.h>


static inline void FileSaveButton(){
    static char buffer[255] = {'\0'};
    static bool drawWindow = false;
    static bool failSave = false;
    
    int button = RGUIDrawButton(0, 0, 70, 50, "Save");
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
            FILE* fp = fopen(buffer, "w");
            if(!fp){
                //printf("Failed Saving File!\n");
                memset(buffer, '\0', 255);
                failSave = true;
                return;
            }
            fprintf(fp, "%s", EditorTextReturnText());
            fclose(fp);
            memset(buffer, '\0', 255);
            EditorTextCanWriteToTextbox(true);
        }
    }
    if(failSave == true){

        int x = (GetScreenWidth() - 400) / 2;
        int y = (GetScreenHeight() - 200) / 2;
        int res = RGUIDrawWindow(x, y, 400, 200, 
            "Save File");
        RGUIDrawText("Couldn't Save File! Check\nIf you have permission to!", 
            x + 10, y + 40, 20, RED);
        if(res == 1){
            failSave = false;
            EditorTextCanWriteToTextbox(true);
        }
    }
}

void EditorRenderTopbar(){
    FileSaveButton();
}