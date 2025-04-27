#include "error.h"
#include "rguiabs.h"
#include <string.h>
#include "../editor/text/text.h"


typedef struct _ErrorWindows {
    Error err;
    bool isActive;
} ErrorWindows;

static ErrorWindows s_ErrWindows[30];
static int s_ErrWindowAmount = 0;

bool ErrCreateError(Error* err, const char* error){
    err->hasFailed = true;
    if(strlen(error) >= ERRORLEN){
        sprintf(err->error, "An error has occured but the error message was too large");
        return false;
    }
    err->hasFailed = true;
    sprintf(err->error, "%s", error);
    return true;
}

void ErrCreatePass(Error* err){
    err->hasFailed = false;
    sprintf(err->error, "No error has occured");
}

static inline int ErrReturnFreeWindowSpot(){
    for(int i = 0; i < s_ErrWindowAmount; i++){
        if(i >= 29) return 29;
        if(s_ErrWindows[i].isActive == false){
            return i;
        }
    }
    return s_ErrWindowAmount++;
}

void ErrCreateErrorWindow(Error err){
    int i = ErrReturnFreeWindowSpot();
    printf("I is %d!\n", i);
    sprintf(s_ErrWindows[i].err.error, "%s", err.error);
    s_ErrWindows[i].err.hasFailed = err.hasFailed;
    s_ErrWindows[i].isActive = true;

}


void ErrRenderAllErrorWindows(){
    for(int i = 0; i < s_ErrWindowAmount; i++){
        if(i >= 30) continue;
        if(s_ErrWindows[i].isActive == false) continue;
        EditorTextCanWriteToTextbox(false);
        int size = MeasureTextEx(RGUIGetFont(), s_ErrWindows[i].err.error, 20, 1).x + 40;
        int x = (GetScreenWidth() - size + (i * 2)) / 2;
        int y = (GetScreenHeight() - 200 + (i * 2)) / 2;
        int res = RGUIDrawWindow(x, y, size, 200, 
            "Cyra-Editor");
        RGUIDrawText(s_ErrWindows[i].err.error, 
            x + 10, y + 40, 20, RED);
        if(res == 1){
            EditorTextCanWriteToTextbox(true);
            s_ErrWindows[i].isActive = false;
        }
    }

}