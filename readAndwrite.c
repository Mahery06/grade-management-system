#include <stdio.h>
#include <stdlib.h>
#include "head file/read_write.h"

void _abstract(int *total, Student *student)
{

    FILE *ptr = fopen("student.dat", "rb");

    if (ptr == NULL)
    {
        printf("找不到文件。\n");
        exit(1);
    }

    *total = (int)fread(student, sizeof(Student), MAX_STUDENTS, ptr);
    if (ferror(ptr))
    {
        printf("读取文件失败。\n");
        fclose(ptr);
        exit(1);
    }

    fclose(ptr);
}

void _writeIn(int total, Student *result)
{
    FILE *ptr;
    ptr = fopen("student.dat", "wb");

    if (ptr == NULL)
    {
        printf("无法打开文件进行写入。\n");
        exit(1);
    }
    size_t written = fwrite(result, sizeof(Student), (size_t)total, ptr);
    int closed = fclose(ptr);
    if (written != (size_t)total || closed != 0)
    {
        printf("写入文件失败。\n");
        exit(1);
    }
    printf("写入成功！😄\n");
}
