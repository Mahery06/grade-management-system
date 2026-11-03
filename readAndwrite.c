#include <stdio.h>
#include <stdlib.h>
#include "head file/read_write.h"

void _abstract(int *total, Student *student)
{

    FILE *ptr = fopen("student.dat", "rb");

    if (ptr == NULL)
    {
        printf("Could not find the file.\n");
        exit(1);
    }

    *total = (int)fread(student, sizeof(Student), MAX_STUDENTS, ptr);
    if (ferror(ptr))
    {
        printf("Read file failed.\n");
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
        printf("Could not open the file for writing.\n");
        exit(1);
    }
    size_t written = fwrite(result, sizeof(Student), (size_t)total, ptr);
    int closed = fclose(ptr);
    if (written != (size_t)total || closed != 0)
    {
        printf("Write file failed.\n");
        exit(1);
    }
    printf("Write In Successful!😄\n");
}
