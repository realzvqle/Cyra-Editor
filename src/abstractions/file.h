#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED




#include "../cyra.h"
#include "error.h"


void FileWriteToFile(Error* err, const char* file, const char* string);
void FileReadFile(Error* err, const char* file, char** string);
long FileReadFileEx(Error* err, const char* file, char** string);
void FileCheckIfFileExists(Error* err, const char* filename);
#endif