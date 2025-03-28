#include "tools.h"
//---------------------------------------------------------------------------
long int FileSize(FILE *file)
{//���������� ������ ��������� �����
    long int pos, fsize;
    if (!file)
       return 0;
    pos = ftell(file);
    fseek(file, 0, 2);
    fsize = ftell(file);
    fseek(file, pos, 0);
    return fsize;
}
//---------------------------------------------------------------------------
long int FileSize(const char *file_name)
{//������ ����� �� ��������
    long int pos, fsize;
    FILE *file = fopen(file_name, "rb");
    if (!file)
       return 0;
    fseek(file, 0 , 2);
    fsize = ftell(file);
    fclose(file);
    return fsize;
}
//---------------------------------------------------------------------------
bool FileExist(const char *file_name)
{//���������� �� ����
   FILE *file;
   file = fopen(file_name, "rb");
   if (!file)
      return false;
   fclose(file);
   return true;
}
//---------------------------------------------------------------------------
bool CreateEmptyFile(const char *file_name)
{//������� ������ ����
   FILE *file;
   file = fopen(file_name, "w");
   if (!file)
      return false;
   fclose(file);
   return true;
}
//---------------------------------------------------------------------------
void SetFileSize(const char *file_name, unsigned new_size)
{//������������� ������ �����
   int file = open(file_name, O_WRONLY);
   chsize(file, new_size);
   close(file);
}
//---------------------------------------------------------------------------
void StrCpy(char *dest, const char *src, int index, int count)
{//�������� count �������� ������ src � dest ������� � index
   int max = index + count;
   for (int i = index, j = 0; i < max; i++, j++)
      dest[j] = src[i];
   dest[count] = '\0';
}
//---------------------------------------------------------------------------
char *GetFileExt(const char *file_name)
{//��������� ���������� �����
   static char ext[4];
   int len = strlen(file_name);
   StrCpy(ext, file_name, len-3, 3);
   return ext;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
