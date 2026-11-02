#include<stdio.h>
#include<stdlib.h>
#include "read_write.h"


Student *_abstract(int *total)
{
    int count =0 ;
    Student group[MAX_STUDENTS]={0}; 

    FILE *ptr = fopen("student.dat","r");

    *total = fread(group,sizeof(Student),MAX_STUDENTS,ptr);

    fclose(ptr);
    return group;
}

void _writeIn(int total,Student *result){
    FILE *ptr;
    ptr= fopen("student.dat","w");

    if (ptr == NULL){
        printf("Could not find the file.\n");
        exit(1);
    }

    for(int i=0;i<total;i++) fwrite(result+i, sizeof(Student), 1, ptr);

    printf("Write In Successful!😄");
    
}
