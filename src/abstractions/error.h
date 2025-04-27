#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED




#include "../cyra.h"

#define ERRORLEN 128

typedef struct _Error {
    bool hasFailed;
    char error[ERRORLEN];
} Error;

bool ErrCreateError(Error* err, const char* error);
void ErrCreatePass(Error* err);
void ErrCreateErrorWindow(Error err);
void ErrRenderAllErrorWindows();
#endif