#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head file/student.h"

void tailored_report(int total, Student stu[]) {

    printf("同学，你好。你的学号是：");
    char id[10]={0};
    scanf("%s", id);
    char path[40]={0};
    char cont[1000]={0};
    char name[10]={0};
    strcpy(path, "report_resource/report");
    for(int i=0; i<total; i++){
        if(! strcmp(id, stu[i].id)){
        strcpy(name,stu[i].name);
        if(stu[i].score<60) strcat(path, "0-60.txt");
        else if(stu[i].score>=60 && stu[i].score<70) strcat(path, "60-70.txt");
        else if(stu[i].score>=70 && stu[i].score<75) strcat(path, "70-75.txt");
        else if(stu[i].score>=75 && stu[i].score<80) strcat(path, "75-80.txt");
        else if(stu[i].score>=80 && stu[i].score<85) strcat(path, "80-85.txt");
        else if(stu[i].score>=85 && stu[i].score<90) strcat(path, "85-90.txt");
        else if(stu[i].score>=90 && stu[i].score<95) strcat(path, "90-95.txt");
        else if(stu[i].score>=95 && stu[i].score<100) strcat(path, "95-100.txt");
        break;

        }
    }
    FILE* ptr;
    ptr = fopen(path, "r");
    fread(cont,1, 1000, ptr);
    fclose(ptr);
    printf("%s 同学,你的学业规划报告如下：\n",name);
    printf("%s\n", cont);
}
