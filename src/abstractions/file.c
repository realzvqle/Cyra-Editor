#include "file.h"
#include "error.h"
#include <string.h>



void FileWriteToFile(Error* err, const char* file, const char* string){
    FILE* fp = fopen(file, "w");
    if(!fp){
        ErrCreateError(err, "Couldn't Open File");
        return;
    }
    fprintf(fp, "%s", string);
    fclose(fp);
    ErrCreatePass(err);
}


void FileReadFile(Error* err, const char* file, char** string){
    FILE* fp = fopen(file, "r");
    if(!fp){
        ErrCreateError(err, "Couldn't Open File");
        return;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    *string = (char*)calloc(size, sizeof(char));
    fread(*string, size, 1, fp);
    ErrCreatePass(err);
    fclose(fp);
}

long FileReadFileEx(Error* err, const char* file, char** string){
    FILE* fp = fopen(file, "r");
    if(!fp){
        ErrCreateError(err, "Couldn't Open File");
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    *string = (char*)calloc(size + 90, sizeof(char));
    fread(*string, size, 1, fp);
    ErrCreatePass(err);
    fclose(fp);
    return size;
}


long FileCheckIfFileExists(Error* err, const char* filename){
    FILE* fp = fopen(filename, "r");
    if(!fp){
        ErrCreateError(err, "Couldn't Open File");
        return -1;
    }
    fclose(fp);
    
}