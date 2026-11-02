#include<stdio.h>
#include<stdlib.h>
#include"head file/read_write.h"


void _abstract(int *total, Student *student)
{
   

    FILE *ptr = fopen("student.dat","r");

    if(ptr == NULL){
        printf("Could not find the file.\n");
        exit(1);
    }

    *total = fread(student,sizeof(Student),MAX_STUDENTS,ptr);

    fclose(ptr);
   
}

void _writeIn(int total,Student *result){
    FILE *ptr;
    ptr= fopen("student.dat","w");

    if (ptr == NULL){
        printf("Could not find the file.\n");
        exit(1);
    }

    for(int i=0;i<total;i++) fwrite(result+i, sizeof(Student), 1, ptr);

    fclose(ptr);

    printf("Write In Successful!😄");
    
}
