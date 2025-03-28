#pragma once
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
enum {a = 1664525};
enum {c = 1013904223};
enum {m = 4294967295};
//---------------------------------------------------------------------------
long int FileSize(FILE *file);
long int FileSize(const char *file_name);
bool FileExist(const char *file_name);
bool CreateEmptyFile(const char *file_name);
void SetFileSize(const char *file_name, unsigned new_size);
void StrCpy(char *dest, const char *src, int index, int count);
char *GetFileExt(const char *file_name);
//---------------------------------------------------------------------------

