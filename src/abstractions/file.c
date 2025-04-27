#include "file.h"



void WriteToFile(Error* err, const char* file, const char* string){
    FILE* fp = fopen(file, "w");
    if(!fp){
        ErrCreateError(err, "Couldn't Open File");
        return;
    }
    fprintf(fp, "%s", string);
    fclose(fp);
    ErrCreatePass(err);
}


