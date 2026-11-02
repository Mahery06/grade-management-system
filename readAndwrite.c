#include<stdio.h>
#include<stdlib.h>
#include"head file/read_write.h"


void _abstract(int *total, Student *student)
{
    int count =0 ;
    Student group[MAX_STUDENTS]={0}; 

    FILE *ptr = fopen("student.dat","r");

    if(ptr == NULL){
        printf("Could not find the file.\n");
        exit(1);
    }

    *total = fread(group,sizeof(Student),MAX_STUDENTS,ptr);

    fclose(ptr);
    student = group;
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
