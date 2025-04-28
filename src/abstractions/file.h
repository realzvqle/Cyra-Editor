#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED




#include "../cyra.h"
#include "error.h"


void WriteToFile(Error* err, const char* file, const char* string);
void ReadFile(Error* err, const char* file, char** string);
long ReadFileEx(Error* err, const char* file, char** string);
#endif