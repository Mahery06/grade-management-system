#ifndef TEMPLATE_H
#define TEMPLATE_H
#define MAX_STUDENTS 200
#define ID_LENGTH 20
#define NAME_LENGTH 40
#define MAX_RESULT MAX_STUDENTS

typedef struct
{
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    double score;
} Student;
#endif